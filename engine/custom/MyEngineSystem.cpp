#include "MyEngineSystem.h"
#include <iomanip>  // for std::put_time
#include <sstream>  // for std::ostringstream
#include <chrono>   // for std::chrono::system_clock
#include <ctime>    // for std::localtime
#include <filesystem> // for handling files and directories
#include <iostream>




namespace fs = std::filesystem;  // 使用 C++17 文件系统库

// 定义全局的 MyEngineSystem 实例
MyEngineSystem g_Logger;

// 设置最大日志文件数量
const size_t MAX_LOG_FILES = 5;

// 获取当前时间戳，格式化为 yyyy-mm-dd_hh-mm-ss
std::string MyEngineSystem::GetTimeStampForLog() {
    auto now = std::chrono::system_clock::now();
    std::time_t timeNow = std::chrono::system_clock::to_time_t(now);
    std::tm* tmNow = std::localtime(&timeNow);
    std::ostringstream oss;
    oss << std::put_time(tmNow, "%Y-%m-%d_%H-%M-%S");  // 格式化为 "yyyy-mm-dd_hh-mm-ss"
    return oss.str();
}

// 检查并执行日志轮转，保留最新的 5 个日志文件
void MyEngineSystem::RotateLogs() {
    const std::string logDir = "logs";

    // 如果日志文件夹不存在，创建文件夹
    if (!fs::exists(logDir)) {
        fs::create_directory(logDir);
    }

    // 获取所有日志文件并按时间排序
    std::vector<fs::path> logFiles;
    for (const auto& entry : fs::directory_iterator(logDir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            logFiles.push_back(entry.path());
        }
    }

    // 按文件修改时间排序（从最旧到最新）
    std::sort(logFiles.begin(), logFiles.end(),
        [](const fs::path& a, const fs::path& b) {
            return fs::last_write_time(a) < fs::last_write_time(b);
        });

    // 如果日志文件数量超过限制，删除最旧的文件
    while (logFiles.size() > MAX_LOG_FILES - 1) { // 保留一个位置给新文件
        try {
            std::cout << "Removing old log file: " << logFiles.front() << std::endl;
            fs::remove(logFiles.front()); // 删除最旧的日志文件
            logFiles.erase(logFiles.begin()); // 从列表中移除
        }
        catch (const std::exception& e) {
            std::cerr << "Failed to remove old log file: " << logFiles.front() << " - " << e.what() << std::endl;
            break;
        }
    }
}


// 构造函数：打开日志文件
MyEngineSystem::MyEngineSystem() {
    static bool isInitialized = false; // 静态变量，记录是否已经初始化

    if (isInitialized) {
        std::cout << "MyEngineSystem Constructor Called Again (Skipped)" << std::endl;
        return; // 如果已经初始化，直接返回
    }

    isInitialized = true; // 设置为已初始化

    std::cout << "MyEngineSystem Constructor Called" << std::endl;

    RotateLogs(); // 调用日志轮转系统

    std::string logFileName = "logs/MyEngineLog_" + GetTimeStampForLog() + ".txt";

    logFile.open(logFileName, std::ios::out);
    if (!logFile) {
        std::cerr << "Failed to open log file: " << logFileName << std::endl;
    }
    else {
        logFile << "Log file created successfully: " << logFileName << std::endl;
        std::cout << "Log file created: " << logFileName << std::endl;
    }
}

// 析构函数：关闭日志文件
MyEngineSystem::~MyEngineSystem() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

std::string MyEngineSystem::GetCurrentTime() {
    auto now = std::chrono::system_clock::now();  // 获取当前时间 Get current time
    std::time_t timeNow = std::chrono::system_clock::to_time_t(now);  // 转换为时间戳 Convert to timestamp

    std::tm* tmNow = std::localtime(&timeNow);  // 获取当前本地时间 Get current local time
    std::ostringstream oss;
    oss << std::put_time(tmNow, "%Y-%m-%d %H:%M:%S");  // 格式化时间Formatting time
    return oss.str();
}

// 设置日志过滤级别
void MyEngineSystem::SetLogLevel(LogLevel level) {
    currentLogLevel = level;
    LogInfo("Log level set to " + std::to_string(level)); // 记录级别更改
}

// 获取当前日志过滤级别
MyEngineSystem::LogLevel MyEngineSystem::GetLogLevel() const {
    return currentLogLevel;
}


// 私有方法：记录日志
void MyEngineSystem::Log(const std::string& message, LogLevel level) {
    // 过滤日志：如果日志级别低于当前设置，则直接返回
    if (level < currentLogLevel) {
        return; // 忽略日志
    }
    
    std::string levelStr;
    switch (level) {
    case INFO: levelStr = "[INFO]"; break;
    case WARNING: levelStr = "[WARNING]"; break;
    case ERROR: levelStr = "[ERROR]"; break;
    case EASTER_EGG: levelStr = "[EASTER_EGG]"; break;
    }

    std::string timeStr = GetCurrentTime();  // 获取时间戳
    std::string logMessage = timeStr + " " + levelStr + " " + message;  // 将时间戳和日志消息拼接

    std::cout << logMessage << std::endl;  // 输出到控制台
    if (logFile.is_open()) {
        logFile << logMessage << std::endl;  // 写入日志文件
    }
}

// 公有方法：记录不同级别的日志
void MyEngineSystem::LogInfo(const std::string& message) {
    Log(message, INFO);
}

void MyEngineSystem::LogWarning(const std::string& message) {
    Log(message, WARNING);
}

void MyEngineSystem::LogError(const std::string& message) {
    Log(message, ERROR);
}

// 激活复活节彩蛋
void MyEngineSystem::ActivateEasterEgg() {
    Log("Kai-Qian-CI517-2024", EASTER_EGG);
}

// 新增方法：记录 CRITICAL 级别的日志
void MyEngineSystem::LogCritical(const std::string& message) {
    Log(message, CRITICAL);
}


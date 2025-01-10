#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include "../EngineCommon.h"
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <filesystem> // include filesystem 头文件
#include <vector>     // vector 来存储文件路径
#include <functional> // std::function 



namespace fs = std::filesystem;  // need C++17 文件系统库

class MyEngineSystem {
public:
    // 枚举：日志级别 Enum log level
    enum LogLevel { INFO, WARNING, ERROR, CRITICAL, EASTER_EGG};

    MyEngineSystem();  // 构造函数
    ~MyEngineSystem(); // 析构函数

    //不同级别的日志记录 different levels of logging
    void LogInfo(const std::string& message);
    void LogWarning(const std::string& message);
    void LogError(const std::string& message);
    void ActivateEasterEgg();// Egg

    void LogCritical(const std::string& message); // 异常捕获

    bool logMovement = false; // log player movement

    // 设置日志过滤器
    void SetLogLevel(LogLevel level);
    LogLevel GetLogLevel() const;

private:
    // 当前最低日志级别
    LogLevel currentLogLevel;

    // 获取当前时间戳
    std::string GetTimeStampForLog(); 

    // Get current time 获取当前的时间
    std::string GetCurrentTime();

    // 私有方法：记录日志
    void Log(const std::string& message, LogLevel level);

    //日志轮转log rotate
    void RotateLogs();

    std::ofstream logFile; // 日志文件
};

// 提供一个全局的日志接口
extern MyEngineSystem g_Logger;

#endif // __MY_ENGINE_H__

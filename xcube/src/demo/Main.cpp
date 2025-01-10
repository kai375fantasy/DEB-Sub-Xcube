#include "MyGame.h"
#include "../engine/custom/MyEngineSystem.h"

int main(int argc, char* args[]) {
    // 设置日志过滤等级为 WARNING，只记录 WARNING、ERROR 和 CRITICAL 级别日志
    g_Logger.SetLogLevel(MyEngineSystem::INFO);

    try {
        g_Logger.LogInfo("Game engine started."); // 开始记录程序运行
        MyGame game;
        game.runMainLoop();
    }
    catch (EngineException& e) {
        std::cout << e.what() << std::endl;
        // 记录引擎异常到日志 exceptions to the log
        g_Logger.LogCritical("EngineException caught: " + std::string(e.what()));
        getchar();
    }
    catch (std::exception& e) {
        // 捕获标准异常并记录日志 Catch  exceptions
        g_Logger.LogCritical("Unhandled std::exception: " + std::string(e.what()));
        getchar();
    }
    catch (...) {
        // 捕获所有未知异常并记录日志
        g_Logger.LogCritical("Unhandled unknown exception occurred.");
        getchar();
    }

    g_Logger.LogInfo("Game engine terminated gracefully."); // 程序正常终止日志
    return 0;
}

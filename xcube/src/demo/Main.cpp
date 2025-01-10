#include "MyGame.h"
#include "../engine/custom/MyEngineSystem.h"

int main(int argc, char* args[]) {
    // ������־���˵ȼ�Ϊ WARNING��ֻ��¼ WARNING��ERROR �� CRITICAL ������־
    g_Logger.SetLogLevel(MyEngineSystem::INFO);

    try {
        g_Logger.LogInfo("Game engine started."); // ��ʼ��¼��������
        MyGame game;
        game.runMainLoop();
    }
    catch (EngineException& e) {
        std::cout << e.what() << std::endl;
        // ��¼�����쳣����־ exceptions to the log
        g_Logger.LogCritical("EngineException caught: " + std::string(e.what()));
        getchar();
    }
    catch (std::exception& e) {
        // �����׼�쳣����¼��־ Catch  exceptions
        g_Logger.LogCritical("Unhandled std::exception: " + std::string(e.what()));
        getchar();
    }
    catch (...) {
        // ��������δ֪�쳣����¼��־
        g_Logger.LogCritical("Unhandled unknown exception occurred.");
        getchar();
    }

    g_Logger.LogInfo("Game engine terminated gracefully."); // ����������ֹ��־
    return 0;
}

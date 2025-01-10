#include "MyGame.h"
#include <chrono>

int MyGame::runMainLoop() {
    
    try {
        return AbstractGame::runMainLoop(); // 调用父类方法
    }
    catch (EngineException& e) {
        g_Logger.LogCritical("EngineException caught: " + std::string(e.what())); // 记录异常到日志
        throw; // 重新抛出异常供上层捕获
    }
    catch (std::exception& e) {
        g_Logger.LogCritical("Unhandled std::exception: " + std::string(e.what())); // 记录标准异常
        throw;
    }
    catch (...) {
        g_Logger.LogCritical("Unhandled unknown exception occurred."); // 记录未知异常
        throw;
    }
}

// 构造函数：初始化游戏
MyGame::MyGame() : AbstractGame(), score(0), lives(3), numKeys(5), gameWon(false), box(5, 5, 30, 30) {
    //过滤 Debug Level
    g_Logger.SetLogLevel(MyEngineSystem::WARNING);
    
    g_Logger.LogInfo("Game started."); // 记录游戏启动信息

    // 设置字体和垂直同步
    TTF_Font* font = ResourceManager::loadFont("res/fonts/arial.ttf", 36);
    gfx->useFont(font);
    gfx->setVerticalSync(true);

    // 初始化钥匙对象
    for (int i = 0; i < numKeys; i++) {
        std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
        k->isAlive = true;
        k->pos = Point2(getRandom(0, 750), getRandom(0, 550));
        gameKeys.push_back(k);
    }
}

// 析构函数：记录游戏终止日志
MyGame::~MyGame() {
    g_Logger.LogInfo("Game terminated.");
}

// 处理玩家键盘输入
void MyGame::handleKeyEvents() {
    int speed = 3;
    std::string currentDirection = "";

    if (eventSystem->isPressed(Key::W)) {
        velocity.y = -speed;
        currentDirection = "up";
    }
    if (eventSystem->isPressed(Key::S)) {
        velocity.y = speed;
        currentDirection = "down";
    }
    if (eventSystem->isPressed(Key::A)) {
        velocity.x = -speed;
        currentDirection = "left";
    }
    if (eventSystem->isPressed(Key::D)) {
        velocity.x = speed;
        currentDirection = "right";
    }

    // 只在方向改变时记录日志
    if (currentDirection != lastDirection) {
        lastDirection = currentDirection;
        if (!currentDirection.empty()) {
            g_Logger.LogInfo("Player moved " + currentDirection + ".");
        }
    }
}

// 游戏更新逻辑
void MyGame::update() {
    // 更新玩家位置
    box.x += velocity.x;
    box.y += velocity.y;

    // 检查是否拾取钥匙
    for (auto key : gameKeys) {
        if (key->isAlive && box.contains(key->pos)) {
            score += 200;
            g_Logger.LogInfo("Collected a key. Score: " + std::to_string(score));
            key->isAlive = false;
            numKeys--;
        }
    }

    velocity.x = 0;
    velocity.y = 0;

    // 检查游戏胜利条件
    if (numKeys == 0 && !gameWon) {
        gameWon = true;
        g_Logger.LogInfo("Game won!");
        g_Logger.ActivateEasterEgg();
    }
}

// 渲染游戏内容
void MyGame::render() {
    gfx->setDrawColor(SDL_COLOR_RED);
    gfx->drawRect(box);

    gfx->setDrawColor(SDL_COLOR_YELLOW);
    for (auto key : gameKeys)
        if (key->isAlive)
            gfx->drawCircle(key->pos, 5);
}

// 渲染 UI 界面
void MyGame::renderUI() {
    gfx->setDrawColor(SDL_COLOR_AQUA);

    // 绘制分数
    std::string scoreStr = std::to_string(score);
    gfx->drawText("Score: " + scoreStr, 780 - scoreStr.length() * 50, 25);

    // 绘制胜利信息
    if (gameWon) {
        gfx->drawText("YOU WON", 250, 500);
    }

    // 计算并绘制 FPS
    static Uint32 lastFrameTime = 0;
    Uint32 currentFrameTime = SDL_GetTicks();
    int fps = 0;

    if (currentFrameTime - lastFrameTime > 0) {
        fps = 1000 / (currentFrameTime - lastFrameTime);
    }
    lastFrameTime = currentFrameTime;

    // 在左上角绘制 FPS
    gfx->drawText("FPS: " + std::to_string(fps), 10, 10);
}

#include "MyGame.h"
#include <chrono>

MyGame::MyGame() : AbstractGame(), score(0), lives(3), numKeys(5), gameWon(false), box(5, 5, 30, 30) {
	g_Logger.LogInfo("Game started."); // ��¼��Ϸ������Ϣ
	TTF_Font * font = ResourceManager::loadFont("res/fonts/arial.ttf", 36);//�����С font
	gfx->useFont(font);
	gfx->setVerticalSync(true);

    for (int i = 0; i < numKeys; i++) {
        std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
        k->isAlive = true;
        k->pos = Point2(getRandom(0, 750), getRandom(0, 550));
        gameKeys.push_back(k);
    }
}

MyGame::~MyGame() {
    g_Logger.LogInfo("Game terminated.");
}


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

    // ֻ�ڷ���ı�ʱ��¼��־ only log direction when it is changed
    if (currentDirection != lastDirection) {
        lastDirection = currentDirection;
        if (currentDirection != "") {
            g_Logger.LogInfo("Player moved " + currentDirection + "."); // <-- ���£���¼����ƶ��ķ���
        }
    }
}

void MyGame::update() {

    


    box.x += velocity.x;
    box.y += velocity.y;

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

    if (numKeys == 0 && !gameWon) {
        gameWon = true;
        g_Logger.LogInfo("Game won!");
        g_Logger.ActivateEasterEgg();
    }
}

void MyGame::render() {
	gfx->setDrawColor(SDL_COLOR_RED);
	gfx->drawRect(box);

	gfx->setDrawColor(SDL_COLOR_YELLOW);
	for (auto key : gameKeys)
        if (key->isAlive)
		    gfx->drawCircle(key->pos, 5);
}

void MyGame::renderUI() {
    gfx->setDrawColor(SDL_COLOR_AQUA);

    // ���Ʒ���
    std::string scoreStr = std::to_string(score);
    gfx->drawText("Score: " + scoreStr, 780 - scoreStr.length() * 50, 25);

    // ����ʤ����Ϣ
    if (gameWon) {
        gfx->drawText("YOU WON", 250, 500);
    }

    // ���㲢���� FPS Calculate and render
    static Uint32 lastFrameTime = 0;
    Uint32 currentFrameTime = SDL_GetTicks();
    int fps = 0;

    if (currentFrameTime - lastFrameTime > 0) {
        fps = 1000 / (currentFrameTime - lastFrameTime); // Calculate FPS
    }
    lastFrameTime = currentFrameTime;

    // �����Ͻǻ��� FPS in the upper left corner
    gfx->drawText("FPS: " + std::to_string(fps), 10, 10);
}
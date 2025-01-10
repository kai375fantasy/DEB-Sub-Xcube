#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/AbstractGame.h"
#include "../engine//custom/MyEngineSystem.h" // 添加日志系统头文件

struct GameKey {
	Point2 pos;
	bool isAlive;
};

class MyGame : public AbstractGame {
	private:
		Rect box;

		Vector2i velocity;

		std::vector<std::shared_ptr<GameKey>> gameKeys;

		/* GAMEPLAY */
		int score, numKeys, lives;
		bool gameWon;

		// 记录玩家上一个移动的方向 latest movement
		std::string lastDirection;


		void handleKeyEvents();
		void update();
		void render();
		void renderUI();

		void initSubsystem();   // 初始化子系统
		void cleanupSubsystem(); // 清理子系统
		
	public:
        MyGame();
		~MyGame();
		int runMainLoop(); // 包装主循环，包括异常捕获
};

#endif // __TEST_GAME_H__
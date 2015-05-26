#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
class PlayLayer;
class BgLayer;
class MenuLayer;

class GameScene : public cocos2d::Layer
{
public:
	enum tags
	{
		BG_TAG = 1,
		PLAY_TAG = 2,
		MENU_TAG = 3
	};
    static cocos2d::Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(GameScene);

	void resetGame();
	void showScore();
	int getCount();
	void setGameOver();
	void time_counting(float dt);
	void update(float delta);
private:
	PlayLayer* playLayer;
	BgLayer* bgLayer;
	MenuLayer* menuLayer;
	int count;
	bool isGameOver;
};

#endif // __GAMESCENE_H__

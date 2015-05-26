#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__
#include "cocos2d.h"
class GameScene;
class MenuLayer;

class GameOverScene : public cocos2d::Layer
{
public:
	GameOverScene();
	~GameOverScene();

	static cocos2d::Scene* createScene(int _count = 0);
	virtual bool init(int _count);
	static GameOverScene* create(int _count);
	void showResult();
private:
	int useTime;
	int bestScore;
	MenuLayer* menuLayer;
};
#endif

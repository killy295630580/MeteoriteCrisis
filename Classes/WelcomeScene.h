#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__
#include "cocos2d.h"
class MenuLayer;
class BgLayer;

class WelcomeScene:public cocos2d::Layer
{
public:
	WelcomeScene();
	~WelcomeScene();
	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(WelcomeScene);
private:
	BgLayer* bgLayer;
	MenuLayer* menuLayer;

};

#endif

#ifndef __HOWTOPLAY_H__
#define __HOWTOPLAY_H__

#include "cocos2d.h"
class HowToPlay :public cocos2d::LayerColor
{
public:
	HowToPlay();
	~HowToPlay();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HowToPlay);
};

#endif 


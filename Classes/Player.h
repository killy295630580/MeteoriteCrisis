#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "cocos2d.h"
class PlayLayer;

class Player :public cocos2d::Node
{
public:
	Player();
	~Player();
	virtual bool init();
	CREATE_FUNC(Player);

	virtual cocos2d::Size getContentSize();
	virtual cocos2d::Rect getBoundingBox();
	void setTarget(const cocos2d::Vec2& _target);
	void setTarget(const float& x,const float& y);
	void fire();
	void hurt();
	void beCrushed();
	bool checkCrushed();
	int getShape();
	float getR();
	cocos2d::Vec2 getCenter();
	void reset();
private:
	cocos2d::Sprite * mainSprite;
	cocos2d::Size mainSize;
	PlayLayer* playLayer;
	float r;
	cocos2d::Vec2 center;
	cocos2d::Rect rect;
	bool isCrushed;
};
#endif
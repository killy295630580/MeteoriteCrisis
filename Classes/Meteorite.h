#ifndef __METEORITE_H__
#define __METEORITE_H__
#include "cocos2d.h"
class PlayLayer;

class Meteorite : public cocos2d::Node
{
public:
	enum MSize
	{
		nothing = 0,
		Tiny = 1,
		Small,
		Medium,
		Big,
		Huge,
		Super
	};
	float speeds[7];
	int lifes[7];
	float scaleRate[7];
	Meteorite();
	~Meteorite();
	static Meteorite* create3();
	static Meteorite* create4();
	static Meteorite* create5();
	static Meteorite* create6();
	int getShape();
	float getR();
	cocos2d::Vec2 getCenter();
	float getSpeed();
	MSize getMSize();
	int getMaxLife();
	int getLife();
	bool setLife(int _life);
	void deleteMe();
	bool checkDelete();
public:
	cocos2d::Vector<Meteorite*> childs;
private:
	virtual bool init(MSize);
	static Meteorite* create(MSize);
	cocos2d::Sprite* mainSprite;
	cocos2d::Size mainSize;
	PlayLayer* playLayer;
	float speed;
	MSize mSize;
	bool isPowerful;
	int life;
	int maxLife;
	bool isCrushed;
	float r;
	cocos2d::Vec2 center;
};

#endif
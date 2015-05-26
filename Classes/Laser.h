#ifndef __LASER_H__
#define __LASER_H__
#include "cocos2d.h"

class PlayLayer;
class Laser:public cocos2d::Node
{
public:
	enum Type
	{
		Small = 1,
		Big = 2
	}; 

	Laser();
	~Laser();
	virtual bool init(Type type);
	static Laser* create(Type type);
	void createLaser(Type type);
	bool getEffective();
	void setEffective(bool _isEffective);
	int getPower();
	float getSpeed();
	void setSpeed(int _speed);
	int getShape();
	cocos2d::Rect getRect();
	float getR();
	cocos2d::Vec2 getCenter();
	void setAnchorPoint(cocos2d::Vec2);
	void changeLength(float scale);
	void deleteMe();
	bool checkDelete();
private:
	cocos2d::Sprite* laserbeam;
	bool isEffective;
	float speed;
	PlayLayer* playLayer;
	cocos2d::Rect rect;
	float r;
	cocos2d::Vec2 center;
	cocos2d::Size mainSize;
	Type type;
	bool tobeDelete;
	int power;
};

#endif




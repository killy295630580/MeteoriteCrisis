#ifndef __UTILS_H__
#define __UTILS_H__
#include "cocos2d.h"
USING_NS_CC;
class Utils
{
public:
	~Utils();
	static Utils * getInstance();
	static void destroyInstance();
	bool collisionDetection(Vec2 point1, Vec2 point2, Vec2 center, float r);
	bool collisionDetection(Rect rect, Vec2 center, float r);
	bool collisionDetection(Vec2 center1, float r1, Vec2 center2, float r2);
	bool collisionDetection(Rect rect1, Rect rect2);
	void setRandSeed();
	int getRandInt(int min, int max);
	int getRandInt(int max);
private:
	Utils();

};

#endif


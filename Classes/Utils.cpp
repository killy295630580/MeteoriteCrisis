#include "Utils.h"


Utils::Utils()
{
}


Utils::~Utils()
{
	destroyInstance();
}

static Utils *instance = nullptr;
Utils* Utils::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Utils();
	}
	return instance;
}
void Utils::destroyInstance()
{
	if (instance == nullptr)
		return;
	delete instance;
}

void Utils::setRandSeed()
{
	struct timeval psv;
	gettimeofday(&psv, NULL);
	unsigned rand_seed = (unsigned)psv.tv_usec;
	srand(rand_seed);
}
int Utils::getRandInt(int max)
{
	setRandSeed();
	if (max < 1)
	{
		return 1 + rand() % INT_MAX;
	}
	return 1 + rand() % max;
}
int Utils::getRandInt(int min, int max)
{
	setRandSeed();
	if (max < min)
	{
		return 1 + rand() % INT_MAX;
	}
	return min + rand() % (max + 1 - min);
}
// �����������ײ
bool Utils::collisionDetection(cocos2d::Rect rect1, cocos2d::Rect rect2)
{
	//ֱ�ӵ���cocos2dx�Դ��ľ�����ײ���
	return rect1.intersectsRect(rect2);
}
//Բ����Բ����ײ
bool Utils::collisionDetection(Vec2 center1, float r1, Vec2 center2, float r2)
{
	//����Բ�ľ���
	float dist = center1.getDistance(center2);

	//�ж���Բ�Ƿ��ཻ
	return dist < (r1 + r2);
}
//Բ���������ײ
bool Utils::collisionDetection(cocos2d::Rect rect, Vec2 center, float r)
{
	float widthOfRect = rect.getMaxX() - rect.getMinX();
	float heightOfRect = rect.getMaxY() - rect.getMinY();
	Rect rect1(rect.getMinX() - r, rect.getMinY(), widthOfRect + 2 * r, heightOfRect);
	Rect rect2(rect.getMinX(), rect.getMinY() - r, widthOfRect, heightOfRect + 2 * r);
	if (rect1.containsPoint(center) || rect2.containsPoint(center))
		return true;
	float d1 = center.distance(Vec2(rect.getMinX(), rect.getMinY()));//����
	float d2 = center.distance(Vec2(rect.getMinX(), rect.getMaxY()));//����
	float d3 = center.distance(Vec2(rect.getMaxX(), rect.getMinY()));//����
	float d4 = center.distance(Vec2(rect.getMaxX(), rect.getMaxY()));//����
	if (d1 < r || d2 < r || d3 < r || d4 < r)
		return true;
	return false;
}
//Բ����������ײ
bool Utils::collisionDetection(Vec2 point1, Vec2 point2, Vec2 center, float r)
{
	float d1 = point1.getDistance(center);
	float d2 = point2.getDistance(center);
	float d3 = point1.getDistance(point2);
	if (d1 <= r || d2 <= r || d3 == d1 + d2)
	{
		return true;
	}
	float p = 0.5*(d1 + d2 + d3);
	float x = 2 * sqrt(p*(p - d1)*(p - d2)*(p - d3)) / d3;
	//float x = ((d3*d1 - d2)*d2) / (d1*d1);
	if (x <= r)
	{
		return true;
	}
	return false;
}
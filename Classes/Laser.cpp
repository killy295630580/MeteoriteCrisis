#include "Laser.h"
#include "PlayLayer.h"
USING_NS_CC;

Laser::Laser()
{
	speed = 10;
	isEffective = true;
	tobeDelete = false;
}
Laser::~Laser()
{
}
Laser* Laser::create(Type _type)
{
	Laser *laser = new Laser();
	if (laser && laser->init(_type))
	{
		laser->autorelease();
		return laser;
	}
	else
	{
		delete laser;
		laser = NULL;
		return NULL;
	}
}
bool Laser::init(Type _type)
{
	if (!Node::init())
	{
		return false;
	}
	playLayer = (PlayLayer*)this->getParent();
	createLaser(type = _type);
	this->setScale(0.5f);
	addChild(laserbeam);
	return true;
}
void Laser::createLaser(Type type)
{
	switch (type)
	{
	case Small:
		laserbeam = Sprite::createWithSpriteFrameName("laserbeam_blue.png");
		mainSize = laserbeam->getContentSize()*0.5;
		r = mainSize.height/2;
		center = Vec2(mainSize.width - r , r);
		rect = Rect(mainSize.width - 2*r, 0, mainSize.width, mainSize.height);
		power = 3;
		break;
	case Big:
		laserbeam = Sprite::createWithSpriteFrameName("laserbeam_blue_1024.png");
		mainSize = laserbeam->getContentSize()*0.5;
		r = 0;
		center = Vec2::ZERO;
		rect = Rect(0, 2, mainSize.width, mainSize.height - 2);
		power = 20;
		break;
	}
}

bool Laser::getEffective()
{
	return isEffective;
}
void Laser::setEffective(bool _isEffective)
{
	isEffective = _isEffective;
}
float Laser::getSpeed()
{
	return speed;
}
void Laser::setSpeed(int _speed)
{
	speed = _speed;
}
int Laser::getShape()
{
	switch (this->type)
	{
	case Type::Big :
		return PlayLayer::MyRect;
	case Type::Small:
		return PlayLayer::MyCircle;
	default:
		return -1;
	}
	
}
Rect Laser::getRect()
{
	return rect;
}

float Laser::getR()
{
	return r;
}
Vec2 Laser::getCenter()
{
	return this->convertToWorldSpace(center);
}

void Laser::setAnchorPoint(cocos2d::Vec2 anchorPoint)
{
	laserbeam->setAnchorPoint(anchorPoint);
}
void Laser::changeLength(float scale)
{
	this->setScaleX(scale);
	rect.setRect(0, 2, mainSize.width*scale, mainSize.height - 2);
}
void Laser::deleteMe()
{
	tobeDelete = true;
}
bool Laser::checkDelete()
{
	return tobeDelete;
}
int Laser::getPower()
{
	return power;
}

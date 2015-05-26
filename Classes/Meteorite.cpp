#include "Meteorite.h"
#include "PlayLayer.h"
#include "Utils.h"

USING_NS_CC;

Meteorite::Meteorite()
{
	float ss[] = { 0, 1.0f, 1.3f, 2.3f, 3.0f, 3.5f, 4.0f };
	int ls[] = { 0, 1, 3, 5, 7, 12, 18 };
	float sR[] = { 0, 1.0f / 8, 1.0f / 6, 1.0f / 4, 1.0f / 2, 2.0f / 3, 1.0f };
	for (int i = 0; i < 7; ++i)
	{
		speeds[i] = ss[i];
		lifes[i] = ls[i];
		scaleRate[i] = sR[i];
	}
	isCrushed = false;
}

Meteorite::~Meteorite()
{
}

Meteorite* Meteorite::create(MSize _mSize)
{
	Meteorite* meteorite = new Meteorite();
	if (meteorite && meteorite->init(_mSize))
	{
		meteorite->autorelease();
		return meteorite;
	}
	else
	{
		delete meteorite;
		meteorite = NULL;
		return NULL;
	}
}
bool Meteorite::init(MSize _mSize)
{
	if (!Node::init())
	{
		return false;
	}
	mSize = _mSize;
	float d = 0;
	int type = 0;
	switch (mSize)
	{
	case Big: // 可分裂 4 * 1						-- 加快0.1  
		for (int i = 0; i < 4;++i)
		{
			Meteorite* _m = Meteorite::create(MSize::Tiny);
			_m->setTag(i);
			childs.pushBack(_m);
		}
		break;
	case Huge://可分裂 4 * 2 ,6 * 1					-- 加快0.2
		type = Utils::getInstance()->getRandInt(1, 2);
		switch (type)
		{
		case MSize::Tiny:
			for (int i = 2; i < 8; ++i)
			{
				Meteorite* _m = Meteorite::create(MSize::Tiny);
				_m->setTag(i);
				childs.pushBack(_m);
			}
			break;
		case MSize::Small:
			for (int i = 0; i < 4; ++i)
			{
				Meteorite* _m = Meteorite::create(MSize::Small);
				_m->setTag(i);
				childs.pushBack(_m);
			}
			break;
		}
		break;
	case Super://可分裂 4 * 3, 6 * 2 , 8 * 1		-- 加快0.4
		type = Utils::getInstance()->getRandInt(1, 3);
		switch (type)
		{
		case MSize::Tiny:
			for (int i = 0; i < 8; ++i)
			{
				Meteorite* _m = Meteorite::create(MSize::Tiny);
				_m->setTag(i);
				childs.pushBack(_m);
			}
			break;
		case MSize::Small:
			for (int i = 2; i < 8; ++i)
			{
				Meteorite* _m = Meteorite::create(MSize::Small);
				_m->setTag(i);
				childs.pushBack(_m);
			}
			break;
		case MSize::Medium:
			for (int i = 0; i < 4; ++i)
			{
				Meteorite* _m = Meteorite::create(MSize::Medium);
				_m->setTag(i);
				childs.pushBack(_m);
			}
			break;
		}
		break;
	}
	d = sqrt(scaleRate[mSize]);
	speed = speeds[mSize];
	maxLife = lifes[mSize];
	life = lifes[mSize];
	mainSprite = Sprite::createWithSpriteFrameName("meteorite.png");
	mainSprite->setScale(d);
	mainSprite->setAnchorPoint(Vec2(0.5, 0.5));
	r = (mainSprite->getContentSize().height / 2 - 5)*d;
	this->setContentSize(Size(r, r));
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(mainSprite);
	mainSprite->setPosition(r / 2, r / 2);

	return true;
}
Meteorite* Meteorite::create3()
{
	int type = Utils::getInstance()->getRandInt(1, 3);
	return Meteorite::create(MSize(MSize::nothing + type));
}
Meteorite* Meteorite::create4()
{
	int type = Utils::getInstance()->getRandInt(1, 4);
	return Meteorite::create(MSize(MSize::nothing + type));
}
Meteorite* Meteorite::create5()
{
	int type = Utils::getInstance()->getRandInt(2, 5);
	return Meteorite::create(MSize(MSize::nothing + type));
}
Meteorite* Meteorite::create6()
{
	int type = Utils::getInstance()->getRandInt(3, 6);
	return Meteorite::create(MSize(MSize::nothing + type));
}
int Meteorite::getShape()
{
	return PlayLayer::MyCircle;
}
float Meteorite::getR()
{
	return r;
}
Vec2 Meteorite::getCenter()
{
	return this->convertToWorldSpace(mainSprite->getPosition());
}
float Meteorite::getSpeed()
{
	return speed;
}
Meteorite::MSize Meteorite::getMSize()
{
	return mSize;
}
void Meteorite::deleteMe()
{
	this->isCrushed = true;
}
bool Meteorite::checkDelete()
{
	return isCrushed;
}
int Meteorite::getMaxLife()
{
	return maxLife;
}
int Meteorite::getLife()
{
	return life;
}
bool Meteorite::setLife(int _life)
{
	life = _life;
	if (life <= 0)
	{
		life = 0;
		//auto playLayer = (PlayLayer*)this->getParent();
		//playLayer->crushTheMeteorite(this);
		return false;
	}
	return true;
}
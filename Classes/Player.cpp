#include "Player.h"
#include "PlayLayer.h"

USING_NS_CC;

Player::Player()
{
	isCrushed = false;
}
Player::~Player()
{
}

bool Player::init()
{
	if (!Node::init())
	{
		return false;
	}
	mainSprite = Sprite::createWithSpriteFrameName("SpaceFlier4.png");
	this->setScale(0.5);
	auto size = mainSprite->getContentSize();
	size = size * 0.5;
	mainSize = Size(size.width*0.7, size.height);
	this->setContentSize(mainSize);
	rect = Rect(size.width - size.width*0.7, 0, mainSize.width,mainSize.height);
	r = size.height / 2;
	center = Vec2(size.width - r ,r);
	Vector<SpriteFrame*> vec_sf;
	auto cache = SpriteFrameCache::getInstance();
	SpriteFrame* sf = NULL;
	for (int i = 1; i <= 5; ++i)
	{
		sf = cache->getSpriteFrameByName(StringUtils::format("SpaceFlier%d.png", i));
		vec_sf.pushBack(sf);
	}
	Animation* animation = Animation::createWithSpriteFrames(vec_sf, 0.05f, -1);
	auto action = Animate::create(animation);
	mainSprite->runAction(CCRepeatForever::create(
						Sequence::create(action,action->reverse(),NULL)));
	addChild(mainSprite);
	return true;
}

Size Player::getContentSize()
{
	return mainSize;
}


Rect Player::getBoundingBox()
{
	auto size = mainSprite->getContentSize();
	Rect rect(0, 0, size.width, size.height);
	return RectApplyAffineTransform(rect, getNodeToParentAffineTransform());
}

void Player::fire()
{

}
void Player::beCrushed()
{
	isCrushed = true;
}
void Player::reset()
{
	isCrushed = false;
}
bool Player::checkCrushed()
{
	return isCrushed;
}

int Player::getShape()
{
	return PlayLayer::MyCircle;
}

float Player::getR()
{
	return r;
}
Vec2 Player::getCenter()
{
	return this->convertToWorldSpace(center);
}



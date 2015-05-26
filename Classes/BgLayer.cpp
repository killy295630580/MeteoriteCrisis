#include "GameScene.h"
#include "PlayLayer.h"
#include "BgLayer.h"
USING_NS_CC;

BgLayer::BgLayer()
{
	finishParticle = NULL;
}

BgLayer::~BgLayer()
{
}
// on "init" you need to initialize your instance
bool BgLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//label
	auto label = Label::createWithTTF("Use Time : 0", "fonts/Marker Felt.ttf", 16,
					Size::ZERO, cocos2d::TextHAlignment::CENTER);
	label->setPosition(Vec2(origin.x + visibleSize.width - 55,
		origin.y + visibleSize.height - 20));
	label->setGlobalZOrder(100);
	this->addChild(label, 1, TimeTag);

	//first png
	sprite1 = Sprite::createWithSpriteFrameName("bg01-1.png");
	auto size = sprite1->getContentSize();
	sprite1->setScaleX(visibleSize.width / size.width);
	sprite1->setScaleY(visibleSize.height / size.height);
	sprite1->setAnchorPoint(Vec2(.5,.5));
	sprite1->setPosition(visibleSize.width*0.5, visibleSize.height / 2);
	this->addChild(sprite1, 0);
	//second png
	auto spSize = sprite1->getContentSize();
	sprite2 = Sprite::createWithSpriteFrameName("bg01-1.png"); 
	size = sprite2->getContentSize();
	sprite2->setScaleX(visibleSize.width / size.width);
	sprite2->setScaleY(visibleSize.height / size.height);
	sprite2->setFlippedX(true);
	sprite2->setAnchorPoint(Vec2(.5, .5));
	sprite2->setPosition(visibleSize.width * 1.49,visibleSize.height/2);
	this->addChild(sprite2, 0);
	auto bgProgress = Sprite::createWithSpriteFrameName("progress_back.png");
	bgProgress->setPosition(0, visibleSize.height);
	bgProgress->setGlobalZOrder(progressGZOrder);
	bgProgress->setScale(ProgressTimerScale);
	bgProgress->setAnchorPoint(Vec2(0, 1));
	bgProgress->setTag(ProgressBgtag);
	this->addChild(bgProgress);
	ProgressTimer* pt = ProgressTimer::create(Sprite::createWithSpriteFrameName("progress_front.png"));
	pt->setPosition(0, visibleSize.height);
	pt->setAnchorPoint(Vec2(0, 1));
	pt->setTag(ProgressTag);
	pt->setScale(ProgressTimerScale);
	pt->setGlobalZOrder(progressGZOrder);

	pt->setPercentage(0);
	pt->setType(ProgressTimer::Type::BAR);

	pt->setMidpoint(Vec2(0, 0));
	pt->setBarChangeRate(Vec2(1, 0));
	this->addChild(pt);
	this->scheduleUpdate();
	return true;
}



void BgLayer::update(float delta)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	int posX1 = sprite1->getPositionX();
	if (posX1 <= -visibleSize.width * 0.48)
	{
		posX1 = visibleSize.width * 1.5 ;
	}
	posX1 -= speed;
	sprite1->setPositionX(posX1);
	
	int posX2 = sprite2->getPositionX();
	if (posX2 <= -visibleSize.width *0.48)
	{
		posX2 = visibleSize.width * 1.5;
	}
	posX2 -= speed;
	sprite2->setPositionX(posX2);
}

void BgLayer::updateProgress(int addPower)
{
	ProgressTimer *ct = (ProgressTimer*)getChildByTag(ProgressTag);
	Vec2 pos = ct->getPosition();
	Size size = ct->getContentSize();
	size = size * ProgressTimerScale;
	int num = ct->getPercentage()+addPower;
	ct->setPercentage(num);
	if (num >= 100)
	{
		num = 100;
		if (getChildByTag(FinishTag))
		{
			removeChildByTag(FinishTag);
		}
		Vec2 pos2(pos.x + size.width, pos.y - 5);
		finishParticle = ParticleSystemQuad::create("particle/progress_finish.plist");
		finishParticle->retain();
		finishParticle->setPosition(pos2);
		finishParticle->setTag(FinishTag);
		finishParticle->setGlobalZOrder(progressGZOrder);;
		addChild(finishParticle);
		auto playLayer = (PlayLayer*)(this->getParent()->getChildByTag(GameScene::PLAY_TAG));
		playLayer->setPowerFull(true);
	}
}
void BgLayer::resetProgress()
{
	ProgressTimer *ct = (ProgressTimer*)getChildByTag(ProgressTag);
	ct->setPercentage(0);
	this->removeChildByTag(FinishTag);
	auto playLayer = (PlayLayer*)(this->getParent()->getChildByTag(GameScene::PLAY_TAG));
}

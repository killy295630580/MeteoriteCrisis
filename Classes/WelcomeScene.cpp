#include "WelcomeScene.h"
#include "BgLayer.h"
#include "MenuLayer.h"
#include "GameScene.h"
#include "HowToPlay.h"

USING_NS_CC;

WelcomeScene::WelcomeScene()
{
}


WelcomeScene::~WelcomeScene()
{
}
Scene* WelcomeScene::createScene()
{
	auto scene = Scene::create();
	auto layer = WelcomeScene::create();
	scene->addChild(layer);
	return scene;
}
bool WelcomeScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/all_pic.plist");

	bgLayer = BgLayer::create();
	bgLayer->removeChildByTag(BgLayer::TimeTag);
	bgLayer->removeChildByTag(BgLayer::ProgressTag);
	bgLayer->removeChildByTag(BgLayer::ProgressBgtag);
	this->addChild(bgLayer);

	menuLayer = MenuLayer::create();
	this->addChild(menuLayer);

	// 标题
	auto titleLabel = Label::createWithTTF("Meteorite Crisis", "fonts/Marker Felt.ttf", 60);
	titleLabel->setPosition(visibleSize.width / 2, visibleSize.height * 0.8);
	addChild(titleLabel);

	//menu play
	auto one_man = MenuItemImage::create();
	auto normal1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("one_man_normal.png");
	auto selected1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("one_man_clicked.png");
	one_man->setNormalSpriteFrame(normal1);
	one_man->setSelectedSpriteFrame(selected1);
	one_man->setCallback([](Ref*){
		auto s = GameScene::createScene();
		float t = 0.5f;
		struct timeval psv;
		gettimeofday(&psv, NULL);
		unsigned rand_seed = (unsigned)(psv.tv_sec + psv.tv_usec);    //转化为毫秒 
		srand(rand_seed);
		float choice = rand_0_1();
		if (choice < 0.25)
		{
			Director::getInstance()->replaceScene(TransitionFlipY::create(t, s));
		}
		else if (choice >= 0.25 && choice < 0.5)
		{
			Director::getInstance()->replaceScene(TransitionFlipY::create(t, s));
		}
		else if (choice >= 0.5 && choice < 0.75)
		{
			Director::getInstance()->replaceScene(TransitionProgressRadialCCW::create(t, s));
		}
		else if (choice >= 0.75 && choice < 1.0)
		{
			Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(t, s));
		}
	});
	one_man->setScale(0.5f);
	//menu how to play
	auto howToPlay = MenuItemImage::create();
	auto normal2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("howtoplay_normal.png");
	auto selected2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("howtoplay_clicked.png");
	howToPlay->setNormalSpriteFrame(normal2);
	howToPlay->setSelectedSpriteFrame(selected2);
	howToPlay->setCallback([&,this](Ref*){
		auto s = HowToPlay::createScene();
		float t = 0.5f;
		struct timeval psv;
		gettimeofday(&psv, NULL);
		unsigned rand_seed = (unsigned)(psv.tv_sec + psv.tv_usec);    //转化为毫秒 
		srand(rand_seed);
		float choice = rand_0_1();
		if (choice < 0.25)
		{
			Director::getInstance()->replaceScene(TransitionFlipY::create(t, s));
		}
		else if (choice >= 0.25 && choice < 0.5)
		{
			Director::getInstance()->replaceScene(TransitionFlipY::create(t, s));
		}
		else if (choice >= 0.5 && choice < 0.75)
		{
			Director::getInstance()->replaceScene(TransitionProgressRadialCCW::create(t, s));
		}
		else if (choice >= 0.75 && choice < 1.0)
		{
			Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(t, s));
		}
	});
	howToPlay->setScale(0.5f);
	howToPlay->setPositionY(- howToPlay->getContentSize().height/2 - 5);
	auto menu = Menu::create(one_man, howToPlay, NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height * 0.5);
	menu->setAnchorPoint(Vec2(0.5,1));
	
	addChild(menu);

	// 主角模型
	auto player = Sprite::createWithSpriteFrameName("SpaceFlier4.png");
	player->setScale(0.5);
	player->setPosition(visibleSize.width/2, visibleSize.height * 0.65);
	auto cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> vec_sf;
	SpriteFrame* sf = NULL;
	for (int i = 1; i <= 5; ++i)
	{
		sf = cache->getSpriteFrameByName(StringUtils::format("SpaceFlier%d.png", i));
		vec_sf.pushBack(sf);
	}
	Animation* animation = Animation::createWithSpriteFrames(vec_sf, 0.05f, -1);
	auto action = Animate::create(animation);
	player->runAction(CCRepeatForever::create(
		Sequence::create(action, action->reverse(), NULL)));
	addChild(player);

	// 最高分
	// 最高分标题
	auto highScoreTitle = Label::createWithTTF("BestScore:", "fonts/Marker Felt.ttf", 25);
	highScoreTitle->setPosition(visibleSize.width * 0.48, visibleSize.height * 0.2);
	this->addChild(highScoreTitle);
	// 最高分
	auto bestScore = UserDefault::getInstance()->getIntegerForKey("highScore");
	auto highScore = Label::createWithTTF(
		__String::createWithFormat("%i", bestScore)->getCString(),
		"fonts/Marker Felt.ttf",
		25);
	highScore->setPosition(visibleSize.width * 0.6 , visibleSize.height * 0.2);
	this->addChild(highScore);

	return true;
}

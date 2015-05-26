#include "HowToPlay.h"
#include "WelcomeScene.h"
#include "GameScene.h"
USING_NS_CC;

HowToPlay::HowToPlay()
{
}


HowToPlay::~HowToPlay()
{
}

Scene* HowToPlay::createScene()
{
	auto scene = Scene::create();
	auto layer = HowToPlay::create();
	scene->addChild(layer);
	return scene;
}
bool HowToPlay::init()
{
	if (!LayerColor::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto howtoplay = Sprite::create("image/howtoplay.png");
	auto size = howtoplay->getContentSize();
	howtoplay->setScaleX(visibleSize.width / size.width);
	howtoplay->setScaleY(visibleSize.height / size.height);
	howtoplay->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	howtoplay->setAnchorPoint(Vec2(.5,.5));
	addChild(howtoplay);
	auto menuItemPlay = MenuItemLabel::create(Label::createWithTTF("Play", "fonts/Marker Felt.ttf", 30)
		, [this](Ref* r){
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
	menuItemPlay->setPosition(visibleSize.width *0.30, visibleSize.height * 0.10);
	auto menuItemBack = MenuItemLabel::create(Label::createWithTTF("MainMenu", "fonts/Marker Felt.ttf", 30)
		, [this](Ref* r){
		auto s = WelcomeScene::createScene();
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
	menuItemBack->setPosition(visibleSize.width *0.70, visibleSize.height * 0.10);
	auto menu = Menu::create(menuItemPlay, menuItemBack, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);
	return true;
}
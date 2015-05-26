#include "GameOverScene.h"
#include "WelcomeScene.h"
#include "GameScene.h"
#include "MenuLayer.h"

USING_NS_CC;


GameOverScene::GameOverScene()
{
}
GameOverScene::~GameOverScene()
{
}

Scene* GameOverScene::createScene(int _count)
{
	auto scene = Scene::create();
	auto layer = GameOverScene::create(_count);
	scene->addChild(layer);
	return scene;
}
GameOverScene* GameOverScene::create(int _count)
{ 
	GameOverScene *pRet = new GameOverScene();
	if (pRet && pRet->init(_count))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool GameOverScene::init(int _count)
{
	if (!Layer::init())
	{
		return false;
	}
	useTime = _count;
	UserDefault* ud = UserDefault::getInstance();
	bestScore = ud->getIntegerForKey("highScore");
	if (bestScore < _count)
	{
		bestScore = _count;
		ud->setIntegerForKey("highScore", _count);
		ud->flush();
	}
	showResult();
	return true;
}

void GameOverScene::showResult()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto layerResult = LayerColor::create(Color4B(180, 170, 160, 220));
	// 关闭
	menuLayer = MenuLayer::create();
	this->addChild(menuLayer);
	// 标题
	auto titleLabel = Label::createWithTTF("Game Over!", "fonts/Marker Felt.ttf", 45);
	titleLabel->setPosition(visibleSize.width / 2, visibleSize.height * 0.9);
	layerResult->addChild(titleLabel);
	// 成绩标题
	auto gameScoreTitle = Label::createWithTTF("Score", "fonts/Marker Felt.ttf", 35);
	gameScoreTitle->setPosition(visibleSize.width / 2, visibleSize.height * 0.75);
	layerResult->addChild(gameScoreTitle);
	// 成绩
	auto gameScore = Label::createWithTTF(
		__String::createWithFormat("%i", useTime)->getCString(),
		"fonts/Marker Felt.ttf",
		40);
	gameScore->setPosition(visibleSize.width / 2, visibleSize.height * 0.62);
	layerResult->addChild(gameScore);
	// 最高分标题
	auto highScoreTitle = Label::createWithTTF("High Score", "fonts/Marker Felt.ttf", 35);
	highScoreTitle->setPosition(visibleSize.width / 2, visibleSize.height * 0.49);
	layerResult->addChild(highScoreTitle);
	// 最高分
	auto highScore = Label::createWithTTF(
		__String::createWithFormat("%i", bestScore)->getCString(),
		"fonts/Marker Felt.ttf",
		40);
	highScore->setPosition(visibleSize.width / 2, visibleSize.height * 0.36);
	layerResult->addChild(highScore);
	//菜单
	// 重置游戏
	auto menuItemReset = MenuItemLabel::create(Label::createWithTTF("Restart", "fonts/Marker Felt.ttf", 35)
		, [this](Ref* r){
			auto gameScene = GameScene::createScene();
			Director::getInstance()->replaceScene(gameScene);
	});
	menuItemReset->setPosition(visibleSize.width / 2, visibleSize.height * 0.23);
	// 返回开始界面
	auto menuItemBack = MenuItemLabel::create(Label::createWithTTF("MainMenu", "fonts/Marker Felt.ttf", 35)
		, [this](Ref* r){
			auto welcomeScene = WelcomeScene::createScene();
			Director::getInstance()->replaceScene(welcomeScene);
		});
	menuItemBack->setPosition(visibleSize.width / 2, visibleSize.height * 0.10);
	// 菜单
	auto menu = Menu::create(menuItemReset, menuItemBack, NULL);
	menu->setPosition(Vec2::ZERO);

	layerResult->addChild(menu);

	this->addChild(layerResult, 1000, 101);
}

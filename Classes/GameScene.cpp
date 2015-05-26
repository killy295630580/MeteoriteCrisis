#include "GameScene.h"
#include "PlayLayer.h"
#include "BgLayer.h"
#include "MenuLayer.h"
#include "Player.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	count = 0;
	isGameOver = false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/all_pic.plist");
	

	bgLayer = BgLayer::create();
	this->addChild(bgLayer, 0, BG_TAG);

	playLayer = PlayLayer::create();
	this->addChild(playLayer, 10, PLAY_TAG);

	menuLayer = MenuLayer::create();
	this->addChild(menuLayer, 20, MENU_TAG);

	this->schedule(schedule_selector(GameScene::time_counting), 1.0f);
	this->scheduleUpdate();

    return true;
}

int GameScene::getCount()
{
	return count;
}

void GameScene::setGameOver()
{
	isGameOver = true;
}

void GameScene::time_counting(float dt)
{
	count++;
	Label* label = (Label*)bgLayer->getChildByTag(BgLayer::TimeTag);
	label->setString(StringUtils::format("Use Time : %d", count));
}

void GameScene::update(float delta)
{
	if (isGameOver)
	{
		this->stopAllActions();
		this->unscheduleAllCallbacks();
		showScore();
	}
}
void GameScene::resetGame()
{
	count = 0;
	isGameOver = false;
	playLayer->resetGame();
}

void GameScene::showScore()
{
	auto gameover = GameOverScene::createScene(count);
	Director::getInstance()->replaceScene(gameover);

}

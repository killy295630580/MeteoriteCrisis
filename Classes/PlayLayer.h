#ifndef __PLAY_LAYER_H__
#define __PLAY_LAYER_H__

#include "cocos2d.h"
#include "BgLayer.h"
#include "Utils.h"
#include <ctime>

class GameScene;
class Meteorite;
class Laser;
class Player;

class PlayLayer : public cocos2d::Layer
{
public:
	enum Tags
	{
		HeroTag = 1,
		SuperlaserTag = 10,
	};
	enum ShapeTpye
	{
		MyCircle = 1,
		MyRect = 2,
	};
	PlayLayer();
	~PlayLayer();
	virtual bool init();
	CREATE_FUNC(PlayLayer);
	cocos2d::Vec2 getEndPoint(cocos2d::Vec2, cocos2d::Vec2, cocos2d::Size);
	void update(float delta);
	void updatePerSecond(float delta);
	void createMeteorites(float delta);
	cocos2d::Vector<Meteorite*> crushTheMeteorite(Meteorite* meteorite);
	void createLasers(float delta);
	void gameOver();
	void resetGame();
	void setPowerFull(bool);
	void setAddPower(int);
	int getAddPower();
public:
	cocos2d::Vector<Meteorite*> meteorites;
	cocos2d::Vector<Laser*> lasers;
private:
	const float speed = 150.0f;
	const float doubleClickedTime = 500.0f;
	const float touchInLeft = 0.1f;
	const int touchPrecision = 10;
	float createMeteoriteTime;
	Player *hero;
	bool including;
	bool isFirstClick;
	bool isDoubleClick;
	bool isInRight;
	bool powerFull;
	int addPower;
	Laser *superlaser;
	cocos2d::Vec2 startPoint;
	cocos2d::Vec2 endPoint;
	cocos2d::Vec2 touchPoint;
	cocos2d::DrawNode* dn;
	long start_time;
	long end_time;
	GameScene* parent;
	cocos2d::EventListenerTouchOneByOne *_touchListener;
	std::function<bool(cocos2d::Touch*, cocos2d::Event*)> touchBegin;
	std::function<void(cocos2d::Touch*, cocos2d::Event*)> touchMoved;
	std::function<void(cocos2d::Touch*, cocos2d::Event*)> touchEnded;
	BgLayer *bgLayer;
	int count;
	int superlaserTime;
};

#endif // __PLAY_LAYER_H__

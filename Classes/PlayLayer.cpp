#include "GameScene.h"
#include "PlayLayer.h"
#include "Player.h"
#include "Laser.h"
#include "Meteorite.h"

USING_NS_CC;

PlayLayer::PlayLayer()
{
	including = false;
	createMeteoriteTime = 0.4f;
	addPower = 1;
	count = 0;
	powerFull = false;
	superlaserTime = 3;
	isDoubleClick = false;
	_touchEnabled = true;
	_touchListener = nullptr;
}
PlayLayer::~PlayLayer()
{}

bool PlayLayer::init()
{
	if (!Layer::create())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin(); 
	isFirstClick = false;
	isDoubleClick = false;
	//
	dn = DrawNode::create();
	addChild(dn);
	dn->drawLine(Vec2(visibleSize.width * touchInLeft, visibleSize.height),
		Vec2(visibleSize.width * touchInLeft, 0), Color4F::RED);
	dn->runAction(Hide::create());
	this->schedule([this](float){
		auto blink = Blink::create(0.5f, 3);
		this->dn->runAction(Sequence::create(Show::create(), blink, Hide::create(), DelayTime::create(1.5f), NULL));
	},1.0f,"drawline");
	//hero
	hero = Player::create();
	Size sizeOfHero = hero->getContentSize();
	hero->setAnchorPoint(Vec2(1,0.5));
	hero->setPosition(sizeOfHero.width, visibleSize.height / 2);
	this->addChild(hero, 10, HeroTag);
	touchBegin = [visibleSize, this](Touch* touch, Event *unused_event)
	{
		Vec2 location = touch->getLocation();
		if (location.x > visibleSize.width * touchInLeft)
		{
			isInRight = true;
			if (isFirstClick)
			{
				double totalTime;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				struct timeval now;
				gettimeofday(&now, NULL);
				end_time = now.tv_usec / 1000;
				struct tm *tm;
				time_t tp = now.tv_sec;
				tm = localtime(&tp);
				end_time += tm->tm_min*60000 +tm->tm_sec*1000;
				totalTime = end_time - start_time;
#endif
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
				end_time = clock();
				totalTime = difftime(end_time, start_time);
#endif
				if (totalTime < doubleClickedTime)
				{
					isDoubleClick = true;
					log("isDoubleClick");
					if (powerFull)
					{
						log("isDoubleClick power");
						parent = (GameScene*)this->getParent();
						bgLayer = (BgLayer*)parent->getChildByTag(GameScene::BG_TAG);
						hero->stopActionByTag(10);
						startPoint = Vec2(hero->getPosition().x + 5, hero->getPosition().y - 7);
						touchPoint = location;
						float disX = touchPoint.x - startPoint.x;
						float disY = touchPoint.y - startPoint.y;
						float angle1 = -atan2(disY, disX);//y-x
						endPoint = getEndPoint(startPoint, touchPoint, visibleSize);
						float distance = startPoint.getDistance(endPoint);
						superlaser = Laser::create(Laser::Big);
						superlaser->changeLength(distance / 1024);
						superlaser->setRotation(angle1 * 180 / 3.14);
						superlaser->setAnchorPoint(Vec2(0, 0.5));
						superlaser->setPosition(startPoint);
						superlaser->setTag(SuperlaserTag);
						addChild(superlaser);
						bgLayer->resetProgress();
						this->unschedule(schedule_selector(PlayLayer::createLasers));
						count = 0;
						this->schedule(schedule_selector(PlayLayer::updatePerSecond), 1.0f);
					}

				}
				else
				{
					isFirstClick = false;
				}
			}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			struct timeval now;
			gettimeofday(&now, NULL);
			start_time = now.tv_usec / 1000;
			struct tm *tm;
			time_t tp = now.tv_sec;
			tm = localtime(&tp);
			start_time += tm->tm_min * 60000 + tm->tm_sec * 1000;
#endif
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
			start_time = clock();
#endif
			return true;
		}
		isInRight = false;
		int heroY = hero->getPositionY();
		if (location.y > (heroY - touchPrecision) && location.y < (heroY + touchPrecision))
		{
			including = true;
		}
		//if (hero->getBoundingBox().containsPoint(location))
		//{
		//	including = true;
		//}
		return true;
	};
	touchMoved = [visibleSize, this](Touch* touch, Event *unused_event)
	{
		auto location = touch->getLocation();
		if (isInRight && isDoubleClick)
		{
			if (location.x < hero->getPositionX() + 5)
			{
				if (getChildByTag(SuperlaserTag))
				{
					this->schedule(schedule_selector(PlayLayer::createLasers), 0.1f);
					this->unschedule(schedule_selector(PlayLayer::updatePerSecond));
					isDoubleClick = false;
					removeChildByTag(SuperlaserTag);
					superlaser = nullptr;
					return;
				}
			}
			if (getChildByTag(SuperlaserTag))
			{
				touchPoint = location;
				float disX = touchPoint.x - startPoint.x;
				float disY = touchPoint.y - startPoint.y;
				float angle1 = -atan2(disY, disX);//y-x
				endPoint = getEndPoint(startPoint, touchPoint, visibleSize);
				float distance = startPoint.getDistance(endPoint);
				superlaser->changeLength(distance / 1024);
				superlaser->setRotation(angle1 * 180 / 3.14);
			}
		}
		else{
			if (including)
			{
				hero->setPositionY(location.y);
			}
		}

	};
	touchEnded = [visibleSize, this](Touch* touch, Event *unused_event)
	{
		Vec2 location = touch->getLocation();
		if (isInRight)
		{
			if (!isFirstClick)//the first ended
			{
				isFirstClick = true;
			}
			else //the second ended
			{
				isFirstClick = false;
				isDoubleClick = false;
				if (getChildByTag(SuperlaserTag))
				{
					this->schedule(schedule_selector(PlayLayer::createLasers), 0.1f);
					this->unschedule(schedule_selector(PlayLayer::updatePerSecond));
					removeChildByTag(SuperlaserTag);
					this->setPowerFull(false);
				}
			}
			isInRight = false;
		}
		else{
			if (location.y < 0)
			{
				location.y = 0;
			}
			if (location.y > visibleSize.height)
			{
				location.y = visibleSize.height;
			}
			hero->stopActionByTag(10);
			float duration = fabs(location.y - hero->getPositionY()) / this->speed;
			auto moveTo = MoveTo::create(duration, Vec2(hero->getPositionX(), location.y));
			moveTo->setTag(10);
			hero->runAction(moveTo);
			including = false;
		}
	};
	
	_touchListener = EventListenerTouchOneByOne::create();
	_touchListener->onTouchBegan = touchBegin;
	_touchListener->onTouchMoved = touchMoved;
	_touchListener->onTouchEnded = touchEnded;
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

	this->schedule(schedule_selector(PlayLayer::createMeteorites),createMeteoriteTime);
	this->schedule(schedule_selector(PlayLayer::createLasers), 0.1f);
	this->scheduleUpdate();
	return true;
}

Vec2 PlayLayer::getEndPoint(Vec2 startPoint, Vec2 touchPoint, Size visibleSize)
{
	float startX = startPoint.x;
	float startY = startPoint.y;
	float touchX = touchPoint.x;
	float touchY = touchPoint.y;
	float endX = visibleSize.width;
	float endY = (endX - startX)*(touchY - startY) / (touchX - startX) + startY;
	return Vec2(endX,endY);
}


void PlayLayer::createMeteorites(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	parent = (GameScene*)this->getParent();
	int count = parent->getCount();
	Meteorite* meteorite;
	if(count >= 80)
	{
		meteorite = Meteorite::create3();
		meteorite = Meteorite::create4();
		meteorite = Meteorite::create5();
		meteorite = Meteorite::create5();
		meteorite = Meteorite::create6();
		if (3 > Utils::getInstance()->getRandInt(1, 50))// 1/25
		{
			createMeteoriteTime /= 3;
		}
	}
	else if (count < 80 && count >= 50)
	{
		meteorite = Meteorite::create3();
		meteorite = Meteorite::create4();
		meteorite = Meteorite::create5();
		meteorite = Meteorite::create5();
		meteorite = Meteorite::create5();
		if (3 > Utils::getInstance()->getRandInt(1, 40))// 1/20
		{
			createMeteoriteTime /= 3;
		}
	}
	else if (count < 50 && count >= 28)
	{
		meteorite = Meteorite::create3();
		meteorite = Meteorite::create3();
		meteorite = Meteorite::create4();
		meteorite = Meteorite::create4();
		meteorite = Meteorite::create4();
		if (3 > Utils::getInstance()->getRandInt(1, 25))// 2/25
		{
			createMeteoriteTime /= 3;
		}
	}
	else
	{
		meteorite = Meteorite::create3();
		meteorite = Meteorite::create3();
		meteorite = Meteorite::create3();
		meteorite = Meteorite::create3();
		meteorite = Meteorite::create3();
		if (3 > Utils::getInstance()->getRandInt(1, 14))// 1/7
		{
			createMeteoriteTime /= 3;
		}
	}
	
	float r = meteorite->getR();
	int localY = Utils::getInstance()->getRandInt(r, visibleSize.height - r);
	meteorite->setPosition(visibleSize.width - meteorite->getContentSize().width,localY);
	meteorites.pushBack(meteorite);
	addChild(meteorite);
}
Vector<Meteorite*> PlayLayer::crushTheMeteorite(Meteorite* meteorite)
{
	Vector<Meteorite*> tempVec;
	if (meteorite->getMSize() > Meteorite::Medium)
	{
		int countOfChilds = meteorite->childs.size();
		float posX = meteorite->getPositionX();
		float posY = meteorite->getPositionY();
		float r0 = meteorite->getR();
		float r1 = r0 * (sqrt(2.0) / 2.0);
		Vec2 poss[] = {
			Vec2(posX + r0, posY), Vec2(posX - r0, posY),
			Vec2(posX, posY + r0), Vec2(posX, posY - r0),
			Vec2(posX + r1, posY + r1), Vec2(posX - r1, posY + r1),
			Vec2(posX + r1, posY - r1), Vec2(posX - r1, posY - r1) };
		for (auto var : meteorite->childs)
		{
			var->setPosition(poss[var->getTag()]);
			addChild(var);
			tempVec.pushBack(var);
		}
	}
	meteorite->deleteMe();
	auto pos = meteorite->getPosition();
	auto explore = ParticleSystemQuad::create("particle/explode.plist");
	explore->setPosition(pos);
	this->addChild(explore);
	this->removeChild(meteorite);
	return tempVec;
}

void  PlayLayer::createLasers(float delta)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	parent = (GameScene*)this->getParent();
	int count = parent->getCount();
	Laser* l = Laser::create(Laser::Small);
	l->setPosition(hero->getPosition().x + 5, hero->getPosition().y - 7);
	lasers.pushBack(l);
	addChild(l);
}
void PlayLayer::update(float delta)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vector<Meteorite*> tempMeteoriteVec;
	// move the meteorite
	for (Vector<Meteorite*>::iterator it = meteorites.begin();it!=meteorites.end();++it)
	{
		float posX = (*it)->getPositionX();
		if (posX < -(*it)->getContentSize().width / 2)
		{
			this->gameOver();
			for (auto item : crushTheMeteorite(*it))
			{
				tempMeteoriteVec.pushBack(item);
			}
		}
		(*it)->setPositionX(posX - (*it)->getSpeed());
	}
	// move the laser
	for (auto item : lasers)
	{
		if (item->getPositionX() > (visibleSize.width + item->getContentSize().width))
		{
			item->deleteMe();
		}
		item->setPositionX(item->getPositionX() + item->getSpeed());
	}
	// 碰撞检测
	for (auto meteorite : meteorites)
	{
		float rMeteorite = meteorite->getR();
		Vec2 centerMeteorite = meteorite->getCenter();
		float rHero = hero->getR();
		Vec2 centerHero = hero->getCenter();
		if (Utils::getInstance()->collisionDetection(centerMeteorite, rMeteorite, centerHero, rHero))
		{
			for (auto item : crushTheMeteorite(meteorite))
			{
				tempMeteoriteVec.pushBack(item);
			}
			hero->beCrushed();
			this->gameOver();
			break;
		}
		for (auto laser : lasers)
		{
			float rLaser = laser->getR();
			Vec2 centerLaser = laser->getCenter();
			if (Utils::getInstance()->collisionDetection(centerMeteorite, rMeteorite, centerLaser, rLaser))
			{
				if (! meteorite->setLife(meteorite->getLife() - laser->getPower()))
				{
					for (auto item : crushTheMeteorite(meteorite))
					{
						tempMeteoriteVec.pushBack(item);
					}
				}
				laser->deleteMe();
				break;
			}
		}
		auto _superlaser = (Laser*)this->getChildByTag(SuperlaserTag);
		if (_superlaser)
		{
			if (Utils::getInstance()->collisionDetection(_superlaser->getPosition(), endPoint, centerMeteorite, rMeteorite))
			{
				if (!meteorite->setLife(meteorite->getLife() - _superlaser->getPower()))
				{
					for (auto item : crushTheMeteorite(meteorite))
					{
						tempMeteoriteVec.pushBack(item);
					}
				}
				break;
			}
		}
	}
	//clear disabled laser
	for (Vector<Laser*>::iterator it = lasers.begin(); it != lasers.end();)
	{
		auto item = *it;
		if (item->checkDelete())
		{
			this->removeChild(item);
			lasers.eraseObject(item);
			it = lasers.begin();
		}
		else
		{
			++it;
		}
	}
	//Clear disabled meteorites
	for (Vector<Meteorite*>::iterator it = meteorites.begin(); it != meteorites.end();)
	{
		auto item = *it;
		if (item->checkDelete())
		{
			parent = (GameScene*)this->getParent();
			bgLayer = (BgLayer*)parent->getChildByTag(GameScene::BG_TAG);
			int maxlife = item->getMaxLife();
			int addPower = getAddPower();
			bgLayer->updateProgress(maxlife * addPower);
			meteorites.eraseObject(item);
			it = meteorites.begin();
		}
		else
		{
			++it;
		}
	}
	// add child meteorites
	for (auto item:tempMeteoriteVec)
	{
		meteorites.pushBack(item);
	}
}

void PlayLayer::updatePerSecond(float delta)
{
	if (powerFull)
	{
		++count;
		if (count > superlaserTime)
		{
			auto superl = (Laser*)this->getChildByTag(SuperlaserTag);
			if (superl)
			{
				this->schedule(schedule_selector(PlayLayer::createLasers), 0.1f);
				this->unschedule(schedule_selector(PlayLayer::updatePerSecond));
				this->removeChildByTag(SuperlaserTag);
				count = 0;
				this->setPowerFull(false);
			}
		}
	}
}

void PlayLayer::gameOver()
{
	this->unscheduleAllCallbacks();
	parent->setGameOver();
}

void PlayLayer::resetGame()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	meteorites.clear();
	lasers.clear();
	if (getChildByTag(SuperlaserTag))
	{
		removeChildByTag(SuperlaserTag);
	}
	hero->reset();
	Size sizeOfHero = hero->getContentSize();
	hero->setAnchorPoint(Vec2(1, 0.5));
	hero->setPosition(sizeOfHero.width, visibleSize.height / 2);
	this->schedule(schedule_selector(PlayLayer::createMeteorites), createMeteoriteTime);
	this->schedule(schedule_selector(PlayLayer::createLasers), 0.1f);
	this->unschedule(schedule_selector(PlayLayer::updatePerSecond));
	this->scheduleUpdate();
}
void PlayLayer::setPowerFull(bool turn)
{
	powerFull = turn;
}
void PlayLayer::setAddPower(int _addPower)
{
	addPower = _addPower;
}
int PlayLayer::getAddPower()
{
	return addPower;
}

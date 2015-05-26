#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    //auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

  
	
	//this->scheduleUpdate();

	/*
	// mytest
	auto sp1 = Sprite::create("image/laserbeam_blue.png");
	sp1->setScaleX(1);
	auto rect = sp1->getBoundingBox();
	auto sp_body1 = PhysicsBody::createEdgeBox(Size(sp1->getContentSize().width*9, sp1->getContentSize().height*0.7));
	sp1->setPhysicsBody(sp_body1);
	sp1->setPosition(visibleSize.width / 2, visibleSize.height / 6);
	addChild(sp1);*/
	
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/all_pic.plist");
	auto sp2 = Sprite::createWithSpriteFrameName("laserbeam_blue_1024.png");
	auto startPoint = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	auto endPoint = Vec2( visibleSize.width*0.1, visibleSize.height*0.9);
	float distance = startPoint.getDistance(endPoint);
	sp2->setScaleX(distance / 1024);
	sp2->setAnchorPoint(Vec2(0,0.5));
	sp2->setPosition(startPoint);
	float disX = endPoint.x - startPoint.x;
	float disY = endPoint.y - startPoint.y;
	float angle1 = -atan2(disY,disX);//y-x
	sp2->setRotation(angle1 * 180 / 3.14);
	addChild(sp2);

	auto sp3 = Sprite::createWithSpriteFrameName("laserbeam_blue_1024.png");
	auto startPoint1 = Vec2(visibleSize.width / 2 +100, visibleSize.height / 2);
	auto endPoint1 = Vec2(visibleSize.width*0.1 +100 , visibleSize.height*0.9);
	float distance1 = startPoint1.getDistance(endPoint1);
	sp3->setScaleX(distance1 / 1024);
	sp3->setAnchorPoint(Vec2(0, 0.5));
	sp3->setPosition(startPoint1);
	float disX1 = endPoint1.x - startPoint1.x;
	float disY1 = endPoint1.y - startPoint1.y;
	float angle11 = -atan2(disY1, disX1);//y-x
	sp3->setRotation(angle11 * 180 / 3.14);
	addChild(sp3);
	BlendFunc bf = BlendFunc::ADDITIVE;
	sp3->setBlendFunc(bf);

	ParticleSystemQuad *myParticle = ParticleSystemQuad::create("particle/laser_hit.plist");
	//SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("laser_hit.png");
	//myParticle->setTexture(frame->getTexture());
	myParticle->retain();
	myParticle->setGravity(-Vec2(disX,disY));
	myParticle->setPosition(endPoint);
	myParticle->setLife(0.1f);
	addChild(myParticle);
	// progress_front.png progress_back.png
	Sprite *pt_bg = Sprite::create("image/progress_back.png");
	pt_bg->setPosition(0, visibleSize.height);
	pt_bg->setAnchorPoint(Vec2(0,1));
	//pt_bg->setScaleX(0.15f);
	//pt_bg->setScaleY(0.3f);
	//addChild(pt_bg);
	ProgressTimer* pt = ProgressTimer::create(Sprite::create("image/progress_front.png"));
	pt->setPosition(0, visibleSize.height);
	pt->setAnchorPoint(Vec2(0, 1));
	// 设置Tag，为后面更新准备
	pt->setTag(10);
	//pt->setScaleX(0.15f);
	//pt->setScaleY(0.3f);

	this->addChild(pt);
	// 设置初始的百分比，0~100 可以是0或者100
	pt->setPercentage(90);
	// 选择类型，是条型还是时针型
	pt->setType(ProgressTimer::Type::BAR);
	//ct->setReverseProgress(true);

	// 下面两个条形的进阶
	pt->setMidpoint(Vec2(0, 0));
	pt->setBarChangeRate(Vec2(1, 0));
	schedule(schedule_selector(HelloWorld::update),1.0f);


    return true;
}
void HelloWorld::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	log("again and again");
	int r6 = getRandInt(4, 6);
	int rr = getRandInt(30, visibleSize.height - 30);
	log("%d .. %d", r6, rr);

	// 通过上面Tag设置，获取对象
	ProgressTimer *ct = (ProgressTimer*)getChildByTag(10);
	// 获取当前进度
	int num = ct->getPercentage();
	// 设置进度速度（此处为每帧+1）
	ct->setPercentage(++num);
	// 设置了循环播放
	if (num >= 100)
		ct->setPercentage(0);

}

void HelloWorld::setRandSeed()
{
	struct timeval psv;
	gettimeofday(&psv, NULL);
	unsigned rand_seed = (unsigned)(psv.tv_sec * 1000 + psv.tv_usec / 1000);    //转化为毫秒 
	srand(rand_seed);
}
int HelloWorld::getRandInt(int max)
{
	setRandSeed();
	return rand() % (max + 1);
}
int HelloWorld::getRandInt(int min, int max)
{
	setRandSeed();
	return min + rand() % (max + 1 - min);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

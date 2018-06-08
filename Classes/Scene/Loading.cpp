#include "Loading.h"

bool Loading::init()
{
	initBackground();
	initTouch();
	_percent = 1;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	_loadProgress = ProgressTimer::create(Sprite::create("UI/bar.png"));//创建一个进程条
	_loadProgress->setBarChangeRate(Point(1, 0));//设置进程条的变化速率
	_loadProgress->setType(ProgressTimer::Type::BAR);//设置进程条的类型
	_loadProgress->setMidpoint(Point(0, 1));//设置进度的运动方向
	_loadProgress->setPosition(visibleSize.width/2, visibleSize.height/2);
	_loadProgress->setPercentage(5);//设置初始值为0
	this->addChild(_loadProgress, 2);


	this->scheduleUpdate();

	return true;
}

void Loading::initBackground()
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto sprite = Sprite::create("title.jpg");

	sprite->setScale(1.6f);
	
	sprite->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height / 2 ));

	this->addChild(sprite, 1);
}

void Loading::initTouch()
{
	/*auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->setTouchEnabled(true);*/
}

void Loading::setFullPercent()
{
	_percent = 100;
}

void Loading::update(float dt)
{
	_percent+=5;
	if (_percent>=100)
	{
		_percent = 100;
	}
	_loadProgress->setPercentage(_percent);

	if (_percent==100)
	{
		CCLOG("finish");
		this->removeFromParentAndCleanup(true);
	}
}

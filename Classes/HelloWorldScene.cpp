#include "HelloWorldScene.h"

#include "Player\BasePlayerLayer.h"
#include "Scene\MainGameScene.h"
#include "Scene\Loading.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
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

    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////

	auto newBeginItem = MenuItemImage::create(
		"UI/button_left.png",
		"UI/button_on.png",
		CC_CALLBACK_1(HelloWorld::newBeginCallback, this));

	newBeginItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height/2 +3*newBeginItem->getContentSize().height));
	auto newbeginlabel = LabelTTF::create(wstrtoutf8::CreateUTF8("新的开始"),"隶书",25);
	newbeginlabel->setPosition(newBeginItem->getPosition());
	newbeginlabel->setColor(ccc3(255,50,50));

	auto contiItem = MenuItemImage::create(
		"UI/button_left.png",
		"UI/button_on.png",
		CC_CALLBACK_1(HelloWorld::contiCallback, this));

	contiItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 + contiItem->getContentSize().height));
	auto contilabel = LabelTTF::create(wstrtoutf8::CreateUTF8("继续征程"), "隶书", 25);
	contilabel->setPosition(contiItem->getPosition());
	contilabel->setColor(ccc3(255, 50, 50));


	auto loadSaveItem = MenuItemImage::create(
		"UI/button_left.png",
		"UI/button_on.png",
		CC_CALLBACK_1(HelloWorld::newBeginCallback, this));

	loadSaveItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height/2- loadSaveItem->getContentSize().height));
	auto loadsavelabel = LabelTTF::create(wstrtoutf8::CreateUTF8("再续前缘"), "隶书", 25);
	loadsavelabel->setPosition(loadSaveItem->getPosition());
	loadsavelabel->setColor(ccc3(255, 50, 50));


	auto leaveItem = MenuItemImage::create(
		"UI/button_left.png",
		"UI/button_on.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	leaveItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height/2 -3*leaveItem->getContentSize().height));
	auto leavelabel = LabelTTF::create(wstrtoutf8::CreateUTF8("归隐山林"), "隶书", 25);
	leavelabel->setPosition(leaveItem->getPosition());
	leavelabel->setColor(ccc3(255, 50, 50));


	// create menu, it's an autorelease object
    auto menu = Menu::create(newBeginItem,contiItem,loadSaveItem,leaveItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	this->addChild(newbeginlabel,2);
	this->addChild(contilabel, 2);
	this->addChild(loadsavelabel,2);
	this->addChild(leavelabel, 2);

    /////////////////////////////
	auto curr = Sprite::create("UI/dqbb.png");
	auto currlabel = LabelTTF::create(
		wstrtoutf8::CreateUTF8("0.0.1"), "Calibri", 30);
	currlabel->setColor(ccc3(255,0,0));

	curr->setPosition(visibleSize.width*0.7, visibleSize.height*0.1);
	currlabel->setPosition(
		curr->getPosition().x + curr->getContentSize().width,
		visibleSize.height*0.1);
	this->addChild(curr,1);
	this->addChild(currlabel,1);
	
    //auto label= Sprite::create("res/Spell_Fire_Fireball02.jpg");

	

    // add the label as a child to this layer
  //  this->addChild(newBeginItem, 1);




    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("title.jpg");

	sprite->setScale(1.6f);
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, 
		visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::newBeginCallback(cocos2d::Ref* pSender)
{
	CCLOG("newBeginCallback",001);

	copyInitDataToSave();//新游戏，将数据在此复制进可修改目录

	DataManage::getInstance()->initData();

	auto scene = MainGameScene::createScene(
		PlayerManage::getInstance()->getMapName(), "");
	auto reScene = CCTransitionProgressRadialCW::create(1.0f, scene);
	Director::getInstance()->replaceScene(reScene);
}

void HelloWorld::contiCallback(cocos2d::Ref * pSender)
{
	CCLOG("contiCallback", 001);
						 //初始化数据
	std::string path=FileUtils::getInstance()->getWritablePath();
	path += "TempSave/Player/player.json\0";
	if (!FileUtils::getInstance()->isFileExist(path))
	{
		return;//如果没有临时存档，就不能继续游戏
	}


	//////////////////////////Test
	/*auto loadingLayer = Loading::create();

	this->addChild(loadingLayer,3);*/
	/////////////////////////////

	DataManage::getInstance()->initData();

	auto scene = MainGameScene::createScene(
		PlayerManage::getInstance()->getMapName(), "");
	auto reScene = CCTransitionProgressRadialCW::create(1.0f, scene);
	Director::getInstance()->replaceScene(reScene);
}

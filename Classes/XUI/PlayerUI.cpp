#include "PlayerUI.h"

#pragma region StatusUi

PlayerUI * PlayerUI::create()
{
	PlayerUI *pRet = new PlayerUI;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else {
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

bool PlayerUI::init()
{
	//setPlayerData(player);
	initTouch();
	initBackground();

	//auto winSize = Director::getInstance()->getWinSize();
	_layer1 = PlayerStatusUI::create();

	//auto _layer2 = CCLayerColor::create(ccc4(50, 100, 100, 200));
	//_layer2->setPosition(180,100);
	_layer2 = BagUI::create();
	_layer3 = NULL;
	_layer4 = NULL;
	_layerMuticomplex = CCLayerMultiplex::create(_layer1, _layer2, _layer3, _layer4, NULL);//
	_layerMuticomplex->addLayer(_layer1);
	_layerMuticomplex->setPosition(0, 0);
	this->addChild(_layerMuticomplex, UILAYER2th);

	initMenu();//Z坐标先后顺序很讲究,菜单同样在UILAYER2th，但是应该在最上层
	return true;
}

void PlayerUI::initBackground()
{
	_backsprite = Sprite::create("/UI/background.png");
	_backsprite->setPosition(_backsprite->getContentSize().width / 2,
		_backsprite->getContentSize().height / 2);
	//_backsprite->setOpacity(1.0f);
	this->addChild(_backsprite);
}

void PlayerUI::initMenu()
{
	auto winSize = Director::getInstance()->getWinSize();
	float pianyi = winSize.width / 2 / 6;
	auto UICloseItem = MenuItemImage::create(
		"UI/returnui.png",
		"UI/returnui.png",
		CC_CALLBACK_1(BaseUI::closeMenuUI, this));
	UICloseItem->setPosition(Vec2(UICloseItem->getBoundingBox().getMaxX(),
		UICloseItem->getBoundingBox().getMaxY()));

	auto StatusItem = MenuItemImage::create(
		"UI/playerui.png",
		"UI/playerui.png",
		CC_CALLBACK_1(PlayerUI::loadPlayerStatusMenuUI, this));
	StatusItem->setPosition(Vec2(StatusItem->getBoundingBox().getMaxX() + pianyi,
		StatusItem->getBoundingBox().getMaxY()));

	auto BagItem = MenuItemImage::create(
		"UI/bagui.png",
		"UI/bagui.png",
		CC_CALLBACK_1(PlayerUI::loadPlayerBagMenuUI, this));
	BagItem->setPosition(Vec2(BagItem->getBoundingBox().getMaxX() + 2 * pianyi,
		BagItem->getBoundingBox().getMaxY()));

	auto SkillItem = MenuItemImage::create(
		"UI/skillui.png",
		"UI/skillui.png",
		CC_CALLBACK_1(PlayerUI::loadPlayerSkillMenuUI, this));
	SkillItem->setPosition(Vec2(SkillItem->getBoundingBox().getMaxX() + 3 * pianyi,
		SkillItem->getBoundingBox().getMaxY()));

	auto TaskItem = MenuItemImage::create(
		"UI/taskui.png",
		"UI/taskui.png",
		CC_CALLBACK_1(PlayerUI::loadPlayerTaskMenuUI, this));
	TaskItem->setPosition(Vec2(TaskItem->getBoundingBox().getMaxX() + 4 * pianyi,
		TaskItem->getBoundingBox().getMaxY()));

	_baseMenu = Menu::create(UICloseItem, StatusItem, BagItem, SkillItem, TaskItem, NULL);
	_baseMenu->setPosition(Vec2::ZERO);
	this->addChild(_baseMenu, UILAYER);
}

void PlayerUI::initTouch()
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(BaseUI::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(BaseUI::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(BaseUI::onTouchEnded, this);
	//listener->onTouchCancelled = CC_CALLBACK_2(FirstScene::keyBackClicked,this);
	listener->setSwallowTouches(true);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->setTouchEnabled(true);
}

void PlayerUI::loadPlayerStatusMenuUI(Ref * pS)
{
	//_layer1->initMenu();
	_layerMuticomplex->switchTo(0);//切换布景，如果使用switchToAndReleaseMe会释放掉当前布景  
}

void PlayerUI::loadPlayerBagMenuUI(Ref * pS)
{
	CCLOG("loadPlayerBagMenuUI");
	_layerMuticomplex->switchTo(1);
}

//void PlayerUI::loadPlayerEquipMenuUI(Ref * pS)
//{
//	CCLOG("loadPlayerEquipMenuUI");
//	_layerMuticomplex->switchTo(1);
//}

void PlayerUI::loadPlayerSkillMenuUI(Ref * pS)
{
	CCLOG("loadPlayerSkillMenuUI");
	//_layerMuticomplex->switchTo(2);
}

void PlayerUI::loadPlayerTaskMenuUI(Ref * pS)
{
	CCLOG("loadPlayerTaskMenuUI");
	//_layerMuticomplex->switchTo(3);
}


void PlayerUI::menuCloseCallback(cocos2d::Ref * pSender)
{
}


#pragma endregion
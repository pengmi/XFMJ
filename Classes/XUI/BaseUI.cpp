#include "BaseUI.h"
#include "PlayerUI.h"
#include "PlayerStatusUI.h"
#include "ConvUI.h"
USING_NS_CC;
#pragma region BASEUI

bool BaseUI::init()
{
	//initTouch();

	initMenu();
	return true;
}

void BaseUI::initBackground()
{
}

void BaseUI::initMenu()
{
	/*Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();*/
	float pianyi = 20.0f;//偏移

	auto playerStatusItem = MenuItemImage::create(
		"UI/huangzaiui.png",
		"UI/huangzaiui.png",
		CC_CALLBACK_1(BaseUI::loadPlayerMenuUI, this));

	//playerStatusItem->setPosition(Vec2(-playerStatusItem->getBoundingBox().getMaxX(),
	//	-playerStatusItem->getBoundingBox().getMaxY()));
	playerStatusItem->setPosition(Vec2(playerStatusItem->getBoundingBox().getMaxX(),
			playerStatusItem->getBoundingBox().getMaxY()));

	auto systemItem = MenuItemImage::create(
		"UI/systemui.png",
		"UI/systemui.png",
		CC_CALLBACK_1(BaseUI::loadSystemMenuUI, this));
	//systemItem->setPosition(Vec2(2*(-systemItem->getBoundingBox().getMaxX())-pianyi,
	//	-systemItem->getBoundingBox().getMaxY()));
	systemItem->setPosition(Vec2(2*(systemItem->getBoundingBox().getMaxX()+pianyi),
		systemItem->getBoundingBox().getMaxY()));


	// create menu, it's an autorelease object
	_baseMenu = Menu::create(playerStatusItem,systemItem, NULL);
	_baseMenu->setPosition(Vec2::ZERO);
	this->addChild(_baseMenu, MENULAYER);
}

void BaseUI::initTouch()
{
	//auto dispatcher = Director::getInstance()->getEventDispatcher();
	//auto listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = CC_CALLBACK_2(BaseUI::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(BaseUI::onTouchMoved, this);
	//listener->onTouchEnded = CC_CALLBACK_2(BaseUI::onTouchEnded, this);
	////listener->onTouchCancelled = CC_CALLBACK_2(FirstScene::keyBackClicked,this);
	//listener->setSwallowTouches(true);
	//dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//this->setTouchEnabled(true);
}





void BaseUI::loadPlayerMenuUI(Ref * pS)
{
	CCLOG("loadPlayerMenuUI");
	auto PlayerMenu = PlayerUI::create();

	this->addChild(PlayerMenu,UILAYER2th);
}

//void BaseUI::loadPlayerStatusMenuUI(Ref * pS)
//{
//	CCLOG("loadPlayerStatusMenuUI");
//}
//
//void BaseUI::loadPlayerEquipMenuUI(Ref * pS)
//{
//	CCLOG("loadPlayerEquipMenuUI");
//}
//
//void BaseUI::loadPlayerSkillMenuUI(Ref * pS)
//{
//	CCLOG("loadPlayerSkillMenuUI");
//}
//
//void BaseUI::loadPlayerTaskMenuUI(Ref * pS)
//{
//	CCLOG("loadPlayerTaskMenuUI");
//}

void BaseUI::loadSystemMenuUI(Ref * pS)
{
	CCLOG("loadSystemMenuUI");
}

void BaseUI::closeMenuUI(Ref * pS)
{
	this->removeFromParentAndCleanup(true);
}

void BaseUI::loadNpcNormalConvUI(NPC * npc, std::vector<NPC*>* npcVec)
{
	//if (!npc->_conv.size())
	//{
	//	return;
	//}

	auto _convUiInstanceOnly = NPCNormalConvUI::create(npc, npcVec);
	_convUiInstanceOnly->setPosition(0, 0);
	this->addChild(_convUiInstanceOnly, UILAYER);
}

void BaseUI::loadTaskBeginUI(Task * task, NPC * npc, std::vector<NPC*>* npcVec)
{
	if (!task->_taskConv._beginTaskConv.size())
	{
		return;
	}
	auto _convUiInstanceOnly = TaskBeginConvUI::create(task,npc, npcVec);
	_convUiInstanceOnly->setPosition(0, 0);
	this->addChild(_convUiInstanceOnly, UILAYER4th);
}

void BaseUI::loadTaskDoingUI(Task * task, NPC * npc, std::vector<NPC*>* npcVec)
{
	if (!task->_taskConv._doingTaskConv.size())
	{
		return;
	}
	auto _convUiInstanceOnly = TaskDoingConvUI::create(task, npc, npcVec);
	_convUiInstanceOnly->setPosition(0, 0);
	this->addChild(_convUiInstanceOnly, UILAYER3th);
}

void BaseUI::loadTaskEndUI(Task * task, NPC * npc, std::vector<NPC*>* npcVec)
{
	//完成界面必须出现，因为完成动作要出现
	//if (!task->_taskConv._finishTaskConv.size())
	//{
	//	return;
	//}
	auto _convUiInstanceOnly = TaskEndConvUI::create(task, npc, npcVec);
	_convUiInstanceOnly->setPosition(0, 0);
	this->addChild(_convUiInstanceOnly, UILAYER2th);
}

//void BaseUI::loadConvUI(std::vector<std::string> &conStr, NPC *npc, 
//	std::vector<NPC*> *npcVec)
//{
//	auto convUI = ConvUI::create(conStr,npc,npcVec);
//	convUI->setPosition(0, 0);
//	this->addChild(convUI,UILAYER2th);
//}

void BaseUI::menuCloseCallback(cocos2d::Ref * pSender)
{
	CCLOG("menuCloseCallback");
}

//void BaseUI::setPlayerData(BasePlayerLayer* hz,BasePlayerLayer *cm, BasePlayerLayer *lian)
//{
//	_player[0] = hz;
//	_player[1] = cm;
//	_player[2] = cm;
//}
//
//void BaseUI::setPlayerData(BasePlayerLayer ** p3)
//{
//	_player[0] = p3[0];
//	_player[1] = p3[1];
//	_player[2] = p3[2];
//}
//
//BasePlayerLayer** BaseUI::getPlayerData()
//{
//	return _player;
//}


#pragma endregion






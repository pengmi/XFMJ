#include "PlayerStatusUI.h"
#include "PlayerUI.h"
#include "BaseUI.h"
#pragma region PlayerStatusUI

//PlayerStatusUI * PlayerStatusUI::create(Status& hz, Status&cm, Status&lina)
//{
//	PlayerStatusUI *pRet = new PlayerStatusUI;
//	if (pRet&&pRet->init(hz,cm,lina))
//	{
//		/*上一页面传入的值*/
//		//pRet->_mapId=MAPID;
//		pRet->autorelease();
//		return pRet;
//	}
//	else {
//		CC_SAFE_DELETE(pRet);
//		return NULL;
//	}
//}

PlayerStatusUI::~PlayerStatusUI()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}

PlayerStatusUI * PlayerStatusUI::create()
{
	PlayerStatusUI *pRet = new PlayerStatusUI;
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

bool PlayerStatusUI::init()
{
	NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PlayerStatusUI::loadStatusCallback), 
		"playerstatuschange",NULL);
	//setPlayerData(player);
	initMenu();
	setCurHero((PlayerManage::getInstance())->_huangZaiLayer);
	loadStatusUi(_curHero);
	return true;
}

/*
暂时只做了主角一个人的按钮，其他的按钮没有效果
*/
void PlayerStatusUI::initMenu()
{
	auto winSize = Director::getInstance()->getWinSize();

	//auto neaack = std::bind(&PlayerStatusUI::menuCloseCallback, this);
	_huangZaiItem = MenuItemImage::create(
		"/player/hzon.png",
		"/player/hzoff.png",
		CC_CALLBACK_1(PlayerStatusUI::menuClickLoadData,this,
			PlayerManage::getInstance()->_huangZaiLayer
			));

	float pianyi = (winSize.height - 10 - _huangZaiItem->getContentSize().height*3.5) / 2;

	_CMItem = NULL;
	_lianItem = NULL;
	if (PlayerManage::getInstance()->getCmVisualable())
	{
		_CMItem = MenuItemImage::create(
			"/player/CM.png",
			"/player/CM.png",
			CC_CALLBACK_1(PlayerStatusUI::menuCloseCallback, this));//需要修改
		_CMItem->setPosition(Vec2(_huangZaiItem->getContentSize().width / 2,
			2 * _huangZaiItem->getContentSize().height + 1 * pianyi));
	}

	if (PlayerManage::getInstance()->getLianVisualable())
	{
		_lianItem = MenuItemImage::create(
			"/player/Lian.png",
			"/player/Lian.png",
			CC_CALLBACK_1(PlayerStatusUI::menuCloseCallback, this));//需要修改
		_lianItem->setPosition(Vec2(_huangZaiItem->getContentSize().width / 2,
			1 * _huangZaiItem->getContentSize().height));
	}


	_huangZaiItem->setPosition(Vec2(_huangZaiItem->getContentSize().width / 2,
		3 * _huangZaiItem->getContentSize().height + 2 * pianyi));

	_baseMenu = Menu::create(_huangZaiItem, _CMItem, _lianItem, NULL);
	_baseMenu->setPosition(Vec2::ZERO);
	this->addChild(_baseMenu, UILAYER3th);

}
void PlayerStatusUI::loadStatusUi(HeroLayer* hero)
{
	if (!hero)
	{
		return;
	}
	auto s = hero->getPlayerStatus();
	auto winSize = Director::getInstance()->getWinSize();

	auto tmpcontent = _huangZaiItem->getContentSize();
	auto tmppoint = _huangZaiItem->getPosition();
	//float pianyi = (winSize.height - 10 - _huangZaiItem->getContentSize().height*3.5) / 2;
	float lablePianYiY = winSize.height / 8;
#pragma region initLabel

	 Label* hzintroLabel = Label::create(wstrtoutf8::CreateUTF8(hero->getHeroIntro().c_str()), "隶书", 24);
	hzintroLabel->setColor(ccc3(100, 50, 0));




	float lablePianYiX = (winSize.width - tmpcontent.width - 10) / 9;

	//float lablePianYiY = winSize.height / 7;
	//hzintroLabel->setPosition(tmppoint.x + 2 * tmpcontent.width,
	//	tmppoint.y + tmpcontent.height / 2 - lablePianYiY);
	hzintroLabel->setPosition(tmppoint.x / 2 + tmpcontent.width + 
		hzintroLabel->getContentSize().width / 2,
		winSize.height - lablePianYiY);
	this->addChild(hzintroLabel, UILAYER3th);


	std::string tmpint;
	tmpint = int2str(s->_level);
	std::string str = "等级:" + tmpint;
	tmpint = int2str(s->_levelExperience);
	str += "  经验" + tmpint;
	tmpint = int2str(s->_needExperience);
	str += "/" + tmpint;

	auto Label0 = LabelTTF::create(wstrtoutf8::CreateUTF8(str.c_str()), "隶书", 24);
	Label0->setColor(ccc3(100, 0, 0));
	Label0->setColor(ccc3(155,100,0));
	Label0->setPosition(tmppoint.x / 2 + tmpcontent.width +
		Label0->getContentSize().width / 2,
		winSize.height - 2*lablePianYiY);
	this->addChild(Label0, UILAYER3th);


	//std::string tmpint;
	tmpint = int2str(s->_playerLife);
	str = "活力:" + tmpint;
	tmpint = int2str(s->_playerMaxLife);
	str += "/" + tmpint;
	tmpint = int2str(s->_playerMagic);
	str += "  法力:" + tmpint;
	tmpint = int2str(s->_playerMaxMagic);
	str += "/" + tmpint;

	auto Label1 = LabelTTF::create(wstrtoutf8::CreateUTF8(str.c_str()), "隶书", 24);
	Label1->setColor(ccc3(100, 0, 0));
	Label1->setPosition(tmppoint.x / 2 + tmpcontent.width +
		Label1->getContentSize().width / 2,
		winSize.height - 3*lablePianYiY);
	this->addChild(Label1, UILAYER3th);

	tmpint = int2str(s->_playerPower);
	str = "蛮力:" + tmpint;
	tmpint = int2str(s->_playerAgility);
	str += "  身法:" + tmpint;
	tmpint = int2str(s->_playerIntelligence);
	str += "  灵力:" + tmpint;

	auto Label2 = LabelTTF::create(wstrtoutf8::CreateUTF8(str.c_str()), "隶书", 24);
	Label2->setColor(ccc3(0, 100, 0));
	Label2->setPosition(tmppoint.x / 2 + tmpcontent.width +
		Label2->getContentSize().width / 2,
		winSize.height - 4 * lablePianYiY);
	this->addChild(Label2, UILAYER3th);

	tmpint = int2str(s->_playerAttack);
	str = "攻击:" + tmpint;
	tmpint = int2str(s->_playerDefence);
	str += "  防御:" + tmpint;

	auto Label3 = LabelTTF::create(wstrtoutf8::CreateUTF8(str.c_str()), "隶书", 24);
	Label3->setColor(ccc3(0, 0, 100));
	Label3->setPosition(tmppoint.x / 2 + tmpcontent.width +
		Label3->getContentSize().width / 2,
		winSize.height - 5 * lablePianYiY);
	this->addChild(Label3, UILAYER3th);

	tmpint = int2str(s->_playerHit);
	str = "命中:" + tmpint;
	tmpint = int2str(s->_playerDodge);
	str += "  闪躲:" + tmpint;

	auto Label4 = LabelTTF::create(wstrtoutf8::CreateUTF8(str.c_str()), "隶书", 24);
	Label4->setColor(ccc3(200, 0, 100));
	Label4->setPosition(tmppoint.x / 2 + tmpcontent.width +
		Label4->getContentSize().width / 2,
		winSize.height - 6 * lablePianYiY);
	this->addChild(Label4, UILAYER3th);
#pragma endregion
}

void PlayerStatusUI::loadStatusCallback(Ref * hero)
{
	if (!hero)
	{
		return;
	}

	menuClickLoadData(this,(HeroLayer*)hero);
}

void PlayerStatusUI::initTouch()
{
}

void PlayerStatusUI::setCurHero(HeroLayer * s)
{
	_curHero = s;
}

void PlayerStatusUI::menuCloseCallback(cocos2d::Ref * pSender)
{

}

void PlayerStatusUI::menuClickLoadData(cocos2d::Ref * pSender,HeroLayer* s)
{
	this->removeAllChildren();//先清除所有的子节点，然后重新加载
	initMenu();
	setCurHero(s);
	loadStatusUi(s);
}


#pragma endregion
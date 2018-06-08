#include"BasePlayerLayer.h"
#include "tool\HelpTool.h"

BasePlayerLayer::~BasePlayerLayer()
{
	/*if (_playerSprite)
	{
		_playerSprite->release();
	}*/
}

bool BasePlayerLayer::init()
{
	initPlayer();
	initStatus();
	initEquipment();
	initSkill();

	_standFrameCache=NULL;
	_attackFrameCache=NULL;
	_skillFrameCache=NULL;
	_hitFrameCache=NULL;
	return true;
}

//bool BasePlayerLayer::init(std::string)
//{
//	initPlayer();
//	initStatus();
//	initEquipment();
//	initSkill();
//	return true;
//}

void BasePlayerLayer::createSpriteCache()
{
	if (!_standFrameCache)
	{
		_standFrameCache = HelpTool::GetFrameCache(
			("player/plist.plist"), ("player/plist.png"));
	}
	if (!_attackFrameCache)
	{
		_attackFrameCache = HelpTool::GetFrameCache(
			("player/plist.plist"), ("player/plist.png"));
	}
	if (!_skillFrameCache)
	{
		_skillFrameCache = HelpTool::GetFrameCache(
			("player/plist.plist"), ("player/plist.png"));
	}
	if (!_hitFrameCache)
	{
		_hitFrameCache = HelpTool::GetFrameCache(
			("player/plist.plist"), ("player/plist.png"));
	}
}

bool BasePlayerLayer::initPlayer()
{
	_heroName = "";
	_playerSprite = NULL;
	//_playerSprite = cocos2d::Sprite::create("player/player.png");
	//_playerSprite->retain();//保持引用，不让其被自动清理
	//_playerSprite = cocos2d::Sprite::create();
	/*if (_playerSprite == NULL)
	{
		return false;
	}*/
	//this->addChild(_playerSprite,PLAYERLAYER);
	return true;
}


void BasePlayerLayer::setPlayerSpriteWithInit()
{
	_playerSprite=Sprite::createWithSpriteFrame(
		_standFrameCache->getSpriteFrameByName("up1.png"));
}

void BasePlayerLayer::setHeroName(std::string str)
{
	_heroName = str;
}

std::string & BasePlayerLayer::getHeroName()
{
	// TODO: 在此处插入 return 语句
	return _heroName;
}

void BasePlayerLayer::setHeroIntro(std::string str)
{
	_intro = str;
}

std::string & BasePlayerLayer::getHeroIntro()
{
	// TODO: 在此处插入 return 语句
	return _intro;
}

void BasePlayerLayer::setPicUrl(std::string str)
{
	_picUrl = str;
}

Status* BasePlayerLayer::getPlayerStatus()
{
	return &_status;
}

Sprite * BasePlayerLayer::getPlayerSprite()
{
	return _playerSprite;
}

EquipmentsList * BasePlayerLayer::getEquipmentsList()
{
	return &_Equipments;
}

void BasePlayerLayer::unloadEquipment(Item * const item)
{
	//如果类型是武器
	if (item->_type=="weapon")
	{
		_Equipments._weaponID = 0;
		return;
	}
	//如果类型是头饰
	if (item->_type == "head")
	{
		_Equipments._headID = 0;
		return;
	}
	//如果类型是衣服
	if (item->_type == "clothes")
	{
		_Equipments._clothesID = 0;
		return;
	}
	//如果类型是披风
	if (item->_type == "cloak")
	{
		_Equipments._cloackID = 0;
		return;
	}
	//如果类型是手套
	if (item->_type == "glove")
	{
		_Equipments._gloveID = 0;
		return;
	}
	//如果类型是腿甲
	if (item->_type == "tasses")
	{
		_Equipments._tassesID = 0;
		return;
	}
	//如果类型是鞋子
	if (item->_type == "shoes")
	{
		_Equipments._shoesID = 0;
		return;
	}
	//如果类型是首饰
	if (item->_type == "ornament")
	{
		_Equipments._ornamentsID = 0;
		return;
	}
}

bool BasePlayerLayer::equipEquipment(Item * const item)
{

	//如果类型是武器
	if (item->_type == "weapon"&&
		!_Equipments._weaponID)
	{
		_Equipments._weaponID =item->_itemId;
		return true;
	}
	//如果类型是头饰
	if (item->_type == "head" &&
		!_Equipments._headID)
	{
		_Equipments._headID = item->_itemId;
		return true;
	}
	//如果类型是衣服
	if (item->_type == "clothes" &&
		!_Equipments._clothesID)
	{
		_Equipments._clothesID = item->_itemId;
		return true;
	}
	//如果类型是披风
	if (item->_type == "cloak" &&
		!_Equipments._cloackID)
	{
		_Equipments._cloackID = item->_itemId;
		return true;
	}
	//如果类型是手套
	if (item->_type == "glove" &&
		!_Equipments._gloveID)
	{
		_Equipments._gloveID = item->_itemId;
		return true;
	}
	//如果类型是腿甲
	if (item->_type == "tasses" &&
		!_Equipments._tassesID)
	{
		_Equipments._tassesID = item->_itemId;
		return true;
	}
	//如果类型是鞋子
	if (item->_type == "shoes" &&
		!_Equipments._shoesID)
	{
		_Equipments._shoesID = item->_itemId;
		return true;
	}
	//如果类型是首饰
	if (item->_type == "ornament" &&
		!_Equipments._ornamentsID)
	{
		_Equipments._ornamentsID = item->_itemId;
		return true;
	}
	return false;
}



void BasePlayerLayer::menuCloseCallback(cocos2d::Ref * pSender)
{
}

void BasePlayerLayer::contactCallback(cocos2d::Ref * pSender)
{
}

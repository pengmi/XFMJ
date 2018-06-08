#include "PlayerManage.h"

PlayerManage *PlayerManage::_instance = NULL;
PlayerManage * PlayerManage::create()
{
	if (_instance)
		return _instance;
	_instance = new PlayerManage();
	if (_instance&&_instance->init())
	{
		_instance->autorelease();
		return _instance;
	}
	else {
		CC_SAFE_DELETE(_instance);
		return NULL;
	}
}

PlayerManage * PlayerManage::getInstance()
{
	if (_instance)
		return _instance;
	_instance = new PlayerManage();
	return _instance;
}

bool PlayerManage::init()
{
	_playerFrameCache = HelpTool::GetFrameCache(_stepPlistSrc.c_str(), _stepPngSrc.c_str());
	
	_sprite = Sprite::createWithSpriteFrame(_playerFrameCache->getSpriteFrameByName("up1.png"));
	//setSprite();
	//_sprite = Sprite::create(_playerSpriteSrc);
	this->addChild(_sprite, PLAYERLAYER);

	//createPlayer();//玩家创建在playerManage数据读取以后
	return true;
}

void PlayerManage::createPlayer()
{
	if (!_huangZaiLayer)
	{
		_huangZaiLayer = HeroLayer::create();
		this->addChild(_huangZaiLayer, PLAYERLAYER);
	}
	
	if (_cmVisualable)
	{
		if (!_cmLayer)
		{
			_cmLayer = HeroLayer::create();
			this->addChild(_cmLayer, PLAYERLAYER);
		}
		
	}
	
	if(_lianVisualable)
	{
		if (!_lianLayer)
		{
			_lianLayer = HeroLayer::create();
			this->addChild(_lianLayer, PLAYERLAYER);
		}
	}
}

void PlayerManage::removePlayer(HeroLayer * hl)
{
	CC_SAFE_RELEASE_NULL(hl);
}

void PlayerManage::checkDirection(Point &p1, Point &p2)
{
	if (p1.x < p2.x)//right
	{
		if (_direct!= Direction::right)
		{
			_stepindex = 1;
		}
		else
		{
			_stepindex = ((_stepindex) % 3)+1;
		}
		_direct= Direction::right;
	}
	else if(p1.x>p2.x)//left
	{
		if (_direct != Direction::left)
		{
			_stepindex = 1;
		}
		else
		{
			_stepindex = ((_stepindex) % 3) + 1;
		}
		_direct = Direction::left;
	}
	else if (p1.x==p2.x)
	{
		if (p1.y < p2.y)//up
		{
			if (_direct != Direction::up)
			{
				_stepindex = 1;
			}
			else
			{
				_stepindex = ((_stepindex) % 3) + 1;
			}
			_direct = Direction::up;
		}
		else if (p1.y>p2.y)//down
		{
			if (_direct != Direction::down)
			{
				_stepindex = 1;
			}
			else
			{
				_stepindex = ((_stepindex) % 3) + 1;
			}
			_direct = Direction::down;
		}
	}
	//CCLOG(" direct %d index %d",_direct,_stepindex);
}

void PlayerManage::setSpriteFrame()
{
	std::string str[4] = {"up","right","left","down"};
	//  

	auto frame = _playerFrameCache->getSpriteFrameByName(str[_direct] + HelpTool::int2str(_stepindex)+".png");

	_sprite->setDisplayFrame(frame);
}

void PlayerManage::moveSprite(Point & point)
{
	auto nowPoint = _sprite->getPosition();

	//方向和脚步确认以后再设置对应的图片
	checkDirection(nowPoint,point);
	setSpriteFrame();

	_sprite->setPosition(point);
}

void PlayerManage::setSpritePosition(Point& point)
{
	_sprite->setPosition(point);
	
}

void PlayerManage::setDirection(int i)
{
	_direct = i;
}

void PlayerManage::setStepIndex(int i)
{
	_stepindex = i;
}


bool PlayerManage::getCmVisualable()
{
	return _cmVisualable;
}

void PlayerManage::setCmVisualable(bool b)
{
	_cmVisualable = b;
}

bool PlayerManage::getLianVisualable()
{
	return _lianVisualable;
}

void PlayerManage::setLianVisualable(bool b)
{
	_lianVisualable = b;
}

void PlayerManage::setMapName(std::string m)
{
	_mapName = m;
}

std::string PlayerManage::getMapName()
{
	return _mapName;
}


std::string PlayerManage::useItem(HeroLayer* hero,Item * const item)
{
	string msgStr = "";
	if (!hero||!item)
	{
		msgStr = "物品不可用";

		return msgStr;
	}

	auto heroStatus = hero->getPlayerStatus();

	//最大生命  
	if (item->_addMaxLife)
	{
		msgStr += "活力上限+" +
			HelpTool::int2str(item->_addMaxLife) + "\n";
		heroStatus->_playerMaxLife += item->_addMaxLife;
	}
	//现在生命 活力
	if (item->_addLife)
	{
		heroStatus->_playerLife += item->_addLife;
		msgStr += "活力+" +
			HelpTool::int2str(item->_addLife) + "\n";
		if (heroStatus->_playerLife>heroStatus->_playerMaxLife)
		{
			heroStatus->_playerLife = heroStatus->_playerMaxLife;
			msgStr += "已经活力满满!\n";
		}
	}
	//最大魔法
	if (item->_addMaxMagic)
	{
		heroStatus->_playerMaxMagic += item->_addMaxMagic;
		msgStr += "法力上限+" +
			HelpTool::int2str(item->_addMaxMagic) + "\n";
	}
	//现在魔法 法力
	if (item->_addMagic)
	{
		heroStatus->_playerMagic += item->_addMagic;
		msgStr += "法力+" +
			HelpTool::int2str(item->_addMagic) + "\n";
		if (heroStatus->_playerMagic>heroStatus->_playerMaxMagic)
		{
			heroStatus->_playerMagic = heroStatus->_playerMaxMagic;
			msgStr += "已经法力饱和!\n";
		}
	}
	//力量
	if (item->_addPower)
	{
		heroStatus->_playerPower += item->_addPower;
		msgStr += "力量+" +
			HelpTool::int2str(item->_addPower) + "\n";
	}
	//身法
	if (item->_addAgility)
	{
		heroStatus->_playerAgility += item->_addAgility;
		msgStr += "身法+" +
			HelpTool::int2str(item->_addAgility) + "\n";
	}
	//灵力
	if (item->_addIntelligence)
	{
		heroStatus->_playerIntelligence += item->_addIntelligence;
		msgStr += "灵力+" +
			HelpTool::int2str(item->_addIntelligence) + "\n";
	}
	//攻击 
	if (item->_addAttack)
	{
		heroStatus->_playerAttack += item->_addAttack;
		msgStr += "攻击+" +
			HelpTool::int2str(item->_addAttack) + "\n";
	}
	//防御
	if (item->_addDefence)
	{
		heroStatus->_playerDefence += item->_addDefence;
		msgStr += "防御+" +
			HelpTool::int2str(item->_addDefence) + "\n";
	}
	//命中
	if (item->_addHit)
	{
		heroStatus->_playerHit += item->_addHit;
		msgStr += "命中+" +
			HelpTool::int2str(item->_addHit) + "\n";
	}
	//闪避
	if (item->_addDodge)
	{
		heroStatus->_playerDodge += item->_addDodge;
		msgStr += "闪避+" +
			HelpTool::int2str(item->_addDodge) + "\n";
	}
	return msgStr;
}

std::string PlayerManage::equipItem(HeroLayer * hero, Item * const item)
{
	string msgStr = "";

	if (!hero || !item)
	{
		msgStr = "物品不可用";

		return msgStr;
	}
	//如果不能装备（格子上已经有装备）
	auto tb = hero->equipEquipment(item);
	if(!tb)
	{
		msgStr = "不能装备!";
		return msgStr;
	}
	auto heroStatus = hero->getPlayerStatus();

	//最大生命  
	if (item->_addMaxLife)
	{
		msgStr += "活力上限+" +
			HelpTool::int2str(item->_addMaxLife) + "\n";
		heroStatus->_playerMaxLife += item->_addMaxLife;
	}
	//现在生命 活力
	if (item->_addLife)
	{
		heroStatus->_playerLife += item->_addLife;
		msgStr += "活力+" +
			HelpTool::int2str(item->_addLife) + "\n";
		if (heroStatus->_playerLife>heroStatus->_playerMaxLife)
		{
			heroStatus->_playerLife = heroStatus->_playerMaxLife;
			msgStr += "已经活力满满!\n";
		}
	}
	//最大魔法
	if (item->_addMaxMagic)
	{
		heroStatus->_playerMaxMagic += item->_addMaxMagic;
		msgStr += "法力上限+" +
			HelpTool::int2str(item->_addMaxMagic) + "\n";
	}
	//现在魔法 法力
	if (item->_addMagic)
	{
		heroStatus->_playerMagic += item->_addMagic;
		msgStr += "法力+" +
			HelpTool::int2str(item->_addMagic) + "\n";
		if (heroStatus->_playerMagic>heroStatus->_playerMaxMagic)
		{
			heroStatus->_playerMagic = heroStatus->_playerMaxMagic;
			msgStr += "已经法力饱和!\n";
		}
	}
	//力量
	if (item->_addPower)
	{
		heroStatus->_playerPower += item->_addPower;
		msgStr += "力量+" +
			HelpTool::int2str(item->_addPower) + "\n";
	}
	//身法
	if (item->_addAgility)
	{
		heroStatus->_playerAgility += item->_addAgility;
		msgStr += "身法+" +
			HelpTool::int2str(item->_addAgility) + "\n";
	}
	//灵力
	if (item->_addIntelligence)
	{
		heroStatus->_playerIntelligence += item->_addIntelligence;
		msgStr += "灵力+" +
			HelpTool::int2str(item->_addIntelligence) + "\n";
	}
	//攻击 
	if (item->_addAttack)
	{
		heroStatus->_playerAttack += item->_addAttack;
		msgStr += "攻击+" +
			HelpTool::int2str(item->_addAttack) + "\n";
	}
	//防御
	if (item->_addDefence)
	{
		heroStatus->_playerDefence += item->_addDefence;
		msgStr += "防御+" +
			HelpTool::int2str(item->_addDefence) + "\n";
	}
	//命中
	if (item->_addHit)
	{
		heroStatus->_playerHit += item->_addHit;
		msgStr += "命中+" +
			HelpTool::int2str(item->_addHit) + "\n";
	}
	//闪避
	if (item->_addDodge)
	{
		heroStatus->_playerDodge += item->_addDodge;
		msgStr += "闪避+" +
			HelpTool::int2str(item->_addDodge) + "\n";
	}
	return msgStr;
}

std::string PlayerManage::unloadEquipment(HeroLayer* hero, Item * const item)
{
	string msgStr = "";
	if (!hero||!item)
	{
		msgStr = "数据错误";

		return msgStr;
	}

	

	auto heroStatus = hero->getPlayerStatus();

	//最大生命  
	if (item->_addMaxLife)
	{
		msgStr += "活力上限-" +
			HelpTool::int2str(item->_addMaxLife) + "\n";
		heroStatus->_playerMaxLife -= item->_addMaxLife;
	}
	//现在生命 活力
	if (item->_addLife)
	{
		heroStatus->_playerLife -= item->_addLife;
		msgStr += "活力-" +
			HelpTool::int2str(item->_addLife) + "\n";
		if (heroStatus->_playerLife>heroStatus->_playerMaxLife)
		{
			heroStatus->_playerLife = 1;
			//msgStr += "已经活力满满!\n";
		}
	}
	//最大魔法
	if (item->_addMaxMagic)
	{
		heroStatus->_playerMaxMagic -= item->_addMaxMagic;
		msgStr += "法力上限-" +
			HelpTool::int2str(item->_addMaxMagic) + "\n";
	}
	//现在魔法 法力
	if (item->_addMagic)
	{
		heroStatus->_playerMagic -= item->_addMagic;
		msgStr += "法力-" +
			HelpTool::int2str(item->_addMagic) + "\n";
		if (heroStatus->_playerMagic>heroStatus->_playerMaxMagic)
		{
			heroStatus->_playerMagic = heroStatus->_playerMaxMagic;
			msgStr += "已经法力饱和!\n";
		}
	}
	//力量
	if (item->_addPower)
	{
		heroStatus->_playerPower -= item->_addPower;
		msgStr += "力量-" +
			HelpTool::int2str(item->_addPower) + "\n";
	}
	//身法
	if (item->_addAgility)
	{
		heroStatus->_playerAgility -= item->_addAgility;
		msgStr += "身法-" +
			HelpTool::int2str(item->_addAgility) + "\n";
	}
	//灵力
	if (item->_addIntelligence)
	{
		heroStatus->_playerIntelligence -= item->_addIntelligence;
		msgStr += "灵力-" +
			HelpTool::int2str(item->_addIntelligence) + "\n";
	}
	//攻击 
	if (item->_addAttack)
	{
		heroStatus->_playerAttack -= item->_addAttack;
		msgStr += "攻击-" +
			HelpTool::int2str(item->_addAttack) + "\n";
	}
	//防御
	if (item->_addDefence)
	{
		heroStatus->_playerDefence -= item->_addDefence;
		msgStr += "防御-" +
			HelpTool::int2str(item->_addDefence) + "\n";
	}
	//命中
	if (item->_addHit)
	{
		heroStatus->_playerHit -= item->_addHit;
		msgStr += "命中-" +
			HelpTool::int2str(item->_addHit) + "\n";
	}
	//闪避
	if (item->_addDodge)
	{
		heroStatus->_playerDodge -= item->_addDodge;
		msgStr += "闪避-" +
			HelpTool::int2str(item->_addDodge) + "\n";
	}
	///////////////////////////

	hero->unloadEquipment(item);

	return msgStr;
}

PlayerManage::PlayerManage()
{
	init();
}

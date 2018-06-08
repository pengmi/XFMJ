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

	//createPlayer();//��Ҵ�����playerManage���ݶ�ȡ�Ժ�
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

	//����ͽŲ�ȷ���Ժ������ö�Ӧ��ͼƬ
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
		msgStr = "��Ʒ������";

		return msgStr;
	}

	auto heroStatus = hero->getPlayerStatus();

	//�������  
	if (item->_addMaxLife)
	{
		msgStr += "��������+" +
			HelpTool::int2str(item->_addMaxLife) + "\n";
		heroStatus->_playerMaxLife += item->_addMaxLife;
	}
	//�������� ����
	if (item->_addLife)
	{
		heroStatus->_playerLife += item->_addLife;
		msgStr += "����+" +
			HelpTool::int2str(item->_addLife) + "\n";
		if (heroStatus->_playerLife>heroStatus->_playerMaxLife)
		{
			heroStatus->_playerLife = heroStatus->_playerMaxLife;
			msgStr += "�Ѿ���������!\n";
		}
	}
	//���ħ��
	if (item->_addMaxMagic)
	{
		heroStatus->_playerMaxMagic += item->_addMaxMagic;
		msgStr += "��������+" +
			HelpTool::int2str(item->_addMaxMagic) + "\n";
	}
	//����ħ�� ����
	if (item->_addMagic)
	{
		heroStatus->_playerMagic += item->_addMagic;
		msgStr += "����+" +
			HelpTool::int2str(item->_addMagic) + "\n";
		if (heroStatus->_playerMagic>heroStatus->_playerMaxMagic)
		{
			heroStatus->_playerMagic = heroStatus->_playerMaxMagic;
			msgStr += "�Ѿ���������!\n";
		}
	}
	//����
	if (item->_addPower)
	{
		heroStatus->_playerPower += item->_addPower;
		msgStr += "����+" +
			HelpTool::int2str(item->_addPower) + "\n";
	}
	//��
	if (item->_addAgility)
	{
		heroStatus->_playerAgility += item->_addAgility;
		msgStr += "��+" +
			HelpTool::int2str(item->_addAgility) + "\n";
	}
	//����
	if (item->_addIntelligence)
	{
		heroStatus->_playerIntelligence += item->_addIntelligence;
		msgStr += "����+" +
			HelpTool::int2str(item->_addIntelligence) + "\n";
	}
	//���� 
	if (item->_addAttack)
	{
		heroStatus->_playerAttack += item->_addAttack;
		msgStr += "����+" +
			HelpTool::int2str(item->_addAttack) + "\n";
	}
	//����
	if (item->_addDefence)
	{
		heroStatus->_playerDefence += item->_addDefence;
		msgStr += "����+" +
			HelpTool::int2str(item->_addDefence) + "\n";
	}
	//����
	if (item->_addHit)
	{
		heroStatus->_playerHit += item->_addHit;
		msgStr += "����+" +
			HelpTool::int2str(item->_addHit) + "\n";
	}
	//����
	if (item->_addDodge)
	{
		heroStatus->_playerDodge += item->_addDodge;
		msgStr += "����+" +
			HelpTool::int2str(item->_addDodge) + "\n";
	}
	return msgStr;
}

std::string PlayerManage::equipItem(HeroLayer * hero, Item * const item)
{
	string msgStr = "";

	if (!hero || !item)
	{
		msgStr = "��Ʒ������";

		return msgStr;
	}
	//�������װ�����������Ѿ���װ����
	auto tb = hero->equipEquipment(item);
	if(!tb)
	{
		msgStr = "����װ��!";
		return msgStr;
	}
	auto heroStatus = hero->getPlayerStatus();

	//�������  
	if (item->_addMaxLife)
	{
		msgStr += "��������+" +
			HelpTool::int2str(item->_addMaxLife) + "\n";
		heroStatus->_playerMaxLife += item->_addMaxLife;
	}
	//�������� ����
	if (item->_addLife)
	{
		heroStatus->_playerLife += item->_addLife;
		msgStr += "����+" +
			HelpTool::int2str(item->_addLife) + "\n";
		if (heroStatus->_playerLife>heroStatus->_playerMaxLife)
		{
			heroStatus->_playerLife = heroStatus->_playerMaxLife;
			msgStr += "�Ѿ���������!\n";
		}
	}
	//���ħ��
	if (item->_addMaxMagic)
	{
		heroStatus->_playerMaxMagic += item->_addMaxMagic;
		msgStr += "��������+" +
			HelpTool::int2str(item->_addMaxMagic) + "\n";
	}
	//����ħ�� ����
	if (item->_addMagic)
	{
		heroStatus->_playerMagic += item->_addMagic;
		msgStr += "����+" +
			HelpTool::int2str(item->_addMagic) + "\n";
		if (heroStatus->_playerMagic>heroStatus->_playerMaxMagic)
		{
			heroStatus->_playerMagic = heroStatus->_playerMaxMagic;
			msgStr += "�Ѿ���������!\n";
		}
	}
	//����
	if (item->_addPower)
	{
		heroStatus->_playerPower += item->_addPower;
		msgStr += "����+" +
			HelpTool::int2str(item->_addPower) + "\n";
	}
	//��
	if (item->_addAgility)
	{
		heroStatus->_playerAgility += item->_addAgility;
		msgStr += "��+" +
			HelpTool::int2str(item->_addAgility) + "\n";
	}
	//����
	if (item->_addIntelligence)
	{
		heroStatus->_playerIntelligence += item->_addIntelligence;
		msgStr += "����+" +
			HelpTool::int2str(item->_addIntelligence) + "\n";
	}
	//���� 
	if (item->_addAttack)
	{
		heroStatus->_playerAttack += item->_addAttack;
		msgStr += "����+" +
			HelpTool::int2str(item->_addAttack) + "\n";
	}
	//����
	if (item->_addDefence)
	{
		heroStatus->_playerDefence += item->_addDefence;
		msgStr += "����+" +
			HelpTool::int2str(item->_addDefence) + "\n";
	}
	//����
	if (item->_addHit)
	{
		heroStatus->_playerHit += item->_addHit;
		msgStr += "����+" +
			HelpTool::int2str(item->_addHit) + "\n";
	}
	//����
	if (item->_addDodge)
	{
		heroStatus->_playerDodge += item->_addDodge;
		msgStr += "����+" +
			HelpTool::int2str(item->_addDodge) + "\n";
	}
	return msgStr;
}

std::string PlayerManage::unloadEquipment(HeroLayer* hero, Item * const item)
{
	string msgStr = "";
	if (!hero||!item)
	{
		msgStr = "���ݴ���";

		return msgStr;
	}

	

	auto heroStatus = hero->getPlayerStatus();

	//�������  
	if (item->_addMaxLife)
	{
		msgStr += "��������-" +
			HelpTool::int2str(item->_addMaxLife) + "\n";
		heroStatus->_playerMaxLife -= item->_addMaxLife;
	}
	//�������� ����
	if (item->_addLife)
	{
		heroStatus->_playerLife -= item->_addLife;
		msgStr += "����-" +
			HelpTool::int2str(item->_addLife) + "\n";
		if (heroStatus->_playerLife>heroStatus->_playerMaxLife)
		{
			heroStatus->_playerLife = 1;
			//msgStr += "�Ѿ���������!\n";
		}
	}
	//���ħ��
	if (item->_addMaxMagic)
	{
		heroStatus->_playerMaxMagic -= item->_addMaxMagic;
		msgStr += "��������-" +
			HelpTool::int2str(item->_addMaxMagic) + "\n";
	}
	//����ħ�� ����
	if (item->_addMagic)
	{
		heroStatus->_playerMagic -= item->_addMagic;
		msgStr += "����-" +
			HelpTool::int2str(item->_addMagic) + "\n";
		if (heroStatus->_playerMagic>heroStatus->_playerMaxMagic)
		{
			heroStatus->_playerMagic = heroStatus->_playerMaxMagic;
			msgStr += "�Ѿ���������!\n";
		}
	}
	//����
	if (item->_addPower)
	{
		heroStatus->_playerPower -= item->_addPower;
		msgStr += "����-" +
			HelpTool::int2str(item->_addPower) + "\n";
	}
	//��
	if (item->_addAgility)
	{
		heroStatus->_playerAgility -= item->_addAgility;
		msgStr += "��-" +
			HelpTool::int2str(item->_addAgility) + "\n";
	}
	//����
	if (item->_addIntelligence)
	{
		heroStatus->_playerIntelligence -= item->_addIntelligence;
		msgStr += "����-" +
			HelpTool::int2str(item->_addIntelligence) + "\n";
	}
	//���� 
	if (item->_addAttack)
	{
		heroStatus->_playerAttack -= item->_addAttack;
		msgStr += "����-" +
			HelpTool::int2str(item->_addAttack) + "\n";
	}
	//����
	if (item->_addDefence)
	{
		heroStatus->_playerDefence -= item->_addDefence;
		msgStr += "����-" +
			HelpTool::int2str(item->_addDefence) + "\n";
	}
	//����
	if (item->_addHit)
	{
		heroStatus->_playerHit -= item->_addHit;
		msgStr += "����-" +
			HelpTool::int2str(item->_addHit) + "\n";
	}
	//����
	if (item->_addDodge)
	{
		heroStatus->_playerDodge -= item->_addDodge;
		msgStr += "����-" +
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

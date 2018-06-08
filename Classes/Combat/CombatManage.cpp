#include "CombatManage.h"
#include "Combat\MonsterManage.h"
#include "Player\PlayerManage.h"
CombatManage* CombatManage::_instance=NULL;
CombatManage::~CombatManage()
{
	//删除怪物实例
	deleteMonsters();
	delete _instance;
	_instance = NULL;
}

CombatManage * CombatManage::getInstance()
{
	if (_instance)
	{
		return _instance;
	}	
	_instance = new CombatManage();
	return _instance;
}

void CombatManage::initCombatTargetsList()
{
	for (int i = 0; i < 3; i++)
	{
		_combatTargetsList[i] = NULL;
	}
	for (int i = 0; i < 3; i++)
	{
		_combatCharacterList[i] = NULL;
	}
}

bool CombatManage::isGetMonsters()
{
	srand(int(time(0))+rand());
	int i = random(0, 100);
	//遇怪机率约为5%
	if (i<5)
	{
		return true;
	}
	return false;
}


Monster** CombatManage::createMonstersRandom(Node* parent)
{
	//如果不遇怪，直接返回空
	//if (!isGetMonsters())
	//{
	//	return NULL;
	//}
	auto monstersinstancelist = MonsterManage::getInstance()->_monstersInstanceList;
	//遇怪，随机拷贝1-3个怪物实例进行战斗列表
	if (int size= monstersinstancelist.size()-1)
	{
		//先删除怪物实例，再重新创建，保证每次怪都重新刷新
		deleteMonsters();
		int num = random(1,3);
		CCLOG("Catch Monsters %d",num);
		int i = random(0, size);
	//	_combatTargetsList[0] = new Monster(monstersinstancelist[i]);
		_combatTargetsList[0] = Monster::createWithSpriteFrame(
			monstersinstancelist[i]->_standFrameCache->getSpriteFrameByName("down1.png"),
			monstersinstancelist[i]);
		parent->addChild(_combatTargetsList[0]);
		num--;
		if (!num)
		{
			//不加载第二个怪和第三个怪
			_combatTargetsList[1]=NULL;
			_combatTargetsList[2]=NULL;
			return NULL;
		}
		i = random(0, size);
		_combatTargetsList[1] = Monster::createWithSpriteFrame(
			monstersinstancelist[i]->_standFrameCache->getSpriteFrameByName("down1.png"),
			monstersinstancelist[i]);
		parent->addChild(_combatTargetsList[1]);
		num--;
		if (!num)
		{
			//不加载第三个怪
			_combatTargetsList[2] = NULL;
			return NULL;
		}
		i = random(0, size);
		_combatTargetsList[2] = Monster::createWithSpriteFrame(
			monstersinstancelist[i]->_standFrameCache->getSpriteFrameByName("down1.png"),
			monstersinstancelist[i]);
		parent->addChild(_combatTargetsList[2]);
	}
	return NULL;
}

void CombatManage::initIndexNStatus()
{
	//初始状态，怪物索引为0，表示不该他的位置
	//_playerControlStatus=true,表示该玩家行动
	//_playerIndex表示该哪个人物行动
	_monsterIndex = 0;
	_playerControlStatus = true;
	_playerIndex = 1;
}

void CombatManage::finishOneStep()
{
	
	/*
	控制状态和操作索引转换
	*/
	if (_playerControlStatus)
	{
		addPlayerIndex();
	}
	else
	{
		addMonsterIndex();
	}
}

bool CombatManage::addPlayerIndex()
{
	auto playermanage = PlayerManage::getInstance();
	if (1 == _playerIndex)
	{
		//如果只有一个玩家
		if (!playermanage->_lianLayer&&!playermanage->_cmLayer)
		{
			_playerControlStatus = false;
			_playerIndex = 1;
			_monsterIndex = 1;
			return false;
		}

		if (playermanage->_lianLayer)
		{
			_playerIndex = 2;
			return true;
		}
		if (playermanage->_cmLayer)
		{
			_playerIndex = 3;
			return true;
		}
	}
	else if (2 == _playerIndex)
	{
		if (!playermanage->_cmLayer)
		{
			_playerControlStatus = false;
			_playerIndex = 1;
			_monsterIndex = 1;
			return false;
		}

		if (playermanage->_cmLayer)
		{
			_playerIndex = 3;
			return true;
		}
	}
	else
	{
		_playerControlStatus = false;
		_playerIndex = 1;
		_monsterIndex = 1;
		return false;
	}
	return true;
}

bool CombatManage::addMonsterIndex()
{
	//怪物状态和战斗转换
	if (1== _monsterIndex)
	{
		if (_combatTargetsList[1])
		{
			_monsterIndex = 2;
			return false;
		}
		else if (_combatTargetsList[2])
		{
			_monsterIndex = 3;
			return false;
		}
		else
		{
			_monsterIndex = 1;
			_playerControlStatus = true;
			_playerIndex = 1;
			return true;
		}
	}

	if (2 == _monsterIndex)
	{
		if (_combatTargetsList[2])
		{
			_monsterIndex = 3;
			return false;
		}
		else
		{
			_monsterIndex = 1;
			_playerControlStatus = true;
			_playerIndex = 1;
			return true;
		}

	}

	if (3 == _monsterIndex)
	{
		_monsterIndex = 1;
		_playerControlStatus = true;
		_playerIndex = 1;
		return true;
	}

	return false;
}

void CombatManage::deleteMonsters()
{
	for (int i = 0; i < 3; i++)
	{
		if (_combatTargetsList[i]&&_combatTargetsList[i]->getParent())
		{
			//如果存在父结点
			//delete _combatTargetsList[i];
			_combatTargetsList[i]->removeFromParentAndCleanup(true);
			_combatTargetsList[i] = NULL;
		}
	}
}

Monster ** CombatManage::getMonsters()
{
	return 	_combatTargetsList;
	;
}

void CombatManage::caculatePlayerDamage()
{
	auto playermanage = PlayerManage::getInstance();
	auto player = playermanage->_huangZaiLayer;
	switch (_playerIndex)
	{
	case 0:
		_playerIndex = 1;
	case 1:
		break;
	case 2:
		player = playermanage->_lianLayer;
		break;
	case 3:
		player = playermanage->_cmLayer;
		break;
	default:
		break;
	} ;
	for (int i = 0; i < 3; i++)
	{
		//如果怪物不存在，下一个
		if (!_combatTargetsList[i])
		{
			continue;
		}
		_combatTargetsList[i]->_life-=
			getDamageValue(player->getPlayerStatus());
		if (_combatTargetsList[i]->_life<=0)
		{
			_combatTargetsList[i]->removeFromParentAndCleanup(true);
			_combatTargetsList[i] = NULL;
		}
	}
}

int CombatManage::getDamageValue(Status const * status)
{

	return status->_playerAttack;
}

bool CombatManage::isSuccess()
{
	for (int i = 0; i < 3; i++)
	{
		if (_combatTargetsList[i])
		{
			return false;
		} 
	}
	return true;
}

void CombatManage::caculateMonsterDamage()
{
}

int CombatManage::getDamageValue(Monster const * status)
{
	return 0;
}

CombatManage::CombatManage()
{
	initCombatTargetsList();
	_playerControlStatus = true;
	_monsterIndex=1;
	_playerIndex=1;
}

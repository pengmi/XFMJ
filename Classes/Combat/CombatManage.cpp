#include "CombatManage.h"
#include "Combat\MonsterManage.h"
#include "Player\PlayerManage.h"
CombatManage* CombatManage::_instance=NULL;
CombatManage::~CombatManage()
{
	//ɾ������ʵ��
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
	//���ֻ���ԼΪ5%
	if (i<5)
	{
		return true;
	}
	return false;
}


Monster** CombatManage::createMonstersRandom(Node* parent)
{
	//��������֣�ֱ�ӷ��ؿ�
	//if (!isGetMonsters())
	//{
	//	return NULL;
	//}
	auto monstersinstancelist = MonsterManage::getInstance()->_monstersInstanceList;
	//���֣��������1-3������ʵ������ս���б�
	if (int size= monstersinstancelist.size()-1)
	{
		//��ɾ������ʵ���������´�������֤ÿ�ιֶ�����ˢ��
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
			//�����صڶ����ֺ͵�������
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
			//�����ص�������
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
	//��ʼ״̬����������Ϊ0����ʾ��������λ��
	//_playerControlStatus=true,��ʾ������ж�
	//_playerIndex��ʾ���ĸ������ж�
	_monsterIndex = 0;
	_playerControlStatus = true;
	_playerIndex = 1;
}

void CombatManage::finishOneStep()
{
	
	/*
	����״̬�Ͳ�������ת��
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
		//���ֻ��һ�����
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
	//����״̬��ս��ת��
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
			//������ڸ����
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
		//������ﲻ���ڣ���һ��
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

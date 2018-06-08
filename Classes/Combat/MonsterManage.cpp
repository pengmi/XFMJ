#include "MonsterManage.h"
#include "Player\PlayerManage.h"
#include "XData\DataManage.h"

MonsterManage * MonsterManage::_instance = NULL;
MonsterManage::~MonsterManage()
{
	//删除怪物数据
	deleteMonstersInstanceList();
	clearMonstersIDList();
	//最后删除怪物管理类实例
	delete _instance;
}

MonsterManage * MonsterManage::getInstance()
{
	if (_instance)
	{
		return _instance;
	}
	_instance = new MonsterManage();
	return _instance;
}

bool MonsterManage::setMonsterActiveStatus(bool b)
{
	
	return _isMonsterActive=b;
}

bool MonsterManage::getMonsterActiveStatus()
{
	return _isMonsterActive;
}

void MonsterManage::setMonstersManageData(string mapname)
{
	//先清空列表
	deleteMonstersInstanceList();
	clearMonstersIDList();
	//获取敌人列表
	DataManage::getInstance()->
		readMonsterManage(this,mapname);

	if (_isMonsterActive)
	{
		createMonstersInstaceList();
	}
}

void MonsterManage::clearMonstersIDList()
{
	_monstersIDList.clear();
}

void MonsterManage::initDictionary()
{
	_mapHasMonsterDic.insert(
		std::pair<std::string, bool>("1-1", false));
	_mapHasMonsterDic.insert(
		std::pair<std::string, bool>("1-2", true));
	_mapHasMonsterDic.insert(
		std::pair<std::string, bool>("1-3", true));
	_mapHasMonsterDic.insert(
		std::pair<std::string, bool>("1-4", true));
	_mapHasMonsterDic.insert(
		std::pair<std::string, bool>("1-5", true));
	_mapHasMonsterDic.insert(
		std::pair<std::string, bool>("2-1", false));
	_mapHasMonsterDic.insert(
		std::pair<std::string, bool>("2-2", false));
	_mapHasMonsterDic.insert(
		std::pair<std::string, bool>("2-3", false));

}

void MonsterManage::createMonstersInstaceList()
{
	if (getMonsterActiveStatus())
	{
		for (int i = 0; i < _monstersIDList.size(); i++)
		{
			if (_monstersIDList[i])
			{
				_monstersInstanceList.push_back(new Monster(_monstersIDList[i]));
			}
		}
	}
}

void MonsterManage::deleteMonstersInstanceList()
{
	for (int i = 0; i < _monstersInstanceList.size(); i++)
	{
		if (_monstersInstanceList[i])
		{ 
			delete _monstersInstanceList[i];
			_monstersInstanceList[i]=NULL;
		}
	}
	_monstersInstanceList.clear();
}

MonsterManage::MonsterManage()
{
	//initDictionary();
	_isMonsterActive = false;
}

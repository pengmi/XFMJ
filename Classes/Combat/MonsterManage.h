#pragma once
#ifndef _MONSTER_MANAGE_H_
#define _MONSTER_MANAGE_H_

#include "Monster.h"
#include<cocos2d.h>

using namespace std;
USING_NS_CC;
class MonsterManage
{
public:
	~MonsterManage();

	static MonsterManage* getInstance();

 	bool setMonsterActiveStatus(bool b);
	bool getMonsterActiveStatus();
	//根据地图名称，获取怪物ID列表
	void setMonstersManageData(string mapname);
	void clearMonstersIDList();
	vector<int> _monstersIDList;

	//怪物实例列表，主要是不想在遇到层物的时候不停的去创建实例
	//直接在怪物管理类中将实例创建，战斗管理调用即可
	vector<Monster*> _monstersInstanceList;
	void createMonstersInstaceList();
	void deleteMonstersInstanceList();
	//static Dictionary _mapAndMonster;
private:
	MonsterManage();
	void initDictionary();
	static MonsterManage * _instance;
	//怪物是否活跃，如果活跃表示会遇怪，否则不会遇怪
	bool _isMonsterActive;
	//地图名字典
	std::map<std::string, bool> _mapHasMonsterDic;
	

};

#endif // !_MONSTER_MANAGER_H_

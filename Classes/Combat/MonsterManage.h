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
	//���ݵ�ͼ���ƣ���ȡ����ID�б�
	void setMonstersManageData(string mapname);
	void clearMonstersIDList();
	vector<int> _monstersIDList;

	//����ʵ���б���Ҫ�ǲ��������������ʱ��ͣ��ȥ����ʵ��
	//ֱ���ڹ���������н�ʵ��������ս��������ü���
	vector<Monster*> _monstersInstanceList;
	void createMonstersInstaceList();
	void deleteMonstersInstanceList();
	//static Dictionary _mapAndMonster;
private:
	MonsterManage();
	void initDictionary();
	static MonsterManage * _instance;
	//�����Ƿ��Ծ�������Ծ��ʾ�����֣����򲻻�����
	bool _isMonsterActive;
	//��ͼ���ֵ�
	std::map<std::string, bool> _mapHasMonsterDic;
	

};

#endif // !_MONSTER_MANAGER_H_

#pragma once
#ifndef _DATA_MANAGE_H_
#define _DATA_MANAGE_H_
#include"cocos2d.h"
#include "json\rapidjson.h"
#include "json\document.h"
#include "Player\PlayerManage.h"
#include "Item\BagManage.h"
#include "Gut\GutManage.h"
#include "Combat\MonsterManage.h"
//#include "Gut\Task.h"
USING_NS_CC;
using namespace std;

class Task;
class NPC;
class GutManage;
class DataManage;
class DataManage
{
	
public:
	DataManage();
	~DataManage();
	static DataManage* getInstance();//�����������ĵ���ģʽ  

	void initData();
	
	void readPlayerManageData(PlayerManage* obj);
	void readHeroStatusNEquipments(HeroLayer *hero,string url= "Player/huangzai.json");

	void readBagData(BagManage* bagManage);

	void readGutData(GutManage* gutManage);
	void readNpcData(NPC* npc,int id);
	void readTaskData(Task* task,int id);

	/*��ȡ��ͼ��Ӧ�Ĺ������ݵ�MonsterManage����*/
	///MonsterManageʵ��
	///��ͼ����
	void readMonsterManage(MonsterManage* monstermanage,string mapName);

	/*�������ݶ�ȡ*/
	///����ID
	///����ʵ��
	void readMonsterData(Monster*monster, int id);

	Item* getItemData(int id);
	void readItemData(int id,Item*);

	Data loadJsonFile(string FileName);
	 //bool saveData();

private:
	string _FileName = "";
	static const int _RES_GUT = 1; // ����ű�
	static class DataManage * _instance;



};

#endif // !_DATA_MANAGE_H_

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
	static DataManage* getInstance();//这种是真正的单例模式  

	void initData();
	
	void readPlayerManageData(PlayerManage* obj);
	void readHeroStatusNEquipments(HeroLayer *hero,string url= "Player/huangzai.json");

	void readBagData(BagManage* bagManage);

	void readGutData(GutManage* gutManage);
	void readNpcData(NPC* npc,int id);
	void readTaskData(Task* task,int id);

	/*读取地图对应的怪物数据到MonsterManage类中*/
	///MonsterManage实例
	///地图名称
	void readMonsterManage(MonsterManage* monstermanage,string mapName);

	/*怪物数据读取*/
	///怪物ID
	///怪物实例
	void readMonsterData(Monster*monster, int id);

	Item* getItemData(int id);
	void readItemData(int id,Item*);

	Data loadJsonFile(string FileName);
	 //bool saveData();

private:
	string _FileName = "";
	static const int _RES_GUT = 1; // 剧情脚本
	static class DataManage * _instance;



};

#endif // !_DATA_MANAGE_H_

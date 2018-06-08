#pragma once
#ifndef _DATA_MODEL_H_
#define _DATA_MODEL_H_
#include"cocos2d.h"
#include<iostream>
using namespace std;

#pragma region Player
//Player
class Status// 玩家状态
{
public:
	Status() {};
	virtual ~Status() {};

	//std::string _playerName;//角色名

	int _level = 1;
	int _levelExperience = 0;
	int _needExperience = 100;

	int _playerMaxLife;//最大活力
	int _playerLife;//现在活力
	int _playerMaxMagic;//最大法力
	int _playerMagic;//现在法力

	int _playerPower;//力量
	int _playerAgility;//身法
	int _playerIntelligence;//灵力

	int _playerAttack;//攻击力
	int _playerDefence;//防御力

	int _playerHit;//命中
	int _playerDodge;//闪避
};
#pragma endregion

#pragma region PlayerManage

class EquipmentsList
{
public:
	EquipmentsList() {};
	~EquipmentsList() {};

	int _weaponID = 0;//武器
	int _headID = 0;//头盔
	int _clothesID = 0;//衣服
	int _cloackID = 0;//披风
	int _gloveID = 0;//手套
	int _tassesID = 0;//裤子
	int _shoesID = 0;//鞋子
	int _ornamentsID = 0;//饰品
};

#pragma endregion

#pragma region Bag&Item
class Item
{
public:
	Item() {};
	~Item() {};

	static Item* create(int id);

	Item* getClassType() { return this; };
	int _itemId = 1001;
	std::string _type = "medicine";
	std::string _itemUrl = "item/1001.png";
	std::string _itemName = "两面针";
	std::string _itemIntro = "最普通的草药,居家旅行必备!";

	int _addMaxLife = 0;//最大生命  
	int _addLife = 100;//现在生命 活力
	int _addMaxMagic = 0;//最大魔法
	int _addMagic = 0;//现在魔法 法力

	int _addPower = 0;//力量
	int _addAgility = 0;//身法
	int _addIntelligence = 0;//灵力

	int _addAttack = 0;//攻击力
	int _addDefence = 0;//防御力

	int _addHit = 0;//命中
	int _addDodge = 0;//闪避

	int _price = 50;//价格
					//物品种类
					//药品，仙药，武器，帽子，衣服，披风，手套，裤子，鞋子，饰品
	/*static const enum ITEMTYPENAME{medicine, forever, weapon, head
					, clothes, cloak, glove, tasses, shoes, ornament};*/
private:
	bool init(int id);
};

struct ItemInBag
{
public:
	Item* item = NULL;
	int num = 0;
};

#pragma endregion




#pragma region GutManage
struct PlayerTaskList
{
public:
	std::vector<int> finished;//已完成列表 
	std::vector<int> ongoing;//正在进行
};
struct PlayerNpcList
{
public:
	std::vector<int> talked;//已对话
	std::vector<int> disable;//已失效，不再出现
};
struct PlayerEnemyList
{
public:
	std::vector<int> combat;//已战斗
};

#pragma endregion


#pragma region Task
////////////////task

struct startCondition
{
	int _finishedTaskID;
	int _ongoingTaskID;
};
struct finishCondition
{
	int _finishTaskID;
	int _talkTo;
	int _combatTo;
};

struct taskReward
{
	int _exp;
	int _getItemID;
	int _deleteNPCID;
};

struct taskConv
{
	//接任务时对话列表
	std::vector<string> _beginTaskConv;
	//做任务时对话列表
	std::vector<string> _doingTaskConv;
	//完成时对话列表
	std::vector<string> _finishTaskConv;
};

////////////
#pragma endregion
#pragma region NPC
////////////////NPC

struct NPCType
{
	int _type;
	vector<int> _typeData;
};

////////////
#pragma endregion

#endif // !_DATA_MODEL_H_

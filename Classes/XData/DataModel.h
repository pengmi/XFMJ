#pragma once
#ifndef _DATA_MODEL_H_
#define _DATA_MODEL_H_
#include"cocos2d.h"
#include<iostream>
using namespace std;

#pragma region Player
//Player
class Status// ���״̬
{
public:
	Status() {};
	virtual ~Status() {};

	//std::string _playerName;//��ɫ��

	int _level = 1;
	int _levelExperience = 0;
	int _needExperience = 100;

	int _playerMaxLife;//������
	int _playerLife;//���ڻ���
	int _playerMaxMagic;//�����
	int _playerMagic;//���ڷ���

	int _playerPower;//����
	int _playerAgility;//��
	int _playerIntelligence;//����

	int _playerAttack;//������
	int _playerDefence;//������

	int _playerHit;//����
	int _playerDodge;//����
};
#pragma endregion

#pragma region PlayerManage

class EquipmentsList
{
public:
	EquipmentsList() {};
	~EquipmentsList() {};

	int _weaponID = 0;//����
	int _headID = 0;//ͷ��
	int _clothesID = 0;//�·�
	int _cloackID = 0;//����
	int _gloveID = 0;//����
	int _tassesID = 0;//����
	int _shoesID = 0;//Ь��
	int _ornamentsID = 0;//��Ʒ
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
	std::string _itemName = "������";
	std::string _itemIntro = "����ͨ�Ĳ�ҩ,�Ӽ����бر�!";

	int _addMaxLife = 0;//�������  
	int _addLife = 100;//�������� ����
	int _addMaxMagic = 0;//���ħ��
	int _addMagic = 0;//����ħ�� ����

	int _addPower = 0;//����
	int _addAgility = 0;//��
	int _addIntelligence = 0;//����

	int _addAttack = 0;//������
	int _addDefence = 0;//������

	int _addHit = 0;//����
	int _addDodge = 0;//����

	int _price = 50;//�۸�
					//��Ʒ����
					//ҩƷ����ҩ��������ñ�ӣ��·������磬���ף����ӣ�Ь�ӣ���Ʒ
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
	std::vector<int> finished;//������б� 
	std::vector<int> ongoing;//���ڽ���
};
struct PlayerNpcList
{
public:
	std::vector<int> talked;//�ѶԻ�
	std::vector<int> disable;//��ʧЧ�����ٳ���
};
struct PlayerEnemyList
{
public:
	std::vector<int> combat;//��ս��
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
	//������ʱ�Ի��б�
	std::vector<string> _beginTaskConv;
	//������ʱ�Ի��б�
	std::vector<string> _doingTaskConv;
	//���ʱ�Ի��б�
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

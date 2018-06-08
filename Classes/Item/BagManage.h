#pragma once
#ifndef _BAG_MANAGE_H_
#define _BAG_MANAGE_H_

#include "XData\DataModel.h"
#include "Player\HeroLayer.h"

class BagManage
{
public:
	~BagManage();//主要是delete 所有new 出的空间
	static BagManage* getInstance();

	//一个装备栏（装备ID放在hero类里），这里主要存放装备数据的
	ItemInBag Equipment[8] ;//装备栏
	//两个背包
	ItemInBag BagOne[3][5] ;//全部放item实例
	ItemInBag BagTwo[3][5] ;//全部放item实例

	int getEmptyCellsNum();
	ItemInBag* getEmptyCellPos();
	ItemInBag* insertItemToBag(int itemid=0,int num=1);
	//返回item剩下数量，用来判断是否隐藏操作按钮
	int deleteItemFromBag(Item * item, int num);
	void deleteItemFromBag(ItemInBag * iteminbag,int num);
	void deleteItemFromBag(int itemid,int num);
	//找到空格子位置

	//装备栏必须先释放再新建，背包也是同样的道理
	void deletePlayerEquipmentData();
	void loadPlayerEquipmentData(HeroLayer * h);
	void insertEquipment(ItemInBag *iib);
	bool checkIsCanEquipment(Item* item);

	/*因为在datamanage里面使用了new所以要delete*/
	void deleteBagData();
	
	/*针对背包数据的操作放在bagui里面，
	因为那里记录了背包值，更方便一些*/
	//void loadBagData();
	//void addItemToBag();
	//void removeItemToBag();

	//void readItem(int itemID,Item* item);

	int& getMoney();
	int& setMoney(int i=0);
	int& addMoney(int i = 0);
	int& subMoney(int i = 0);


private:
	BagManage();
	int _money = 0;
	static BagManage* _instance;
};



#endif // !_BAG_H_

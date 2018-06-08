#pragma once
#ifndef _BAG_H_
#define _BAG_H_

#include "PlayerStatusUI.h"
USING_NS_CC;

class BagUI:public PlayerStatusUI
{
public:
	CREATE_FUNC(BagUI);
	virtual bool init();
	
	void setBagBack();
	void setEquipBack();

	//删除菜单项
	void removeItemCells();
	void removeBagItemCell(MenuItem* itemPtr);
	void loadBagData(int i=1);
	void loadItem();
	void updateBagData(int &a,int &b);
	//找到空格子位,更新图标
	bool addToCellInBagAndItem(ItemInBag * itemIB);

	void clearEquipmentData();
	void removeEquipment(MenuItem*);
	void loadEquipmentData();

	void clearListItemInfo();
	void listItemInfo(ItemInBag * itemIB);

	//点击物品项以后的ui加载
	void clearSelectedOperationUI();
	void hideSelectedOperationUI();
	void viewSelectedOperationUI();
	void setSelectedOperationUI(cocos2d::Ref * pSender, ItemInBag * itemIB);
	void setEquipmentOperationUI(cocos2d::Ref * pSender, ItemInBag * itemIB);

	/*
	点击物品以后，如果物品存在，弹出右边选项
	1.如果是药品，或者使用永久属性物品，使用或丢弃
	2.如果是装备物品，装备或丢弃。
	3.如果已经装备，查看或卸下
	*/
	void menuClickEmpty(cocos2d::Ref * pSender) {};
	//点击加载背包
	void menuClickLoadBag(cocos2d::Ref * pSender,int n=1);
	//点击人物图标加载玩家数据
	void menuClickLoadData(cocos2d::Ref * pSender, HeroLayer *s);
	//点击显示信息和加载操作按钮
	void itemClickLoadBagItemInfo(cocos2d::Ref * pSender, ItemInBag * itemIB);
	//点击显示信息和加载操作按钮
	void itemClickLoadEquipmentInfo(cocos2d::Ref * pSender, ItemInBag * itemIB);
	//点击显示信息
	void itemClickShowInfo(cocos2d::Ref * pSender, ItemInBag * itemIB);

	//使用item分别传入this,背包中物品，图标指针
	void useItem(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr);
	//装备按钮
	void equipItem(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr);
	//物品数量-1，不删除实例
	//void equipNumReduce(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr);
	//卸下按钮
	void unequipItem(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr);
	//删除item
	void deleteItem(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr);
	//物品数量-1，要删除实例
	void itemNumReduce(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr);
	//查看按钮
	void viewItem(cocos2d::Ref * pSender, ItemInBag * itemIB);
	//清楚所有选择按钮
	//void clearAllOperationItem();

	//提示信息
	void popMsgLabel(std::string str);
	void deleteNode(cocos2d::Node * pSender);
	void deleteMsgLabel(cocos2d::Node * pSender);
	//单个物品处理（卸下）
	
	void cleanup();
	void removeMsgLabelList();
private:

	vector<LabelTTF*> _msgLabelList;

	Sprite* _bagback = NULL;//背包背景
	Sprite* _equipback = NULL;//装备背景

	Label * _money = NULL;
	
	MenuItem * _one = NULL;//背包一按钮
	MenuItem * _two = NULL;//背包二按钮
	//int _curBag=1;
	ItemInBag (*_tmpBag)[5] ;

	MenuItem * _imageItem[3][5] = {NULL};
	Menu * _bagIndex = NULL;//按钮容器

	MenuItem * _equipItem[8] = { NULL };
	Menu* _equipMenu = NULL;//装备的菜单容器

	MenuItem * _useItem = NULL;//使用/装备按钮
	MenuItem * _deleteItem = NULL;//丢弃按钮
	Menu * _selectedMenu = NULL;//选择物品时的菜单容器


};



#endif // !_BAG_H_

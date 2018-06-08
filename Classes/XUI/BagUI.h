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

	//ɾ���˵���
	void removeItemCells();
	void removeBagItemCell(MenuItem* itemPtr);
	void loadBagData(int i=1);
	void loadItem();
	void updateBagData(int &a,int &b);
	//�ҵ��ո���λ,����ͼ��
	bool addToCellInBagAndItem(ItemInBag * itemIB);

	void clearEquipmentData();
	void removeEquipment(MenuItem*);
	void loadEquipmentData();

	void clearListItemInfo();
	void listItemInfo(ItemInBag * itemIB);

	//�����Ʒ���Ժ��ui����
	void clearSelectedOperationUI();
	void hideSelectedOperationUI();
	void viewSelectedOperationUI();
	void setSelectedOperationUI(cocos2d::Ref * pSender, ItemInBag * itemIB);
	void setEquipmentOperationUI(cocos2d::Ref * pSender, ItemInBag * itemIB);

	/*
	�����Ʒ�Ժ������Ʒ���ڣ������ұ�ѡ��
	1.�����ҩƷ������ʹ������������Ʒ��ʹ�û���
	2.�����װ����Ʒ��װ��������
	3.����Ѿ�װ�����鿴��ж��
	*/
	void menuClickEmpty(cocos2d::Ref * pSender) {};
	//������ر���
	void menuClickLoadBag(cocos2d::Ref * pSender,int n=1);
	//�������ͼ������������
	void menuClickLoadData(cocos2d::Ref * pSender, HeroLayer *s);
	//�����ʾ��Ϣ�ͼ��ز�����ť
	void itemClickLoadBagItemInfo(cocos2d::Ref * pSender, ItemInBag * itemIB);
	//�����ʾ��Ϣ�ͼ��ز�����ť
	void itemClickLoadEquipmentInfo(cocos2d::Ref * pSender, ItemInBag * itemIB);
	//�����ʾ��Ϣ
	void itemClickShowInfo(cocos2d::Ref * pSender, ItemInBag * itemIB);

	//ʹ��item�ֱ���this,��������Ʒ��ͼ��ָ��
	void useItem(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr);
	//װ����ť
	void equipItem(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr);
	//��Ʒ����-1����ɾ��ʵ��
	//void equipNumReduce(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr);
	//ж�°�ť
	void unequipItem(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr);
	//ɾ��item
	void deleteItem(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr);
	//��Ʒ����-1��Ҫɾ��ʵ��
	void itemNumReduce(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr);
	//�鿴��ť
	void viewItem(cocos2d::Ref * pSender, ItemInBag * itemIB);
	//�������ѡ��ť
	//void clearAllOperationItem();

	//��ʾ��Ϣ
	void popMsgLabel(std::string str);
	void deleteNode(cocos2d::Node * pSender);
	void deleteMsgLabel(cocos2d::Node * pSender);
	//������Ʒ����ж�£�
	
	void cleanup();
	void removeMsgLabelList();
private:

	vector<LabelTTF*> _msgLabelList;

	Sprite* _bagback = NULL;//��������
	Sprite* _equipback = NULL;//װ������

	Label * _money = NULL;
	
	MenuItem * _one = NULL;//����һ��ť
	MenuItem * _two = NULL;//��������ť
	//int _curBag=1;
	ItemInBag (*_tmpBag)[5] ;

	MenuItem * _imageItem[3][5] = {NULL};
	Menu * _bagIndex = NULL;//��ť����

	MenuItem * _equipItem[8] = { NULL };
	Menu* _equipMenu = NULL;//װ���Ĳ˵�����

	MenuItem * _useItem = NULL;//ʹ��/װ����ť
	MenuItem * _deleteItem = NULL;//������ť
	Menu * _selectedMenu = NULL;//ѡ����Ʒʱ�Ĳ˵�����


};



#endif // !_BAG_H_

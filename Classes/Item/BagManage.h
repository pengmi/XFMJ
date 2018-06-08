#pragma once
#ifndef _BAG_MANAGE_H_
#define _BAG_MANAGE_H_

#include "XData\DataModel.h"
#include "Player\HeroLayer.h"

class BagManage
{
public:
	~BagManage();//��Ҫ��delete ����new ���Ŀռ�
	static BagManage* getInstance();

	//һ��װ������װ��ID����hero�����������Ҫ���װ�����ݵ�
	ItemInBag Equipment[8] ;//װ����
	//��������
	ItemInBag BagOne[3][5] ;//ȫ����itemʵ��
	ItemInBag BagTwo[3][5] ;//ȫ����itemʵ��

	int getEmptyCellsNum();
	ItemInBag* getEmptyCellPos();
	ItemInBag* insertItemToBag(int itemid=0,int num=1);
	//����itemʣ�������������ж��Ƿ����ز�����ť
	int deleteItemFromBag(Item * item, int num);
	void deleteItemFromBag(ItemInBag * iteminbag,int num);
	void deleteItemFromBag(int itemid,int num);
	//�ҵ��ո���λ��

	//װ�����������ͷ����½�������Ҳ��ͬ���ĵ���
	void deletePlayerEquipmentData();
	void loadPlayerEquipmentData(HeroLayer * h);
	void insertEquipment(ItemInBag *iib);
	bool checkIsCanEquipment(Item* item);

	/*��Ϊ��datamanage����ʹ����new����Ҫdelete*/
	void deleteBagData();
	
	/*��Ա������ݵĲ�������bagui���棬
	��Ϊ�����¼�˱���ֵ��������һЩ*/
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

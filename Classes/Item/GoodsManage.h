#pragma once
#ifndef _GOODS_MANAGE_H_
#define _GOODS_MANAGE_H_

#include <cocos2d.h>
USING_NS_CC;
using namespace std;

class GoodsManage
{
public:
	~GoodsManage();
	static GoodsManage* getInstance();
	
	//ͨ��id����Ʒʵ����
	//����������������Ϊֱ����Ҫ��ȡ��ǰ��Ʒ�б�
	vector<class Item*>* getGoodsInstanceList(class NPC* merchant=NULL);
	
	Item* getItemFromGoodsInstanceList(int itemid=0);

	void deleteGoodsInstanceList();

	//����Ʒ����Ʒ������,����Ʒ�ڱ���������
	void buyGoods(int id,int num);

	int sellItem(int id,int num);

	int _tempMerchantId;
	vector<class Item*> _goodsInstanceList;//��Ʒʵ��
private:
	GoodsManage();
	static GoodsManage* _instance;
	
};

#endif // !_GOODS_MANAGE_H_

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
	
	//通过id将商品实例化
	//如果不输入参数，即为直接想要获取当前商品列表
	vector<class Item*>* getGoodsInstanceList(class NPC* merchant=NULL);
	
	Item* getItemFromGoodsInstanceList(int itemid=0);

	void deleteGoodsInstanceList();

	//买物品在商品管理里,卖物品在背包管理里
	void buyGoods(int id,int num);

	int sellItem(int id,int num);

	int _tempMerchantId;
	vector<class Item*> _goodsInstanceList;//商品实例
private:
	GoodsManage();
	static GoodsManage* _instance;
	
};

#endif // !_GOODS_MANAGE_H_

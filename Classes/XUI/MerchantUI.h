#pragma once
#ifndef _MERCHANT_UI_H_
#define _MERCHANT_UI_H_

#include<cocos2d.h>

USING_NS_CC;
using namespace std;

class MerchantUI :public Layer
{
public:
	static MerchantUI* create();

	bool init();
	//设置背景
	void setBackGround();
	void initData();
	//设置点击事件，主要用来屏蔽点击事件
	void initMenu();
	void initTouch();
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *user_event) { return 1; };
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *user_event) {};
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *user_evenr) {};

	//加载商品菜单及菜单项
	void menuClickLoadGoods(cocos2d::Ref * pSender) ;
	void setGoodsMenuUI();
	//加载背包菜单及菜单项
	void menuClickLoadBag(cocos2d::Ref * pSender,bool option=false) ;
	void setBagMenuUI();
	//清空UI数组
	void clearGoodsMenuUI();
	//关闭背包
	void menuClickClose(cocos2d::Ref * pSender);


	//点击物品项以后的ui加载
	//void hideSelectedOperationUI();//隐藏
	//void viewSelectedOperationUI();//显示

	//弹出提示信息
	void popMsgLabel(std::string str);

	//点击显示物品信息
	void listItemInfo(cocos2d::Ref * pSender, class Item * item,int num=0);
	//点击物品以后，加载以下4个操作按钮
	void itemClickLoadOperateUI(cocos2d::Ref * pSender, Item * item,int num=0);
	//清除操作按钮
	void clearOperateUI();
	void hideOperateUI();
	void visiableOperateUI();
	//购买物品按钮回调函数
	//数据处理在GoodsManage里面进行
	void menuClickConfirmBuy(cocos2d::Ref * pSender, int itemid);
	/*出售物品按钮回调函数
	数据处理在BagManage里面进行
	*/
	void menuClickConfirmSell(cocos2d::Ref * pSender,Item *item);
	//增加操作数量
	void menuClickAddOperateNum(cocos2d::Ref * pSender,int numInBag=0);
	//减少操作数量
	void menuClickSubOperateNum(cocos2d::Ref * pSender);

	void refreshNumLabel();
	void refreshMoneyLabel();
private:

	int _itemNum;

	int _operateType;

	//金钱，图标
	Label * _moneyLabel = NULL;
	Label * _numLabel = NULL;
						   //int _curBag=1;
	Sprite* _bagback1 = NULL;//背包背景
	Sprite* _bagback2 = NULL;//背包背景

	MenuItem * _closeItem = NULL;//退出商店按钮
	MenuItem * _goodsItem = NULL;//切换到商品按钮
	MenuItem * _bagItem = NULL;//切换到背包按钮
	MenuItem * _imageItemLeft[3][5] = { NULL };
	MenuItem * _imageItemRight[3][5] = { NULL };
	Menu * _itemsMenu = NULL;//按钮容器



	MenuItem * _confirmBuyItem = NULL;//购买按钮
	MenuItem * _confirmSellItem = NULL;//出售按钮
	MenuItem * _subNumItem = NULL;//数量减按钮
	MenuItem * _addNumItem = NULL;//数量加按钮
	Menu * _selectedMenu = NULL;//选择物品时的菜单容器
};

#endif // !1


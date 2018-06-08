#pragma once
#ifndef _ITEM_INFO_H_
#define _ITEM_INFO_H_
#include <cocos2d.h>
#include "XData\DataModel.h"

USING_NS_CC;

class ItemInfoUI:public Layer 
{
public:
	CREATE_FUNC(ItemInfoUI);
	bool init();
	//设置层背景
	//层点击事件
	//事件结束后移除信息层
	virtual bool onTouchBegan(cocos2d::Touch *touch, 
		cocos2d::Event *user_event);
	virtual void onTouchEnded(cocos2d::Touch *touch,
		cocos2d::Event *user_event);
	//列出物品中不为0的信息（有用的信息）
	void listItemInfo(ItemInBag *IIb);
	void listItemInfo(Item *item,int num=0);
	
private:
	void initItemMap();
	void deleteItemMap();
	void initTouch();
	std::map<std::string, std::string> *_map=NULL;
};


#endif // !_ITEM_INFO_H_

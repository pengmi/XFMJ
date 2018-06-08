#pragma once

#ifndef _PLAYER_STATUS_UI_H_
#define _PLAYER_STATUS_UI_H_
#include "cocos2d.h"
#include "XData\DataModel.h"
#include "Player\BasePlayerLayer.h"
#include "Gut\NPC.h"
#include "XData\Global.h"
#include "tool\WStrToUTF8.h"

USING_NS_CC;


class PlayerStatusUI :public BaseUI
{
public:
	~PlayerStatusUI();
	// implement the "static create()" method manually
	//CREATE_FUNC(PlayerStatusUI);
	static PlayerStatusUI* create();
	//static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void initMenu();
	void loadStatusUi(HeroLayer* hero);
	void loadStatusCallback(Ref* hero);
	virtual void initTouch();
	virtual void setCurHero(HeroLayer *s);
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual void menuClickLoadData(cocos2d::Ref * pSender, 
		HeroLayer *s);

	//control
protected:
	HeroLayer* _curHero = NULL;//当前选择的英雄
private:
	MenuItem* _huangZaiItem;
	MenuItem* _CMItem;
	MenuItem* _lianItem;
};


#endif _PLAYER_STATUS_UI_H_
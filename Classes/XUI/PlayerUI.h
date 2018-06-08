#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "cocos2d.h"
#include "XData\DataModel.h"
#include "Player\BasePlayerLayer.h"
#include "Gut\NPC.h"
#include "XData\Global.h"
#include "tool\WStrToUTF8.h"
#include "BaseUI.h"
#include "PlayerStatusUI.h"
#include "BagUI.h"

USING_NS_CC;
class PlayerUI :public BaseUI
{
public:
	// implement the "static create()" method manually
	//CREATE_FUNC(PlayerUI);
	static PlayerUI* create();
	//static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void initBackground();
	virtual void initMenu();
	virtual void initTouch();
	//管理加载页面
	virtual void loadPlayerStatusMenuUI(Ref* pS);//加载状态界面
	virtual void loadPlayerBagMenuUI(Ref* pS);//加载状态界面
	//virtual void loadPlayerEquipMenuUI(Ref* pS);//加载状态界面
	virtual void loadPlayerSkillMenuUI(Ref* pS);//加载状态界面
	virtual void loadPlayerTaskMenuUI(Ref* pS);//加载状态界面
											   // a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

private:

	LayerMultiplex * _layerMuticomplex;
	class BaseUI * _layer1 = NULL;//人物属性
	class BaseUI * _layer2 = NULL;//装备，背包
 	class BaseUI * _layer3 = NULL;//人物技能
	class BaseUI * _layer4 = NULL;//对话日志
	//control
};



#endif _PLAYER_H_
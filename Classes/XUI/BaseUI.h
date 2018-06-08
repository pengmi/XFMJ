#pragma once

#ifndef _BASEUI_H_
#define _BASEUI_H_
#include "cocos2d.h"
#include "XData\DataModel.h"
#include "Player\BasePlayerLayer.h"
#include "Gut\NPC.h"
#include "XData\Global.h"
#include "tool\WStrToUTF8.h"
#include "Player\PlayerManage.h"
#include "XData\DataModel.h"
#include "Gut\Task.h"

USING_NS_CC;

class PlayerUI;
class PlayerStatusUI;
class ConvUI;

class BaseUI :public cocos2d::Layer
{
public:
	// implement the "static create()" method manually
	CREATE_FUNC(BaseUI);
	//static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void initBackground();//初始化背景图片，很多时候不需要
	virtual void initMenu();
	virtual void initTouch();

	//界面管理
	virtual void loadPlayerMenuUI(Ref* pS);//加载状态界面
	//virtual void loadPlayerStatusMenuUI(Ref* pS);//加载状态界面
	//virtual void loadPlayerEquipMenuUI(Ref* pS);//加载状态界面
	//virtual void loadPlayerSkillMenuUI(Ref* pS);//加载状态界面
	//virtual void loadPlayerTaskMenuUI(Ref* pS);//加载状态界面
	virtual void loadSystemMenuUI(Ref* pS);//加载状态界面
	virtual void closeMenuUI(Ref* pS);//关掉最上层界面
	virtual void loadNpcNormalConvUI(class NPC *npc, //加载与Npc的对话
		std::vector<NPC*> *npcVec);

	void loadTaskBeginUI(class Task* task, class NPC *npc,//加载任务对话
		std::vector<NPC*> *npcVec);
	void loadTaskDoingUI(class Task* task, class NPC *npc,//加载任务对话
		std::vector<NPC*> *npcVec);
	void loadTaskEndUI(class Task* task, class NPC *npc,//加载任务对话
		std::vector<NPC*> *npcVec);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	//control

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *user_event) { return 1; };
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *user_event) {};
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *user_evenr) {};

	//data
	//virtual void setPlayerData(const Status& sta);//暂时只有一个参数 ，实际上要至少三个参数
//	virtual void setPlayerData(BasePlayerLayer* hz, BasePlayerLayer*, BasePlayerLayer*);
//	virtual void setPlayerData(BasePlayerLayer** p3);
	//virtual BasePlayerLayer** getPlayerData();//暂时写成Status* ，实际上要返回数据

protected:
	Sprite *_backsprite=NULL;
	Menu *_baseMenu=NULL;//基础菜单
						 //BaseUI不需要的,二级菜单下的子菜单层
//	BasePlayerLayer * _player[3];//hz,cm,lian/0,1,2
	
};










#endif // !_BASEUI_H_

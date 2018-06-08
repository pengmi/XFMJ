#pragma once
#ifndef _CONV_UI_H_
#define _CONV_UI_H_
#include "cocos2d.h"
#include "XData\DataModel.h"
#include "Player\BasePlayerLayer.h"
#include "Gut\NPC.h"
#include "XData\Global.h"
#include "tool\WStrToUTF8.h"
#include "BaseUI.h"
#include "PlayerStatusUI.h"

USING_NS_CC;

class NPCNormalConvUI :public BaseUI
{
public:
	// implement the "static create()" method manually

	static NPCNormalConvUI* create(class NPC *npc, std::vector<NPC*> *npcVec);

	virtual bool init(class NPC *npc,
		std::vector<NPC*> *npcVec);
	virtual void initBackground();
	void popMsgLabel(std::string str="");
	virtual void initTouch();
	void menuCloseCallback(cocos2d::Ref* pSender) {};
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *user_event);
	//control
protected:

	BaseUI* _parentLayer;

	LabelTTF *_convLabel = NULL;
	std::vector<std::string> _conStr;
	int _index = 0;

	class NPC * _operateNPC = NULL;
	std::vector<class NPC*> *_npcVector = NULL;
};

class TaskBeginConvUI :public NPCNormalConvUI
{
public:
	static TaskBeginConvUI* create(Task * task,class NPC *npc, std::vector<NPC*> *npcVec);

	virtual bool init(Task * task, class NPC *npc, std::vector<NPC*> *npcVec);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *user_event);
protected:
	Task * _curTask=NULL;
};

class TaskDoingConvUI :public NPCNormalConvUI
{
public:
	static TaskDoingConvUI* create(Task * task, class NPC *npc, std::vector<NPC*> *npcVec);

	virtual bool init(Task * task, class NPC *npc, std::vector<NPC*> *npcVec);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *user_event);
protected:
	Task * _curTask = NULL;
};

class TaskEndConvUI :public TaskDoingConvUI
{
public:
	static TaskEndConvUI* create(Task * task, class NPC *npc, std::vector<NPC*> *npcVec);

	virtual bool init(Task * task, class NPC *npc, std::vector<NPC*> *npcVec);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *user_event);
	
protected:
};


#endif _CONV_UI_H_
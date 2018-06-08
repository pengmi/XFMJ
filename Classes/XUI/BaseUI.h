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
	virtual void initBackground();//��ʼ������ͼƬ���ܶ�ʱ����Ҫ
	virtual void initMenu();
	virtual void initTouch();

	//�������
	virtual void loadPlayerMenuUI(Ref* pS);//����״̬����
	//virtual void loadPlayerStatusMenuUI(Ref* pS);//����״̬����
	//virtual void loadPlayerEquipMenuUI(Ref* pS);//����״̬����
	//virtual void loadPlayerSkillMenuUI(Ref* pS);//����״̬����
	//virtual void loadPlayerTaskMenuUI(Ref* pS);//����״̬����
	virtual void loadSystemMenuUI(Ref* pS);//����״̬����
	virtual void closeMenuUI(Ref* pS);//�ص����ϲ����
	virtual void loadNpcNormalConvUI(class NPC *npc, //������Npc�ĶԻ�
		std::vector<NPC*> *npcVec);

	void loadTaskBeginUI(class Task* task, class NPC *npc,//��������Ի�
		std::vector<NPC*> *npcVec);
	void loadTaskDoingUI(class Task* task, class NPC *npc,//��������Ի�
		std::vector<NPC*> *npcVec);
	void loadTaskEndUI(class Task* task, class NPC *npc,//��������Ի�
		std::vector<NPC*> *npcVec);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	//control

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *user_event) { return 1; };
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *user_event) {};
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *user_evenr) {};

	//data
	//virtual void setPlayerData(const Status& sta);//��ʱֻ��һ������ ��ʵ����Ҫ������������
//	virtual void setPlayerData(BasePlayerLayer* hz, BasePlayerLayer*, BasePlayerLayer*);
//	virtual void setPlayerData(BasePlayerLayer** p3);
	//virtual BasePlayerLayer** getPlayerData();//��ʱд��Status* ��ʵ����Ҫ��������

protected:
	Sprite *_backsprite=NULL;
	Menu *_baseMenu=NULL;//�����˵�
						 //BaseUI����Ҫ��,�����˵��µ��Ӳ˵���
//	BasePlayerLayer * _player[3];//hz,cm,lian/0,1,2
	
};










#endif // !_BASEUI_H_

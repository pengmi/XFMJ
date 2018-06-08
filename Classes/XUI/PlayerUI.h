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
	//�������ҳ��
	virtual void loadPlayerStatusMenuUI(Ref* pS);//����״̬����
	virtual void loadPlayerBagMenuUI(Ref* pS);//����״̬����
	//virtual void loadPlayerEquipMenuUI(Ref* pS);//����״̬����
	virtual void loadPlayerSkillMenuUI(Ref* pS);//����״̬����
	virtual void loadPlayerTaskMenuUI(Ref* pS);//����״̬����
											   // a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

private:

	LayerMultiplex * _layerMuticomplex;
	class BaseUI * _layer1 = NULL;//��������
	class BaseUI * _layer2 = NULL;//װ��������
 	class BaseUI * _layer3 = NULL;//���＼��
	class BaseUI * _layer4 = NULL;//�Ի���־
	//control
};



#endif _PLAYER_H_
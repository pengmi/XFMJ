#pragma once
#ifndef _COMBAT_H_
#define _COMBAT_H_
#include <cocos2d.h>
USING_NS_CC;
using namespace std;

class CombatUI:public Layer
{
public:
	//自动管理内存,减少工作量
	CREATE_FUNC(CombatUI);

	bool init();
	//设置背景
	void setBackGround();
	void initMonsterSprite();
	//初始化战斗场景中角色图片，添加到战斗管理列表中
	void initPlayerSprite();
	//设置弹出动画
	void initAction();
	void setPlayerControlDisactive(cocos2d::Node * pSender);
	void setPlayerControlActive(cocos2d::Node * pSender);
	//设置点击事件，主要用来屏蔽点击事件
	void initMenu();
	void clearMenu();
	void initTouch();
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *user_event) { return 1; };
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *user_event) {};
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *user_evenr) {};

	void setCombatTurn();

	Point getTurnPosition();

	void viewTarget(cocos2d::Ref * pSender,class Monster* sprite);
	//清楚所有选择按钮
	//void clearAllOperationItem();
	//隐藏/显示操作按钮,攻击，法术等
	void hideOperationItem();
	void viewOperationItem(cocos2d::Node * pSender);
	void hideTurnSprite();
	void viewTurnSprite(cocos2d::Node * pSender);

	/*战斗*/
	//普通攻击
	void caclulatePlayerDamage(cocos2d::Node * pSender);
	void caclulateMonsterDamage(cocos2d::Node * pSender);
	
	//怪物行动
	void monstersAct(float dt);
	void monsterAttack(float dt,Monster* monster);
	//战斗结束后处理
	void afterAttack(cocos2d::Node * pSender);
	//战斗结束后处理
	void afterMonsterAttack(cocos2d::Node * pSender);
	//接收计算伤害的通知
	void receiveCaclulateNotification(Ref* data);
	//接收怪物攻击完后的通知
	void receiveMonsterAttackFinishNotification(Ref* data);
	//提示信息
	void popMsgLabel(std::string str);
	//逃跑点击事件
	void runawayClick(cocos2d::Ref * pSender);
	//攻击点击事件
	void attackClick(cocos2d::Ref * pSender);
	//背包点击事件
	void bagClick(cocos2d::Ref * pSender);
	//技能点击事件
	void skillClick(cocos2d::Ref * pSender);
	void deleteNode(cocos2d::Node * pSender);
	//bool _operateStatus;

	//清除，继承自Layer，Layer切换的时候就会调用，
	void cleanup();

private:

	Sprite* _backsprite=NULL;

	Sprite* _combatTurn=NULL;

	Sprite* _playerOne = NULL;
	Sprite* _playerTwo = NULL;
	Sprite* _playerThree = NULL;

	Menu * _operateMenu;
	MenuItem* _operateAttackItem;//攻击
	MenuItem* _operateRunawayItem;//逃跑
	MenuItem* _operateSkillItem;//技能
	MenuItem* _operateBagItem;//背包
};

#endif // !_COMBAT_H_

#pragma once
#ifndef _COMBAT_H_
#define _COMBAT_H_
#include <cocos2d.h>
USING_NS_CC;
using namespace std;

class CombatUI:public Layer
{
public:
	//�Զ������ڴ�,���ٹ�����
	CREATE_FUNC(CombatUI);

	bool init();
	//���ñ���
	void setBackGround();
	void initMonsterSprite();
	//��ʼ��ս�������н�ɫͼƬ����ӵ�ս�������б���
	void initPlayerSprite();
	//���õ�������
	void initAction();
	void setPlayerControlDisactive(cocos2d::Node * pSender);
	void setPlayerControlActive(cocos2d::Node * pSender);
	//���õ���¼�����Ҫ�������ε���¼�
	void initMenu();
	void clearMenu();
	void initTouch();
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *user_event) { return 1; };
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *user_event) {};
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *user_evenr) {};

	void setCombatTurn();

	Point getTurnPosition();

	void viewTarget(cocos2d::Ref * pSender,class Monster* sprite);
	//�������ѡ��ť
	//void clearAllOperationItem();
	//����/��ʾ������ť,������������
	void hideOperationItem();
	void viewOperationItem(cocos2d::Node * pSender);
	void hideTurnSprite();
	void viewTurnSprite(cocos2d::Node * pSender);

	/*ս��*/
	//��ͨ����
	void caclulatePlayerDamage(cocos2d::Node * pSender);
	void caclulateMonsterDamage(cocos2d::Node * pSender);
	
	//�����ж�
	void monstersAct(float dt);
	void monsterAttack(float dt,Monster* monster);
	//ս����������
	void afterAttack(cocos2d::Node * pSender);
	//ս����������
	void afterMonsterAttack(cocos2d::Node * pSender);
	//���ռ����˺���֪ͨ
	void receiveCaclulateNotification(Ref* data);
	//���չ��﹥������֪ͨ
	void receiveMonsterAttackFinishNotification(Ref* data);
	//��ʾ��Ϣ
	void popMsgLabel(std::string str);
	//���ܵ���¼�
	void runawayClick(cocos2d::Ref * pSender);
	//��������¼�
	void attackClick(cocos2d::Ref * pSender);
	//��������¼�
	void bagClick(cocos2d::Ref * pSender);
	//���ܵ���¼�
	void skillClick(cocos2d::Ref * pSender);
	void deleteNode(cocos2d::Node * pSender);
	//bool _operateStatus;

	//������̳���Layer��Layer�л���ʱ��ͻ���ã�
	void cleanup();

private:

	Sprite* _backsprite=NULL;

	Sprite* _combatTurn=NULL;

	Sprite* _playerOne = NULL;
	Sprite* _playerTwo = NULL;
	Sprite* _playerThree = NULL;

	Menu * _operateMenu;
	MenuItem* _operateAttackItem;//����
	MenuItem* _operateRunawayItem;//����
	MenuItem* _operateSkillItem;//����
	MenuItem* _operateBagItem;//����
};

#endif // !_COMBAT_H_

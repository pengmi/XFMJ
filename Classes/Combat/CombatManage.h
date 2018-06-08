#pragma once
#ifndef _COMBAT_MANAGE_H_
#define _COMBAT_MANAGE_H_
#include <cocos2d.h>
#include "Monster.h"
using namespace std;
USING_NS_CC;

class CombatManage
{
public:
	~CombatManage();
	static CombatManage* getInstance();

	Monster* _combatTargetsList[3];
	Layer * _combatCharacterList[3];
	void initCombatTargetsList();
	bool isGetMonsters();
	//����������������ز�Ϊ�գ���ʾ���֣��������֡�
	/*һ��Ҫ����parent�ڵ㣬��Ϊsprite���Զ��ͷ��ڴ�ģ�
	���û�����þͻ�ܿ��ͷ�,����Ҫ�ڴ���sprite�Ժ����ϼ���ڵ�
	�����ͱ�������޷�Ԥ�ϵ�����*/
	Monster** createMonstersRandom(Node* parent);
	//��ʼ������
	void initIndexNStatus();
	void finishOneStep();
	//���һ�������ж�һ�Σ����ȫ���ж�����ʾ�棬����Ϊ��
	//״̬�ı��ں��������
	bool addPlayerIndex();
	
	//����һ���ж�һ�Σ����ȫ���ж�����ʾ�棬����Ϊ��
	//״̬�ı��ں��������
	bool addMonsterIndex();
	void deleteMonsters();
	//��ȡ�����Ĺ���
	Monster** getMonsters();

	//�Թ�����й���
	//����˺�ֵ
	void caculatePlayerDamage();
	int getDamageValue(class  Status const *status);
	//�Ƿ�ʤ��
	bool isSuccess();

	void caculateMonsterDamage();
	int getDamageValue(class  Monster const *status);
	
	void isFailed();
	/*ͨ����������״̬����˳��
	��ʼ��_playerControlStatus=true��ʾ��Ҳ������ִ�
	_monsterIndex��ʾ�������0��ʾ�Ѿ�ѭ��һ��
	_playerIndex��ʾ��Ҵ���
	*/
	bool _playerControlStatus;
	//0,1,2,3
	int _monsterIndex;
	//0,1,2,3
	int _playerIndex;
private:
	CombatManage();
	static CombatManage* _instance;
	
};


#endif // !_COMBAT_MANAGE_H_

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
	//随机创建怪物，如果返回不为空，表示遇怪，否则不遇怪。
	/*一定要加上parent节点，因为sprite是自动释放内存的，
	如果没有引用就会很快释放,所以要在创建sprite以后马上加入节点
	这样就避免出现无法预料的问题*/
	Monster** createMonstersRandom(Node* parent);
	//初始化次序
	void initIndexNStatus();
	void finishOneStep();
	//玩家一个人物行动一次，如果全部行动，表示真，否则为假
	//状态改变在函数里进行
	bool addPlayerIndex();
	
	//怪物一个行动一次，如果全部行动，表示真，否则为假
	//状态改变在函数里进行
	bool addMonsterIndex();
	void deleteMonsters();
	//获取创建的怪物
	Monster** getMonsters();

	//对怪物进行攻击
	//攻物，伤害值
	void caculatePlayerDamage();
	int getDamageValue(class  Status const *status);
	//是否胜利
	bool isSuccess();

	void caculateMonsterDamage();
	int getDamageValue(class  Monster const *status);
	
	void isFailed();
	/*通过以下三个状态控制顺序
	初始是_playerControlStatus=true表示玩家操作的轮次
	_monsterIndex表示怪物次序0表示已经循环一次
	_playerIndex表示玩家次序
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

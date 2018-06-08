#pragma once
#ifndef _NPC_H_
#define _NPC_H_
#include <cocos2d.h>
#include "XUI\BaseUI.h"
USING_NS_CC;
class NPC :public Layer
{
public:
	static NPC *create(int npcid);
	virtual bool init(int npcid);//对NPC初始化

	//virtual void initPos();//主要初始化位置就行

	virtual void action();//动作（消失，弹出购买界面，进入战斗，获取物品）
	virtual std::vector<std::string> getConv();//播放对话

	Sprite* getNPCSprite();

	// a selector callback
	//void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	//CREATE_FUNC(BaseNPC);
	int _NPCID;
	string _name;
	string  _picurl;
	Sprite* _npcSprite;
	
	//int _type;//默认为0，NPC类型,普通，敌人，铁匠，药师，宝箱
	//int _typeForID;//对应类型ID，比如敌人对应哪个敌人ID，铁匠对应哪个ID

	NPCType _npcType;

	int _action;//NPC动作类型,停留，移动，移除
	std::vector<int> _taskIDList;//对应任务ID
	std::vector<string> _conv;//对话列表


	
	const static enum  NPCTYPE
	{
		//普通，商人,敌人，宝箱
		NORMAL, MERCHANT,ENEMY,BOX
	};
	const static enum  ACTIONTYPE
	{
		//不动，走动，移除
		stay, move,remove
	};

private:

};

#endif // !_BASE_NPC_H_

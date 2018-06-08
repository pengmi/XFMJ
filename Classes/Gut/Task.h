#pragma once
#pragma once
#ifndef _TASK_H_
#define _TASK_H_
#include <cocos2d.h>
#include "XUI\BaseUI.h"
#include "XData\DataModel.h"
#include "XData\DataManage.h"
USING_NS_CC;
class Task 
{
public:
	Task(int id);
	~Task();

	int _taskID;//����ID
	vector<int> _orderList;
	string _intro;//�������

	bool operator <(const Task*);
	//bool operator ==(const Task*);
	startCondition _startCondition;
	finishCondition _finishCondition;
	taskReward _reward;
	taskConv _taskConv;
	
	const static enum  ORDERTYPE
	{
		//�޶�����ɾ��npc������ս�����棬����
		NONE,REMOVE,ENEMY,MERCHANT
	};
private:

};

#endif // !_TASK_H_
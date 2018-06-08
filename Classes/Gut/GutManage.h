#pragma once
#ifndef _GUT_MANAGE_H_
#define _GUT_MANAGE_H_

#include "XData\DataModel.h"
#include "Gut\Task.h"
#include <iostream>
class Task;
class GutManage
{
public:
	~GutManage()
	{
		delete _instance;
		deleteTaskInstanceList();//剧情管理退出时释放堆空间
	}
	static GutManage* getInstance();

	void insertIntoConfigList(vector<int> *list,int id);

	//插入实例表，如果存在(实例或者id)，不插入
	//template<class T>
	//static void insertToVectorListSortByID(vector<T*> *list, T* id);
	template<class T>
	void insertToVectorListSortByID(vector<T> *list, T id);
	template<class T>
	void deleteFromVectorListSortByID(vector<T> *list, T id);
	template<class T>
	bool checkVectorListByID(vector<T> *list, T id);


	void createTaskInstance(int id);
	void createTaskInstance(vector<int> *idlist);
	//检查任务实体是否存在,存在返回真，否则返回假
	bool checkTaskInstance(int id);
	Task* getTaskInstance(int id);
	void deleteTaskInstance(int id);
	void deleteTaskInstanceList();

	bool checkTaskStartCondition(int taskid);
	bool checkTaskFinishCondition(int taskid);
	//任务配置列表
	PlayerTaskList _taskConfigList;

	void insertToTaskFinishedConfigList(int id);
	void insertToTaskDoingConfigList(int id);

	void finishiTask(int id);
	bool checkTaskFinishedConfigList(int id);
	bool checkTaskDoingConfigList(int id);
	//怪物配置列表
	PlayerEnemyList _enemyConfigList;
	void insertToEnemyCombatConfigList(int id);

	bool checkEnemyCombatConfigList(int id);
	//NPC配置列表
	PlayerNpcList _npcConfigList;

	void insertToNPCTalkedConfigList(int id);
	void insertToNPCDisableConfigList(int id);

	bool checkNpcTalkedConfigList(int id);
	bool checkNpcDisableConfigList(int id);
	//地图名字典
	std::map<std::string,std::string> MapNameDic;

	//任务实例列表
	//游戏开始后第一次遇到任务就加载任务实例
	//如果没有找到任务实例就创建，如果通过ID找到了就直接使用。
	//任务完成后将任务实例删除.
	//这样做是减小内存消耗同时平衡读取文件的次数
	vector<Task*> _taskInstanceList;
private:
	GutManage();
	static GutManage* _instance;
};



#endif // !_GUT_MANAGE_H_




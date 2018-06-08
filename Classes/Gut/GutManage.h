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
		deleteTaskInstanceList();//��������˳�ʱ�ͷŶѿռ�
	}
	static GutManage* getInstance();

	void insertIntoConfigList(vector<int> *list,int id);

	//����ʵ�����������(ʵ������id)��������
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
	//�������ʵ���Ƿ����,���ڷ����棬���򷵻ؼ�
	bool checkTaskInstance(int id);
	Task* getTaskInstance(int id);
	void deleteTaskInstance(int id);
	void deleteTaskInstanceList();

	bool checkTaskStartCondition(int taskid);
	bool checkTaskFinishCondition(int taskid);
	//���������б�
	PlayerTaskList _taskConfigList;

	void insertToTaskFinishedConfigList(int id);
	void insertToTaskDoingConfigList(int id);

	void finishiTask(int id);
	bool checkTaskFinishedConfigList(int id);
	bool checkTaskDoingConfigList(int id);
	//���������б�
	PlayerEnemyList _enemyConfigList;
	void insertToEnemyCombatConfigList(int id);

	bool checkEnemyCombatConfigList(int id);
	//NPC�����б�
	PlayerNpcList _npcConfigList;

	void insertToNPCTalkedConfigList(int id);
	void insertToNPCDisableConfigList(int id);

	bool checkNpcTalkedConfigList(int id);
	bool checkNpcDisableConfigList(int id);
	//��ͼ���ֵ�
	std::map<std::string,std::string> MapNameDic;

	//����ʵ���б�
	//��Ϸ��ʼ���һ����������ͼ�������ʵ��
	//���û���ҵ�����ʵ���ʹ��������ͨ��ID�ҵ��˾�ֱ��ʹ�á�
	//������ɺ�����ʵ��ɾ��.
	//�������Ǽ�С�ڴ�����ͬʱƽ���ȡ�ļ��Ĵ���
	vector<Task*> _taskInstanceList;
private:
	GutManage();
	static GutManage* _instance;
};



#endif // !_GUT_MANAGE_H_




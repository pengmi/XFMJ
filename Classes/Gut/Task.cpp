#include "Task.h"

Task::Task(int id)
{
	//_TaskID = id;

	//_intro = "";
	//_startCondition = { 0 };
	//_finishCondition = { 0 };
	//_reward = { 0 };
	//_taskConv = {};
	//��ʼ������������ݽ��ж�ȡ
	DataManage::getInstance()->readTaskData(this,id);

}

Task::~Task()
{

}

bool Task::operator<(const Task * t)
{
	if (this->_taskID<t->_taskID)
	{
		return true;
	}
	return false;
}

//bool Task::operator==(const Task * t)
//{
//	if (this==t||this->_TaskID==t->_TaskID)
//	{
//		return true;
//	}
//	return false;
//}

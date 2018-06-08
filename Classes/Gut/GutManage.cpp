#include "GutManage.h"

#include "XData\DataModel.h"

GutManage*  GutManage::_instance = NULL;
GutManage * GutManage::getInstance()
{
	if (_instance==NULL)
	{
		_instance = new GutManage();
	}
	return _instance;
}
void GutManage::insertIntoConfigList(vector<int>* list, int id)
{
	for (vector<int>::iterator i = list->begin(); 
		i !=list->end() ; ++i)
	{
		if (*i<id)
		{
			//在++i之前i之后插入元素id
			list->insert(++i, id);
			break;
		}
	}
}


void GutManage::createTaskInstance(int id)
{
	//如果检查到实例存在或者
	if (checkTaskInstance(id))
	{
		return;
	}
	auto task = new Task(id);
	insertToVectorListSortByID(&_taskInstanceList,task);
}

void GutManage::createTaskInstance(vector<int>* idlist)
{
	for (vector<int>::iterator i = idlist->begin(); i != idlist->end(); ++i)
	{
		//如果检查到实例存在或者已经完成直接退出本次操作
		//已经做完的没必要实例化了
		//已经实例化的不能再实例化了
		if (checkTaskInstance(*i)||checkTaskFinishedConfigList(*i))
		{
			continue;
		}
		auto task = new Task(*i);
		insertToVectorListSortByID(&_taskInstanceList, task);
	}

}

//template<class T>
//void GutManage::insertToVectorListSortByID(vector<T*>* list, T * id)
//{
//	//如果为空
//	if (!list->Size()))
//	{
//		list->push_back(id);
//		return;
//	}
//
//	for (vector<T*>::iterator i = list->begin();
//		i != list->end(); ++i)
//	{
//		if (*i<id)
//		{
//			//在++i之前i之后插入元素id
//			list->insert(++i, id);
//			break;
//		}
//		else if (*i == id)
//		{
//			break;//如果id已经存在，不用再插入
//		}
//	}
//}


template<class T>
void GutManage::insertToVectorListSortByID(vector<T>* list, T id)
{
	//如果为空
	if (!list->size())
	{
		list->push_back(id);
		return;
	}

	for (vector<T>::iterator i = list->begin();
		i != list->end(); ++i)
	{
		if (*i == id)//id已经存在，不插入
		{
			break;
		}

		//已经到最后一位
		if (i == (list->end() - 1))
		{
			//在i之前插入元素id
			list->insert(++i, id);
			break;
		}

		//不是最后一位,插入位置必须是两者之间，不然会重复插入
		if ((*i<id)&&(*(i+1)>id))
		{
			//在i之前插入元素id
			list->insert(i+1, id);
			break;
		}
	}
}

template<class T>
void GutManage::deleteFromVectorListSortByID(vector<T>* list, T id)
{
	//如果为空
	if (!list->size())
	{
		return;
	}

	for (vector<T>::iterator i = list->begin();
		i != list->end(); ++i)
	{
		if (*i == id)//id已经存在
		{
			//删除
			list->erase(i);
			break;
		}
	}
}

template<class T>
bool GutManage::checkVectorListByID(vector<T>* list, T id)
{

	for (vector<T>::iterator  i = list->begin()
		;  i != list->end(); ++i)
	{
		if (*i == id)
		{
			return true;
		}
	}
	return false;
}

bool GutManage::checkTaskInstance(int id)
{
	if (!id)
	{
		return true;
	}
	for (vector<Task*>::iterator i = _taskInstanceList.begin(); 
		i < _taskInstanceList.end();)
	{
		if (id==(*i)->_taskID)
		{
			return true;
		}
		++i;
	}
	return false;
}

Task * GutManage::getTaskInstance(int id)
{
	if (0==id)
	{
		return NULL;
	}
	for (vector<Task*>::iterator i = _taskInstanceList.begin(); 
		i != _taskInstanceList.end();++i )
	{
		if (id==(*i)->_taskID)
		{
			return *i;
		}
	}
	return NULL;
}

void GutManage::deleteTaskInstance(int id)
{
	for (vector<Task*>::iterator i = _taskInstanceList.begin();
		i != _taskInstanceList.end(); ++i)
	{
		if ((*i)->_taskID==id)
		{
			delete *i;
			break;
		}

	}
}

void GutManage::deleteTaskInstanceList()
{
	for (vector<Task*>::iterator i = _taskInstanceList.begin(); 
		i != _taskInstanceList.end(); ++i)
	{
		if (*i)
		{
			delete *i;
		}
		
	}
}

bool GutManage::checkTaskStartCondition(int taskid)
{
	//如果taskid==0,没有剧情
	if (taskid == 0)
	{
		return false;
	}

	auto taskinstance = getTaskInstance(taskid);
	//同时满足两个条件(开始条件不存在，或者开始条件已经满足)
	if ((!taskinstance->_startCondition._ongoingTaskID || 
		checkTaskDoingConfigList(taskinstance->_startCondition._ongoingTaskID))
		&& (!taskinstance->_startCondition._finishedTaskID || 
			checkTaskFinishedConfigList(taskinstance->_startCondition._finishedTaskID))
		)
	{
		return true;
	}

	return false;
}

bool GutManage::checkTaskFinishCondition(int taskid)
{
	//如果taskid==0,没有剧情
	if (taskid==0)
	{
		return false;
	}

	auto taskinstance = getTaskInstance(taskid);
	//同时满足三个条件(完成条件不存在，或者完成条件已经满足)
	if ((!taskinstance->_finishCondition._finishTaskID ||
		checkTaskFinishedConfigList(taskinstance->_finishCondition._finishTaskID))
		&&(!taskinstance->_finishCondition._talkTo || 
			checkNpcTalkedConfigList(taskinstance->_finishCondition._talkTo))
		&&(!taskinstance->_finishCondition._combatTo ||
			checkEnemyCombatConfigList(taskinstance->_finishCondition._combatTo))
		)
	{
		return true;
	}

	return false;
}

void GutManage::insertToTaskFinishedConfigList(int id)
{
	insertToVectorListSortByID(&(this->_taskConfigList.finished), id);
}

void GutManage::insertToTaskDoingConfigList(int id)
{
	insertToVectorListSortByID(&(this->_taskConfigList.ongoing), id);
}

void GutManage::finishiTask(int id)
{
	//更新进行列表和已完成列表
	//从进行列表里删除
	deleteFromVectorListSortByID(&(_taskConfigList.ongoing),id);
	//在完成列表里添加
	insertToTaskFinishedConfigList(id);
	//完成任务时最后删除实例，因为要读取任务内容
	deleteTaskInstance(id);
}

bool GutManage::checkTaskFinishedConfigList(int id)
{

	return checkVectorListByID(&(this->_taskConfigList.finished),id);
}

bool GutManage::checkTaskDoingConfigList(int id)
{
	//如果id是为0,表示完成，返回未在进行列表里
	if (!id)
	{
		return false;
	}
	return checkVectorListByID(&(this->_taskConfigList.ongoing), id);
}

void GutManage::insertToEnemyCombatConfigList(int id)
{
	insertToVectorListSortByID(&(this->_enemyConfigList.combat), id);
}

bool GutManage::checkEnemyCombatConfigList(int id)
{

	return checkVectorListByID(&(this->_enemyConfigList.combat), id);
}

void GutManage::insertToNPCTalkedConfigList(int id)
{
	insertToVectorListSortByID(&(this->_npcConfigList.talked), id);
}

void GutManage::insertToNPCDisableConfigList(int id)
{
	insertToVectorListSortByID(&(this->_npcConfigList.disable), id);
}

bool GutManage::checkNpcTalkedConfigList(int id)
{

	return checkVectorListByID(&(this->_npcConfigList.talked), id);
}

bool GutManage::checkNpcDisableConfigList(int id)
{

	return checkVectorListByID(&(this->_npcConfigList.disable), id);
}

GutManage::GutManage()
{
	MapNameDic.insert(
		std::pair<std::string,std::string>("1-1","后山草地"));
	MapNameDic.insert(
		std::pair<std::string, std::string>("1-2", "伐木场"));
	MapNameDic.insert(
		std::pair<std::string, std::string>("1-3", "三清墓地"));
	MapNameDic.insert(
		std::pair<std::string, std::string>("1-4", "后山山路"));
	MapNameDic.insert(
		std::pair<std::string, std::string>("1-5", "洗剑池"));
	MapNameDic.insert(
		std::pair<std::string, std::string>("2-1", "三清宫"));
	MapNameDic.insert(
		std::pair<std::string, std::string>("2-2", "三清殿"));
	MapNameDic.insert(
		std::pair<std::string, std::string>("2-3", "商店"));
	
}
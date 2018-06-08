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
			//��++i֮ǰi֮�����Ԫ��id
			list->insert(++i, id);
			break;
		}
	}
}


void GutManage::createTaskInstance(int id)
{
	//�����鵽ʵ�����ڻ���
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
		//�����鵽ʵ�����ڻ����Ѿ����ֱ���˳����β���
		//�Ѿ������û��Ҫʵ������
		//�Ѿ�ʵ�����Ĳ�����ʵ������
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
//	//���Ϊ��
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
//			//��++i֮ǰi֮�����Ԫ��id
//			list->insert(++i, id);
//			break;
//		}
//		else if (*i == id)
//		{
//			break;//���id�Ѿ����ڣ������ٲ���
//		}
//	}
//}


template<class T>
void GutManage::insertToVectorListSortByID(vector<T>* list, T id)
{
	//���Ϊ��
	if (!list->size())
	{
		list->push_back(id);
		return;
	}

	for (vector<T>::iterator i = list->begin();
		i != list->end(); ++i)
	{
		if (*i == id)//id�Ѿ����ڣ�������
		{
			break;
		}

		//�Ѿ������һλ
		if (i == (list->end() - 1))
		{
			//��i֮ǰ����Ԫ��id
			list->insert(++i, id);
			break;
		}

		//�������һλ,����λ�ñ���������֮�䣬��Ȼ���ظ�����
		if ((*i<id)&&(*(i+1)>id))
		{
			//��i֮ǰ����Ԫ��id
			list->insert(i+1, id);
			break;
		}
	}
}

template<class T>
void GutManage::deleteFromVectorListSortByID(vector<T>* list, T id)
{
	//���Ϊ��
	if (!list->size())
	{
		return;
	}

	for (vector<T>::iterator i = list->begin();
		i != list->end(); ++i)
	{
		if (*i == id)//id�Ѿ�����
		{
			//ɾ��
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
	//���taskid==0,û�о���
	if (taskid == 0)
	{
		return false;
	}

	auto taskinstance = getTaskInstance(taskid);
	//ͬʱ������������(��ʼ���������ڣ����߿�ʼ�����Ѿ�����)
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
	//���taskid==0,û�о���
	if (taskid==0)
	{
		return false;
	}

	auto taskinstance = getTaskInstance(taskid);
	//ͬʱ������������(������������ڣ�������������Ѿ�����)
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
	//���½����б��������б�
	//�ӽ����б���ɾ��
	deleteFromVectorListSortByID(&(_taskConfigList.ongoing),id);
	//������б������
	insertToTaskFinishedConfigList(id);
	//�������ʱ���ɾ��ʵ������ΪҪ��ȡ��������
	deleteTaskInstance(id);
}

bool GutManage::checkTaskFinishedConfigList(int id)
{

	return checkVectorListByID(&(this->_taskConfigList.finished),id);
}

bool GutManage::checkTaskDoingConfigList(int id)
{
	//���id��Ϊ0,��ʾ��ɣ�����δ�ڽ����б���
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
		std::pair<std::string,std::string>("1-1","��ɽ�ݵ�"));
	MapNameDic.insert(
		std::pair<std::string, std::string>("1-2", "��ľ��"));
	MapNameDic.insert(
		std::pair<std::string, std::string>("1-3", "����Ĺ��"));
	MapNameDic.insert(
		std::pair<std::string, std::string>("1-4", "��ɽɽ·"));
	MapNameDic.insert(
		std::pair<std::string, std::string>("1-5", "ϴ����"));
	MapNameDic.insert(
		std::pair<std::string, std::string>("2-1", "���幬"));
	MapNameDic.insert(
		std::pair<std::string, std::string>("2-2", "�����"));
	MapNameDic.insert(
		std::pair<std::string, std::string>("2-3", "�̵�"));
	
}
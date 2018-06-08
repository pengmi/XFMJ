#include "BagManage.h"
//#include "Player\PlayerManage.h"
#include "XData\DataManage.h"

BagManage* BagManage::_instance = NULL;

//void BagManage::addItemToBag()
//{
//}
//void BagManage::removeItemToBag()
//{
//}
//void BagManage::readItem(int itemID, Item * item)
//{
//	//ͨ��id���itemʵ������ȡitem�ļ������ݼ��ص�item�У�
//}
int &BagManage::getMoney()
{
	return _money;
}
int &BagManage::setMoney(int i)
{
	return _money = i;
}
int &BagManage::addMoney(int i)
{
	return _money += i;
}
int & BagManage::subMoney(int i)
{
	return _money -= i;
	// TODO: �ڴ˴����� return ���
}
BagManage::BagManage()
{
	
}

BagManage::~BagManage()
{
	deletePlayerEquipmentData();
	deleteBagData();
	
	delete _instance;
}

BagManage * BagManage::getInstance()
{
	if (NULL == _instance)
	{
		_instance = new BagManage();
	}
	return _instance;
}

int BagManage::getEmptyCellsNum()
{
	int num=0;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (NULL == BagOne[i][j].item)
				++num;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (NULL == BagTwo[i][j].item)
				++num;
		}
	}
	return num;
}

ItemInBag* BagManage::getEmptyCellPos()
{

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (NULL == BagOne[i][j].item)
				return &BagOne[i][j];
		}
	}
	
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (NULL == BagTwo[i][j].item)
				return &BagTwo[i][j];
		}
	}

	return NULL;
}

ItemInBag* BagManage::insertItemToBag(int itemid, int num)
{
	auto tempPosInBag = getEmptyCellPos();

	if (itemid&&tempPosInBag)
	{
		if (tempPosInBag)
		{
			tempPosInBag->item = DataManage::getInstance()->getItemData(itemid);
			tempPosInBag->num = num;
			return tempPosInBag;
		}
	}
	return NULL;
}

int BagManage::deleteItemFromBag(Item * item, int num)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (item==BagOne[i][j].item)
			{
				if (BagOne[i][j].num>num)
				{
					BagOne[i][j].num -= num;
				}
				else
				{
					BagOne[i][j].num = 0;
					delete BagOne[i][j].item;
					BagOne[i][j].item = NULL;
					
				}
				return BagOne[i][j].num;
				break;
			}
			else if(item == BagTwo[i][j].item)
			{
				if (BagTwo[i][j].num>num)
				{
					BagTwo[i][j].num -= num;
				}
				else
				{
					BagTwo[i][j].num = 0;
					delete BagTwo[i][j].item;
					BagTwo[i][j].item = NULL;
				}
				return BagTwo[i][j].num;
				break;
			}
			else
			{
				continue;
			}
		}
	}
	return -1;
}

void BagManage::deleteItemFromBag(ItemInBag * iteminbag,int num)
{

	if (iteminbag)
	{
		if (iteminbag->num>num)
		{
			iteminbag->num -= num;
		}
		else
		{
			iteminbag->num = 0;
			delete iteminbag->item;
			iteminbag->item = NULL;
		}
	}
}

void BagManage::deleteItemFromBag(int itemid, int num)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{

		}
	}
}

void BagManage::deletePlayerEquipmentData()
{
	for (int j = 0; j < 8; j++)
	{
		if (Equipment[j].item)
		{
			delete Equipment[j].item;//������֤���ڴ�ȷʵ�Ѿ��ͷ�
			Equipment[j].item = NULL;
			Equipment[j].num = 0;
		}
	}
}

void BagManage::loadPlayerEquipmentData(HeroLayer * h)
{
	/*��������������������һ�����ض������ڴ�й©*/
	deletePlayerEquipmentData();

	EquipmentsList* ePList = h->getEquipmentsList();

	if (ePList->_weaponID)//���ID��Ϊ0��װ�����ڣ���ȡװ������
	{
		Equipment[0].item= DataManage::getInstance()->
			getItemData(ePList->_weaponID);
		Equipment[0].num = 1;

	}
	if (ePList->_headID)
	{
		//ͨ��id��ȡ��Ʒ����
		Equipment[1].item = DataManage::getInstance()->
			getItemData(ePList->_headID);
		Equipment[1].num = 1;
	}
	if (ePList->_clothesID)
	{
		Equipment[2].item =DataManage::getInstance()->
			getItemData(ePList->_clothesID);
		Equipment[2].num = 1;
	}
	if (ePList->_cloackID)
	{
		Equipment[3].item =DataManage::getInstance()->
			getItemData(ePList->_cloackID);
		Equipment[3].num = 1;
	}
	if (ePList->_gloveID)
	{
		Equipment[4].item =DataManage::getInstance()->
			getItemData(ePList->_gloveID);
		Equipment[4].num = 1;
	}
	if (ePList->_tassesID)
	{
		Equipment[5].item = DataManage::getInstance()->
			getItemData(ePList->_tassesID);
		Equipment[5].num = 1;
	}
	if (ePList->_shoesID)
	{
		Equipment[6].item = DataManage::getInstance()->
			getItemData(ePList->_shoesID);
		Equipment[6].num = 1;
	}
	if (ePList->_ornamentsID)
	{
		Equipment[7].item = DataManage::getInstance()->
			getItemData(ePList->_ornamentsID);
		Equipment[7].num = 1;
	}
}

void BagManage::insertEquipment(ItemInBag * iib)
{
	auto item = iib->item;
	//�������������
	if (item->_type == "weapon")
	{
		Equipment[0].item = iib->item;
		Equipment[0].num = 1;//װ��ֻ����װ��һ��
		return;
	}

	//���������ͷ��
	if (item->_type == "head")
	{
		Equipment[1].item = iib->item;
		Equipment[1].num = 1;
		return;
	}
	//����������·�
	if (item->_type == "clothes")
	{
		Equipment[2].item = iib->item;
		Equipment[2].num = 1;
		return;
	}
	//�������������
	if (item->_type == "cloak")
	{
		Equipment[3].item = iib->item;
		Equipment[3].num = 1;
		return;
	}
	//�������������
	if (item->_type == "glove")
	{
		Equipment[4].item = iib->item;
		Equipment[4].num = 1;
		return;
	}
	//����������ȼ�
	if (item->_type == "tasses")
	{
		Equipment[5].item = iib->item;
		Equipment[5].num = 1;
		return;
	}
	//���������Ь��
	if (item->_type == "shoes")
	{
		Equipment[6].item = iib->item;
		Equipment[6].num = 1;
		return;
	}
	//�������������
	if (item->_type == "ornament")
	{
		Equipment[7].item = iib->item;
		Equipment[7].num = 1;
		return;
	}
}

bool BagManage::checkIsCanEquipment(Item * item)
{
	if (item->_type == "weapon"&&!Equipment[0].item)
	{

		return true;
	}

	//���������ͷ��
	if (item->_type == "head"&&!Equipment[1].item)
	{

		return true;
	}
	//����������·�
	if (item->_type == "clothes" && !Equipment[2].item)
	{

		return true;
	}
	//�������������
	if (item->_type == "cloak" && !Equipment[3].item)
	{

		return true;
	}
	//�������������
	if (item->_type == "glove" && !Equipment[4].item)
	{

		return true;
	}
	//����������ȼ�
	if (item->_type == "tasses" && !Equipment[5].item)
	{

		return true;
	}
	//���������Ь��
	if (item->_type == "shoes" && !Equipment[6].item)
	{

		return true;
	}
	//�������������
	if (item->_type == "ornament" && !Equipment[7].item)
	{

		return true;
	}
	return false;
}

void BagManage::deleteBagData()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (BagOne[i][j].item)
			{
				delete BagOne[i][j].item;
				BagOne[i][j].num = 0;
				BagOne[i][j].item = NULL;
			}
		}
	}
}

//void BagManage::loadBagData()
//{
//}

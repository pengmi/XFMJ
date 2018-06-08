#include "DataModel.h"
#include "XData\DataManage.h"

Item * Item::create(int id)
{
	
	if (!id)
	{
		return NULL;
	}
	auto pInstance = new Item();
	if (pInstance->init(id))
	{
		return pInstance;
	}
	
	delete pInstance;

	return NULL;
}

bool Item::init(int id)
{
	DataManage::getInstance()->readItemData(id, this);
	return true;
}

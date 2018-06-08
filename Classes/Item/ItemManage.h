#pragma once
#ifndef _ITEM_MANAGE_H_
#define _ITEM_MANAGE_H_

#include "XData\DataModel.h"

class ItemManage;
class ItemManage
{
public:
	
	virtual~ItemManage();

	static ItemManage* getInstance();

	void useItem(Item &i,Status &s);


private:
	ItemManage();
	static ItemManage* _instance;
};


#endif // !_ITEM_MANAGE_H_

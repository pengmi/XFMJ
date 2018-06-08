#pragma once
#ifndef _RES_BASE_H_
#define _RES_BASE_H_
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class ResBase
{

public:

	virtual void setData();
	

	int &getType();
	int &getIndex();

protected:
	int _type;
	int _index;

};


#endif _RES_BASE_H_
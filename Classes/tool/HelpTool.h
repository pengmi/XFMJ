#ifndef _HELPTOOL_H_
#define _HELPTOOL_H_

#include "cocos2d.h"
using namespace cocos2d;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include <vector>
using namespace std;
#pragma once
#include "cocos2d.h"


class HelpTool  {
public:
	HelpTool() {};
	~HelpTool() {};

	static CCAnimation* CreateAnimationByFile(const char*name, int hori, int vert);
	static Rect GetSpritePosition(Sprite* sprite);//取得精灵的方块
	static SpriteFrameCache* GetFrameCache(const char*, const char*);
	static Animation* GetHitAnimationByFileName(const char*name,const char*,int );
	static int RemoveFromArry(vector< Sprite*>,Sprite*);
	static Sprite* GetSpriteByFileName(const char*,int);//这个主要是用来截取png里只有两个元素的

	static std::string int2str(const int &int_temp);

	/*
	怪异的语法
	static template方法无法被分开定义在.h和.cpp文件里面
	只能一起定义在.h里面，不然无法识别这个函数符号。
	不知道为什么
	*/
	template<class T>
	static void insertToVectorListSort(vector<T> *list, T id);
	template<class T>
	static void deleteFromVectorListSort(vector<T> *list, T id);


};

#endif _HELPTOOL_H

template<class T>
inline void HelpTool::insertToVectorListSort(vector<T>* list, T id)
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
		if ((*i<id) && (*(i + 1)>id))
		{
			//在i之前插入元素id
			list->insert(i + 1, id);
			break;
		}
	}
}

template<class T>
inline void HelpTool::deleteFromVectorListSort(vector<T>* list, T id)
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

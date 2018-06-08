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
	static Rect GetSpritePosition(Sprite* sprite);//ȡ�þ���ķ���
	static SpriteFrameCache* GetFrameCache(const char*, const char*);
	static Animation* GetHitAnimationByFileName(const char*name,const char*,int );
	static int RemoveFromArry(vector< Sprite*>,Sprite*);
	static Sprite* GetSpriteByFileName(const char*,int);//�����Ҫ��������ȡpng��ֻ������Ԫ�ص�

	static std::string int2str(const int &int_temp);

	/*
	������﷨
	static template�����޷����ֿ�������.h��.cpp�ļ�����
	ֻ��һ������.h���棬��Ȼ�޷�ʶ������������š�
	��֪��Ϊʲô
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
		if ((*i<id) && (*(i + 1)>id))
		{
			//��i֮ǰ����Ԫ��id
			list->insert(i + 1, id);
			break;
		}
	}
}

template<class T>
inline void HelpTool::deleteFromVectorListSort(vector<T>* list, T id)
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

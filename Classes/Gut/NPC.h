#pragma once
#ifndef _NPC_H_
#define _NPC_H_
#include <cocos2d.h>
#include "XUI\BaseUI.h"
USING_NS_CC;
class NPC :public Layer
{
public:
	static NPC *create(int npcid);
	virtual bool init(int npcid);//��NPC��ʼ��

	//virtual void initPos();//��Ҫ��ʼ��λ�þ���

	virtual void action();//��������ʧ������������棬����ս������ȡ��Ʒ��
	virtual std::vector<std::string> getConv();//���ŶԻ�

	Sprite* getNPCSprite();

	// a selector callback
	//void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	//CREATE_FUNC(BaseNPC);
	int _NPCID;
	string _name;
	string  _picurl;
	Sprite* _npcSprite;
	
	//int _type;//Ĭ��Ϊ0��NPC����,��ͨ�����ˣ�������ҩʦ������
	//int _typeForID;//��Ӧ����ID��������˶�Ӧ�ĸ�����ID��������Ӧ�ĸ�ID

	NPCType _npcType;

	int _action;//NPC��������,ͣ�����ƶ����Ƴ�
	std::vector<int> _taskIDList;//��Ӧ����ID
	std::vector<string> _conv;//�Ի��б�


	
	const static enum  NPCTYPE
	{
		//��ͨ������,���ˣ�����
		NORMAL, MERCHANT,ENEMY,BOX
	};
	const static enum  ACTIONTYPE
	{
		//�������߶����Ƴ�
		stay, move,remove
	};

private:

};

#endif // !_BASE_NPC_H_

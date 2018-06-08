#pragma once
#ifndef _BASE_PLAYER_H_
#define _BASE_PLAYER_H_
#include<cocos2d.h>
#include<XData\Global.h>
#include"XData\DataModel.h"
USING_NS_CC;
class BasePlayerLayer :public cocos2d::Layer
{
public:
	//static cocos2d::Scene* createScene();

	~BasePlayerLayer();

	virtual bool init();
	/*virtual bool init(std::string);*/
	
	virtual bool initPlayer();
	virtual bool initStatus() =0;
	virtual bool initEquipment() =0;
	virtual bool initSkill() =0;

	void createSpriteCache();
	void setPlayerSpriteWithInit();
	//data
	void setHeroName(std::string str);
	std::string& getHeroName();
	void setHeroIntro(std::string str);
	std::string& getHeroIntro();
	void setPicUrl(std::string str);
	 /*״̬*/
	Status* getPlayerStatus();
	Sprite* getPlayerSprite();
	 /*װ��*/
	EquipmentsList* getEquipmentsList();
	void unloadEquipment(Item* const item);
	bool equipEquipment(Item* const item);
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void contactCallback(cocos2d::Ref* pSender);//������ײ�Ժ�Ļص�����

	// implement the "static create()" method manually
	//CREATE_FUNC(BasePlayerLayer);
	string _standUrl;//վ��plist
	string _attackUrl;//����plist
	string _skillUrl;//����plist
	string _hitUrl;//������plist
	SpriteFrameCache *_standFrameCache;
	SpriteFrameCache *_attackFrameCache;
	SpriteFrameCache *_skillFrameCache;
	SpriteFrameCache *_hitFrameCache;
protected:
	std::string _picUrl;//ͼ��·��
	std::string _heroName;//Ӣ������
	std::string _intro;//Ӣ�۽���
	cocos2d::Sprite *_playerSprite = NULL;//����ͼ��
	Status _status;//״̬
	EquipmentsList _Equipments;
};


#endif // !_BASE_PLAYER_H_

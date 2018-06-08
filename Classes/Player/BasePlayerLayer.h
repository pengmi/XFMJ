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
	 /*状态*/
	Status* getPlayerStatus();
	Sprite* getPlayerSprite();
	 /*装备*/
	EquipmentsList* getEquipmentsList();
	void unloadEquipment(Item* const item);
	bool equipEquipment(Item* const item);
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void contactCallback(cocos2d::Ref* pSender);//面向碰撞以后的回调函数

	// implement the "static create()" method manually
	//CREATE_FUNC(BasePlayerLayer);
	string _standUrl;//站立plist
	string _attackUrl;//攻击plist
	string _skillUrl;//技能plist
	string _hitUrl;//被攻击plist
	SpriteFrameCache *_standFrameCache;
	SpriteFrameCache *_attackFrameCache;
	SpriteFrameCache *_skillFrameCache;
	SpriteFrameCache *_hitFrameCache;
protected:
	std::string _picUrl;//图标路径
	std::string _heroName;//英雄名字
	std::string _intro;//英雄介绍
	cocos2d::Sprite *_playerSprite = NULL;//人物图标
	Status _status;//状态
	EquipmentsList _Equipments;
};


#endif // !_BASE_PLAYER_H_

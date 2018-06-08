#pragma once
#ifndef _HUANG_ZAI_LAYER_H_
#define _HUANG_ZAI_LAYER_H_
#include<cocos2d.h>
#include"Player\BasePlayerLayer.h"
/// 男主人公
///
///
class HeroLayer :public BasePlayerLayer
{
public:
	static HeroLayer* create();
	
	//virtual bool init();
	//virtual bool init(std::string);//每一个人物的状态，装备，技能都不同，所以初始函数不同
	virtual bool initStatus();
	virtual bool initEquipment();
	virtual bool initSkill();
	


	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	//CREATE_FUNC(HeroLayer);

//private:
//	cocos2d::Sprite *playerSprite = NULL;
//	
//
};


#endif // !_HUANG_ZAI_LAYER_H_

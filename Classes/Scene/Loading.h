#pragma once

#ifndef _LOADING_H_

#define _LOADING_H_



#include "cocos2d.h"

USING_NS_CC;

class Loading :public Layer {
public:
	
	virtual bool init();
	void initBackground();

	void initTouch();
	CREATE_FUNC(Loading);

	void setFullPercent();

	void update(float dt);


	float _percent;

	ProgressTimer* _loadProgress;//½ø¶ÈÌõ

};


#endif // !_LOADING_H_
#ifndef __FIRST_SCENE_H__
#define __FIRST_SCENE_H__

#include "cocos2d.h"
#include "Scene\BaseScene.h"
USING_NS_CC;
class MainGameScene : public BaseScene
{
public:
	//创建这个函数的目的是传入参数，默认的create是没有参数的
	static MainGameScene* create(std::string nextMAPNAME, std::string curMAPNAME);
	//static cocos2d::Scene* createScene();
	static cocos2d::Scene* createScene(std::string nextMAPNAME, std::string curMAPNAME);

	//初始化

	virtual bool initMap(std::string mapName);
	virtual bool initPlayer();
	
	//控制


	//update
	virtual void changeScene(std::string mapName);


};

#endif // __FIRST_SCENE_H__
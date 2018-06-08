#ifndef __FIRST_SCENE_H__
#define __FIRST_SCENE_H__

#include "cocos2d.h"
#include "Scene\BaseScene.h"
USING_NS_CC;
class MainGameScene : public BaseScene
{
public:
	//�������������Ŀ���Ǵ��������Ĭ�ϵ�create��û�в�����
	static MainGameScene* create(std::string nextMAPNAME, std::string curMAPNAME);
	//static cocos2d::Scene* createScene();
	static cocos2d::Scene* createScene(std::string nextMAPNAME, std::string curMAPNAME);

	//��ʼ��

	virtual bool initMap(std::string mapName);
	virtual bool initPlayer();
	
	//����


	//update
	virtual void changeScene(std::string mapName);


};

#endif // __FIRST_SCENE_H__
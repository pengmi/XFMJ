#include "Scene\MainGameScene.h"
//#include "HelloWorldScene.h"
USING_NS_CC;


MainGameScene * MainGameScene::create(std::string nextMAPNAME, std::string curMAPNAME)
{
	MainGameScene *pRet = new MainGameScene;
		if (pRet&&pRet->init(nextMAPNAME,curMAPNAME))
		{
			/*��һҳ�洫���ֵ*/
			//pRet->_mapId=MAPID;
			pRet->autorelease();
			return pRet;
		}
		else {
			CC_SAFE_DELETE(pRet);
			return NULL;
		}
}

cocos2d::Scene * MainGameScene::createScene(std::string nextMAPNAME, std::string curMAPNAME)
{
	//_mapId = mapid;
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainGameScene::create(nextMAPNAME,curMAPNAME);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MainGameScene::initMap(std::string mapName)
{
	_tileMap = cocos2d::experimental::TMXTiledMap::create("maps/"+mapName+".tmx");
	if (!_tileMap)
	{
		return false;
	}
	_tileMap->setPosition(0,0);
	
	this->addChild(_tileMap,MAPLAYER,"MAP");

	return true;
};
bool MainGameScene::initPlayer()
{	
	getPlayerManager();
	setPlayerSpwanPoint();//������ͼ����(0,0)��������Ϸ
						  //�����������ң������ݶ�ȡ��ʱ��ͼ�����λ����
	return true;
};

void MainGameScene::changeScene(std::string nextMapName)
{
	/*
	��ת��ͼ��֮ǰ�����������ʱ�浵
	*/


	////////////////////////////
	if (nextMapName == "")
		return;
	_preMapName = getCurMapName();//������ת��ͼ�������ڵĵ�ͼ�ݴ�Ϊǰ��ͼ
	auto scene = MainGameScene::createScene(nextMapName,_preMapName);
	
	//    ���ã�����һ����ҳ�Ĺ��ɶ���
	//    ����1�����ɶ���������ʱ��
	//    ����2���л���Ŀ�곡���Ķ���
	//    ����3���Ƿ�����ҳ
	auto reScene = CCTransitionPageTurn::create(1.5f, scene, false);

	Director::getInstance()->replaceScene(reScene);
}

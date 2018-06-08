#include "Scene\MainGameScene.h"
//#include "HelloWorldScene.h"
USING_NS_CC;


MainGameScene * MainGameScene::create(std::string nextMAPNAME, std::string curMAPNAME)
{
	MainGameScene *pRet = new MainGameScene;
		if (pRet&&pRet->init(nextMAPNAME,curMAPNAME))
		{
			/*上一页面传入的值*/
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
	setPlayerSpwanPoint();//如果玩家图标在(0,0)则是新游戏
						  //如果不是新玩家，在数据读取的时候就加载了位置了
	return true;
};

void MainGameScene::changeScene(std::string nextMapName)
{
	/*
	跳转地图的之前，必须更新临时存档
	*/


	////////////////////////////
	if (nextMapName == "")
		return;
	_preMapName = getCurMapName();//即将跳转地图，将现在的地图暂存为前地图
	auto scene = MainGameScene::createScene(nextMapName,_preMapName);
	
	//    作用：创建一个翻页的过渡动画
	//    参数1：过渡动作持续的时间
	//    参数2：切换的目标场景的对象
	//    参数3：是否逆向翻页
	auto reScene = CCTransitionPageTurn::create(1.5f, scene, false);

	Director::getInstance()->replaceScene(reScene);
}

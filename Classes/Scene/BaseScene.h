#ifndef __Base_SCENE_H__
#define __Base_SCENE_H__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Player\HeroLayer.h"
#include "XUI\BaseUI.h"
#include "Gut\NPC.h"
#include "Player\PlayerManage.h"
#include "XData\DataManage.h"
#include <iostream>
//using namespace cocos2d;
//using namespace CocosDenshion;
USING_NS_CC;

class BaseScene : public cocos2d::Layer
{
public:
	//基类场景，只用来继承,createScene在其他场景
	//static cocos2d::Scene* createScene();


	//init
	//virtual bool init();
	virtual bool init(std::string curMAPNAME,std::string preMAPNAME);
	void popMsg();
	virtual bool initMap(std::string mapName) ;//地图
	virtual bool getPlayerManager();//玩家管理类
	virtual bool initPlayer() ;//玩家
	void setPlayerSpwanPoint();
	virtual void initBackground();
	virtual void initTouch();
	void initXData();
	void initXUI();
	//initData()
	//是不是还需要一个初始化地图数据,得到这个数据以后再去初始化地图中的敌人，NPC，物品
	virtual bool initEnemy() ;//敌人

	virtual bool initNPC() ;//友好单位,商人，任务等
	bool checkNPCInConfigDisableList(int id);

	//control
	
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *user_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *user_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *user_evenr);
	//virtual void keyBackClicked(Touch *touch, Event *user_evenr) {};//Android 返回键
	//virtual void keyMenuClicked(Touch *touch, Event *user_evenr) {};//Android 菜单键


	//数据操作
	cocos2d::ValueMap getObjectGroupValueMap(std::string objectName);//找到本地图Object层里面的对象数据
	//cocos2d::Vector<cocos2d::ValueMap> getObjectGroupsValueMap();
	cocos2d::ValueVector getAllObjectGroupValueMaps();//

	//更新函数
	//virtual void update(float dt) {};//update函数
	void updateViewPointCenter();
	//void updateBaseUIPosition(Point &point);
	void updateBaseUIPosition(Point &point);
	const std::string getCurMapName();
	virtual void changeScene(std::string mapName) {};//加载地图


	//碰撞检测
	////实际上.h文件里的函数体是默认内联函数，无需加上inline,这里我是为了以后看的方便.
	//碰撞检测会很频繁的使用，所以使用内联函数。这个函数也应该尽量小.

	//找到在瓦片素材中的位置
	cocos2d::Point tileCoordForPosition(cocos2d::Point position);

	//inline
	//地图层的碰撞检测
	bool mapCollisonDetection(cocos2d::Point position);
	
	//检测与地图中地图控制器的碰撞
	std::map<std::string, std::string> mapControllerDetection();
	
	//是否与npc碰撞,如果碰撞的话检查npc对应的任务，如果没有任务实例就创建
	bool npcCollisonDetection(Point position);

	bool gutDisplay(NPC* npc);

	//不需要继承的函数，直接可以使用
	void setPlayerPosition(cocos2d::CCPoint point)
	{
		_playerManager->_sprite->setPosition(point);
	}

	//void popMsgInfo(std::string);
	
	//回调函数

	void menuCloseCallback(cocos2d::Ref* pSender);
	bool mainSceneChangeCheck();

protected:
	

	/*
	为什么UI类不像人物管理器一样，只能一个实例用到尾，而是可以每个场景都重新加载？
	因为UI类的数据是依赖于人物管理器类的数据，我不需要一个实例从头到尾，只需要玩
	家打开UI的时候，我手动的把人物数据传递给UI就行了，并不需要像人物管理器一样。
	当然，其实UI类确实可以像人物管理器类一样。
	*/
	BaseUI * _baseUi;//菜单层


	std::string _mapName = "";//现在地图ID
	std::string _preMapName = "";//暂存上一个地图ID，主要用来确认出生点
	cocos2d::experimental::TMXTiledMap *_tileMap = NULL;//地图文件

	//用人物管理器去管理，而不是直接管理人物实例，因为玩家有三个实例，
	//而且这个玩家管理器从游戏一开始，只创建一次实例，其他全部使用他，
	//因为玩家不一定随时存档，不可能每一次切换场景，我都去加载数据
	//加载的数据也不是最新的数据，所以我们在需要手动加载的时候加载数据
	//这个玩家管理器里面的内容做为暂时的，非持久化的数据存放地点，就只能有一个实例一使用。
	PlayerManage * _playerManager=NULL;

	std::vector<NPC*> _npcVector;
};

#endif // __BASE_SCENE_H__
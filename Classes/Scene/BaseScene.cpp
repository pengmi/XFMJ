#include "Scene\BaseScene.h"
#include "XUI\ConvUI.h"
#include "Combat\MonsterManage.h"
#include "Combat\CombatManage.h"
#include "XUI\CombatUI.h"
USING_NS_CC;


//Scene* BaseScene::createScene()
//{
//	// 'scene' is an autorelease object
//	auto scene = Scene::create();
//
//	// 'layer' is an autorelease object
//	auto layer = BaseScene::create();
//
//	// add layer as a child to scene
//	scene->addChild(layer);
//
//	// return the scene
//	return scene;
//}

// on "init" you need to initialize your instance

bool BaseScene::init(std::string curMAPNAME, std::string preMAPNAME)
{
	if (!Layer::init())
	{
		return false;
	}
	//读取mapid
	_mapName = curMAPNAME;
	_preMapName = preMAPNAME;
	
	initXData();
	initTouch();
	/*Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();*/
	initMap(curMAPNAME);
	initBackground();
	initXUI();
	
	//initPlayerManager();
	initPlayer();
	initNPC();
	initEnemy();
	popMsg();
//	_baseUi->setPlayerData(_playerManager->_huangZaiLayer,NULL,NULL);
	return true;
}

void BaseScene::popMsg()
{
	auto position = PlayerManage::getInstance()->
		getPlayerSprite()->getPosition();
	auto winSize = Director::getInstance()->getWinSize();


	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	CCPoint actualPosition = ccp(x, y+100);

	auto msgLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(
				GutManage::getInstance()->
				MapNameDic.at(_mapName).c_str()),
		"隶书", 28);
	msgLabel->setPosition(actualPosition);
	this->addChild(msgLabel, UILAYER3th);
	
	//msgLabel->setColor(ccc3(255, 60, 0));

	msgLabel->runAction(
		Sequence::create(
			DelayTime::create(1.0f)
			,
			FadeOut::create(2)
			//DelayTime::create(1.0f)
			,
			NULL
		)
	);
}

bool BaseScene::initMap(std::string mapName)
{
	return false;
}

bool BaseScene::getPlayerManager()
{
	if (_playerManager = PlayerManage::getInstance())
	{
		//如果存在父类就只能移除了以后再添加到新的父层中
		if (auto p=_playerManager->getParent())
		{
			//_playerManager->retain();//保持引用，不要自动释放内存
			p->removeChild(_playerManager);
		//	_playerManager = PlayerManage::create();
		}
		_playerManager->setPosition(0,0);
		_playerManager->setMapName(_mapName);
		this->addChild(_playerManager,PLAYERLAYER);
		return true;
	}
	return false;

	//if (_playerManager = PlayerManage::getInstance())
	//{
	//	_playerManager->retain();//保持引用，不要自动释放内存

	//	_playerManager->setPosition(0, 0);
	//	this->addChild(_playerManager,PLAYERLAYER);
	//	_playerManager->setMapName(_mapName);
	//	return true;
	//}
	//return false;
}

bool BaseScene::initPlayer()
{
	getPlayerManager();
	setPlayerSpwanPoint();
	return false;
}

void BaseScene::setPlayerSpwanPoint()
{
	/*获取玩家人物加载位置*/
	ValueMap spawnPointMap;
	if (_preMapName == "")//代表读取存档或者重新开始,总之,与切换地图分开
	{
		//出身点作废，因为只有新建游戏的时候有用，太浪费了，直接在读取存档的时候设置位置
		//spawnPointMap = getObjectGroupValueMap("SpawnPoint");
		updateViewPointCenter();
		return;
	}
	else
	{
		auto objectPointMap = getAllObjectGroupValueMaps();
		for (auto i = objectPointMap.begin(); i != objectPointMap.end(); i++)
		{
			ValueMap tmp = i->asValueMap();
			if (tmp["NextMapName"].asString() == _preMapName)
			{
				spawnPointMap = tmp;
				break;
			}
		}
	}
	float x = spawnPointMap["x"].asFloat() + spawnPointMap["width"].asFloat() / 2;
	float y = spawnPointMap["y"].asFloat() + spawnPointMap["height"].asFloat() / 2;

	_playerManager->_sprite->setPosition(Vec2(x, y));

	updateViewPointCenter();
}

void BaseScene::initXUI()
{
	_baseUi = BaseUI::create();
	//_baseUi->setPlayerData(*(_huangZaiLayer->getPlayerStatus()));
	this->addChild(_baseUi,MENULAYER);

	_baseUi->setPosition(Point(0, 0));
}

bool BaseScene::initEnemy()
{
	if (auto monstermanage = MonsterManage::getInstance())
	{
		//如果怪物在地图中处于活跃状态
		//if (monstermanage->setMonsterActiveOrNot(_mapName))
		//{
		//	//加载本地图的怪物列表
		//	monstermanage->setMonstersIDList(_mapName);
		//} 
		monstermanage->setMonstersManageData(_mapName);
		return true;
	}
	return false;
}

bool BaseScene::initNPC()
{
	auto nextMapPointVector = getAllObjectGroupValueMaps();
	for (auto i = nextMapPointVector.begin();
		i != nextMapPointVector.end(); i++)
	{
		auto tmp = i->asValueMap();

		if (tmp.size())//数据存在
		{
			if (tmp["type"].asString() == "NPC")//如果是NPC
			{
				int id = tmp["NPCID"].asInt();
				
				//如果存在于disable列表中，表示不加载此NPC
				if (checkNPCInConfigDisableList(id))
				{
					continue;
				}
				//取得NPCID,在这个位置设置NPC
				auto tbn= NPC::create(id);
				tbn->setPosition(tmp["x"].asFloat() + tmp["width"].asFloat() / 2,
					tmp["y"].asFloat()+ tmp["height"].asFloat() / 2);
				this->addChild(tbn,PLAYERLAYER);
				_npcVector.push_back(tbn);

			}
		};
	}
	return true;
}

bool BaseScene::checkNPCInConfigDisableList(int id)
{
	vector<int> *tmpList = &(GutManage::getInstance()->_npcConfigList.disable);
	for (vector<int>::iterator i = tmpList->begin(); i != tmpList->end(); ++i)
	{
		if (*i==id)
		{
			return true;
		}
	}
	return false;
}

void BaseScene::initBackground()
{
}

void BaseScene::initTouch()
{
	//触控
	setKeypadEnabled(true);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(BaseScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(BaseScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(BaseScene::onTouchEnded, this);
	//listener->onTouchCancelled = CC_CALLBACK_2(FirstScene::keyBackClicked,this);
	listener->setSwallowTouches(true);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->setTouchEnabled(true);
}

void BaseScene::initXData()
{
	DataManage::getInstance();

}


void BaseScene::updateViewPointCenter()
{
	if (_playerManager == NULL &&_tileMap== NULL)
		return;
	auto position = _playerManager->_sprite->getPosition();
	//地图移动的方式达到视角跟随的目的，（不好用，以后碰撞检测不好做）
	//_tileMap->setPosition(position.x/2,position.y/2);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	CCPoint actualPosition = ccp(x, y);

	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);

	//设置scene位置,保持在中心
	this->setPosition(viewPoint);
	updateBaseUIPosition(actualPosition);


}

void BaseScene::updateBaseUIPosition(Point &point)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	//_baseUi->setPosition(point.x+winSize.width/2,point.y+winSize.height/2);
	_baseUi->setPosition(point.x- winSize.width / 2, point.y- winSize.height / 2);
}

bool BaseScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * user_event)
{
	//auto loc = touch->getLocationInView();
	//if (collisonDetection(_huangZaiLayer->getPosition()))	
	//	return false;
	return true;
}

void BaseScene::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * user_event)
{
	auto loc = touch->getLocationInView();

}

void BaseScene::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * user_evenr)
{
	CCPoint touchLocation = this->convertTouchToNodeSpace(touch);

	CCPoint playerPos = _playerManager->_sprite->getPosition();
	//CCPoint tmp = playerPos;
	CCPoint mapPos = _tileMap->getPosition();

	CCPoint diff = ccpSub(touchLocation, playerPos);
	if (abs(diff.x) > abs(diff.y))
	{
		if (diff.x > 0)
		{
			playerPos.x += _tileMap->getTileSize().width;
		}
		else
		{
			playerPos.x -= _tileMap->getTileSize().width;
		}
	}
	else
	{
		if (diff.y > 0)
		{
			playerPos.y += _tileMap->getTileSize().height;
		}
		else
		{
			playerPos.y -= _tileMap->getTileSize().height;
		}
	}

	if (playerPos.x <= (_tileMap->getMapSize().width * _tileMap->getTileSize().width) &&
		playerPos.y <= (_tileMap->getMapSize().height * _tileMap->getTileSize().height) &&
		playerPos.y >= 0 && playerPos.x >= 0)
	{
		//做碰撞检测，如果不能通过就直接返回，如果可以通过就直接行动
		//避免作用临时对象，对象朝生夕灭浪费资源
		//bool tmpT = mapCollisonDetection(playerPos);
		if (mapCollisonDetection(playerPos) || npcCollisonDetection(playerPos))
		{
			CCLOG("collison detection true");
			return;
		}
	}
	//updateViewPointCenter();
	//_playerManager->setSpritePosition(playerPos);

	_playerManager->moveSprite(playerPos);
	updateViewPointCenter();
	//如果是跳转场景中，不加载战斗，防止出现Bug
	if (!mainSceneChangeCheck())
	{
		//如果不是跳转场景
		//判断是否进入战斗
		//如果地图上的怪物活跃（存在）
		if (MonsterManage::getInstance()->
			getMonsterActiveStatus())
		{
			//随机判断是否遇怪
			if (CombatManage::getInstance()->isGetMonsters())
			{
				//如果遇怪
				
				//弹出战斗场景
			//	CombatManage::getInstance()->getMonsters();
				auto combatuilayer= CombatUI::create();
			/*	combatuilayer->setPosition(
					PlayerManage::getInstance()->
					getPlayerSprite()->getPosition());*/
				_baseUi->addChild(combatuilayer,UILAYER);
				/*CCTransitionPageTurn::create();*/
				
			}
		}
	}
}

ValueMap BaseScene::getObjectGroupValueMap(std::string objectName)
{
	
	auto objects = _tileMap->getObjectGroup("Objects");
	CCAssert(objects != NULL, "Objects' object group not found");
	return ValueMap(objects->getObject(objectName));
}

cocos2d::ValueVector BaseScene::getAllObjectGroupValueMaps()
{
	auto objects = _tileMap->getObjectGroup("Objects");
	//auto objects = _tileMap->getObjectGroups();
	CCAssert(objects != NULL, "Objects' object group not found");
	//ValueMap spawnPointMap = objects->getObject("NextMap");
	return objects->getObjects();
}

const std::string BaseScene::getCurMapName()
{
	return _mapName;
}

cocos2d::Point BaseScene::tileCoordForPosition(Point position)
{
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;

	return cocos2d::Point(x,y);
}


inline bool BaseScene::mapCollisonDetection(cocos2d::Point position)
{

	cocos2d::Point tileCoord = tileCoordForPosition(position);
	auto collisonLayer = _tileMap->getLayer("Collision");
	int teiledMapGlobalID = collisonLayer->getTileGIDAt(tileCoord);

	//CCLOG("teiledMapGlobalID: %d", teiledMapGlobalID);

	if (teiledMapGlobalID)
	{
		//auto properties = _tileMap->getPropertiesForGID(teiledMapGlobalID);
		/*if (properties.isNull())
		{
			return false;
		}*/
		//auto  tmp= properties.asValueMap();
		if (_tileMap->getPropertiesForGID(teiledMapGlobalID).
			asValueMap()["colliable"].asString()=="true")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

std::map<std::string, std::string> BaseScene::mapControllerDetection()
{
	auto nextMapPointVector = getAllObjectGroupValueMaps();
	/*auto tp = _playerManager->_sprite->getBoundingBox();
	tp.setRect(point.x, point.y, tp.getMaxX(), tp.getMaxY());*/

	for (auto i = nextMapPointVector.begin(); 
		i != nextMapPointVector.end(); i++)
	{
		auto tmp = i->asValueMap();
		
		cocos2d::Rect r;
		r.setRect(tmp["x"].asDouble(),
			tmp["y"].asDouble(), tmp["width"].asDouble(), tmp["height"].asDouble());
		//CCLOG("collison sprite position %f,%f", _playerManager->_sprite->getPosition().x, _playerManager->_sprite->getPosition().y);
		if (_playerManager->_sprite->getBoundingBox().intersectsRect(r))//碰撞
		//if (tp.intersectsRect(r))//碰撞
		{
			
			std::map<std::string, std::string> value;
			//value.insert(str1,str2);
			value.insert({ "type",tmp["type"].asString() });
			if (tmp["type"].asString()=="MapController")//如果是页面跳转控制obj
			{
				//取得页面跳转控制器中的下一个地图
				value.insert({ std::string("attribute"), tmp["NextMapName"].asString() });
			}
			
			return	value;
		}	;
	}
	return std::map<std::string, std::string>();
}

bool BaseScene::npcCollisonDetection(Point position)
{
#pragma region NPC碰撞检测
	
	if (_npcVector.begin()==_npcVector.end())
	{
		return false;
	}
	auto gutinstnce = GutManage::getInstance();

	auto playerR = _playerManager->_sprite->getBoundingBox();
	
	//auto playerV = _huangZaiLayer->getPlayerSprite()->getContentSize();
	playerR.setRect(position.x, position.y,
		_playerManager->getPlayerSprite()->getContentSize().width,
		_playerManager->getPlayerSprite()->getContentSize().height);
	for (std::vector<NPC*>::iterator i = _npcVector.begin();
		i != _npcVector.end(); i++)
	{
		/*CCLOG(" _player %f, %f", _huangZaiLayer->getBoundingBox().origin.x, _huangZaiLayer->getBoundingBox().origin.y);
		CCLOG(" next %f, %f", playerR.origin.x, playerR.origin.y);
		CCLOG(" _NPC  %f, %f", (*i)->getBoundingBox().origin.x, (*i)->getBoundingBox().origin.y);*/
		//auto tmpRect = _huangZaiLayer->getBoundingBox();
		auto npcR = (*i)->getBoundingBox();
		npcR.setRect(npcR.origin.x, npcR.origin.y,
			(*i)->_npcSprite->getContentSize().width,
			(*i)->_npcSprite->getContentSize().height);
		if (playerR.intersectsRect(npcR))
		{
			/*
				与NPC的图片碰撞后，首先播放剧情：
				3.如果已经做完，就不管了。
				1.播放剧情就是查看是否有任务在做
				4.如果还在做就查看是否满足完成条件。
				5.如果满足完成条件就完成，获取奖励。
				2.是否有任务满足开始条件
				6.如果满足开始条件就开始，然后回到1。
				一定要先把正在做的任务检查完了再去检查还没开始的任务。因为也许存在依赖关系。
			*/

			//如果没有任务了，直接播放普通对话.
			if (!gutDisplay(*i))
			{
				_baseUi->loadNpcNormalConvUI(*i, &_npcVector);
			};

			//_npcVector.erase(_npcVector.begin());
			return true;
		};
		//i++;
	}
#pragma endregion
	return false;
}

bool BaseScene::gutDisplay(NPC* npc)
{
	bool tempBool=false;
	auto gutinstance = GutManage::getInstance();

	gutinstance->insertToNPCTalkedConfigList(npc->_NPCID);

	for (int i = 0; i < npc->_taskIDList.size(); ++i)
	{
		//如果列表值为0，空或者处于完成列表，直接跳过本次循环
		if (!npc->_taskIDList[i] ||gutinstance->checkTaskFinishedConfigList(npc->_taskIDList[i]))
		{
			continue;
		}

		auto taskinstance = gutinstance->getTaskInstance(npc->_taskIDList[i]);

		//如果一个任务id处于进行列表中
		if (gutinstance->checkTaskDoingConfigList(npc->_taskIDList[i]))
		{
			//检查完成条件，如果满足完成条件，1.播放完成对话2.获得奖励3.更新任务列表
			if (gutinstance->checkTaskFinishCondition(npc->_taskIDList[i]))
			{
				//播放完成对话和动作
				_baseUi->loadTaskEndUI(taskinstance, npc, &_npcVector);
				//获得奖励

				////更新任务列表
				//gutinstance->finishiTask(npc->_taskIDList[i]);
			}
			else//如果不能满足完成条件，播放进行中对话
			{
				//播放进行中对话
				_baseUi->loadTaskDoingUI(taskinstance, npc, &_npcVector);
			}
			tempBool = true;
			continue;//一次检测只进行一项剧情,所以直接返回 
		}
		//如果一个任务id没有在进行和完成列表中，且不为0和空（已在前面判断过）
		//检查是否满足开始任务条件
		if (gutinstance->checkTaskStartCondition(npc->_taskIDList[i]))
		{
			//播放开始任务的对话

			_baseUi->loadTaskBeginUI(taskinstance,npc,&(this->_npcVector));

			//更新任务进行列表
			gutinstance->insertToTaskDoingConfigList(npc->_taskIDList[i]);

			//检查完成条件，如果满足完成条件，1.播放完成对话2.获得奖励3.更新任务列表
			if (gutinstance->checkTaskFinishCondition(npc->_taskIDList[i]))
			{
				//播放完成对话和动作
				_baseUi->loadTaskEndUI(taskinstance,npc,&_npcVector);
				//获得奖励

				////更新任务列表
				//gutinstance->finishiTask(npc->_taskIDList[i]);
			}
			return true;
		}
	}

	return tempBool;
}

//void BaseScene::popMsgInfo(std::string str)
//{
//	auto msgLabel = LabelTTF::create(
//		wstrtoutf8::CreateUTF8(str.c_str()), "隶书", 24);
//	msgLabel->setPosition(Director::getInstance()->getWinSize() / 2);
//	this->addChild(msgLabel, UILAYER3th);
//
//	msgLabel->runAction(
//		Sequence::create(
//			FadeOut::create(3)
//			//DelayTime::create(1.0f)
//			,
//			NULL
//		)
//	);
//}

void BaseScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
//判断是否需要切换场景
bool BaseScene::mainSceneChangeCheck()
{
	std::map<std::string, std::string> collisonObjectVector = mapControllerDetection();
	if (collisonObjectVector.cbegin() != collisonObjectVector.cend())//如果碰撞到object
	{
		if (collisonObjectVector["type"] == "MapController")
		{

			changeScene(collisonObjectVector["attribute"]);
			return true;
		}
	}
	return false;
}

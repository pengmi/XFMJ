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
	//��ȡmapid
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
		"����", 28);
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
		//������ڸ����ֻ���Ƴ����Ժ�����ӵ��µĸ�����
		if (auto p=_playerManager->getParent())
		{
			//_playerManager->retain();//�������ã���Ҫ�Զ��ͷ��ڴ�
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
	//	_playerManager->retain();//�������ã���Ҫ�Զ��ͷ��ڴ�

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
	/*��ȡ����������λ��*/
	ValueMap spawnPointMap;
	if (_preMapName == "")//�����ȡ�浵�������¿�ʼ,��֮,���л���ͼ�ֿ�
	{
		//��������ϣ���Ϊֻ���½���Ϸ��ʱ�����ã�̫�˷��ˣ�ֱ���ڶ�ȡ�浵��ʱ������λ��
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
		//��������ڵ�ͼ�д��ڻ�Ծ״̬
		//if (monstermanage->setMonsterActiveOrNot(_mapName))
		//{
		//	//���ر���ͼ�Ĺ����б�
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

		if (tmp.size())//���ݴ���
		{
			if (tmp["type"].asString() == "NPC")//�����NPC
			{
				int id = tmp["NPCID"].asInt();
				
				//���������disable�б��У���ʾ�����ش�NPC
				if (checkNPCInConfigDisableList(id))
				{
					continue;
				}
				//ȡ��NPCID,�����λ������NPC
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
	//����
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
	//��ͼ�ƶ��ķ�ʽ�ﵽ�ӽǸ����Ŀ�ģ��������ã��Ժ���ײ��ⲻ������
	//_tileMap->setPosition(position.x/2,position.y/2);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	CCPoint actualPosition = ccp(x, y);

	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);

	//����sceneλ��,����������
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
		//����ײ��⣬�������ͨ����ֱ�ӷ��أ��������ͨ����ֱ���ж�
		//����������ʱ���󣬶�����Ϧ���˷���Դ
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
	//�������ת�����У�������ս������ֹ����Bug
	if (!mainSceneChangeCheck())
	{
		//���������ת����
		//�ж��Ƿ����ս��
		//�����ͼ�ϵĹ����Ծ�����ڣ�
		if (MonsterManage::getInstance()->
			getMonsterActiveStatus())
		{
			//����ж��Ƿ�����
			if (CombatManage::getInstance()->isGetMonsters())
			{
				//�������
				
				//����ս������
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
		if (_playerManager->_sprite->getBoundingBox().intersectsRect(r))//��ײ
		//if (tp.intersectsRect(r))//��ײ
		{
			
			std::map<std::string, std::string> value;
			//value.insert(str1,str2);
			value.insert({ "type",tmp["type"].asString() });
			if (tmp["type"].asString()=="MapController")//�����ҳ����ת����obj
			{
				//ȡ��ҳ����ת�������е���һ����ͼ
				value.insert({ std::string("attribute"), tmp["NextMapName"].asString() });
			}
			
			return	value;
		}	;
	}
	return std::map<std::string, std::string>();
}

bool BaseScene::npcCollisonDetection(Point position)
{
#pragma region NPC��ײ���
	
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
				��NPC��ͼƬ��ײ�����Ȳ��ž��飺
				3.����Ѿ����꣬�Ͳ����ˡ�
				1.���ž�����ǲ鿴�Ƿ�����������
				4.����������Ͳ鿴�Ƿ��������������
				5.������������������ɣ���ȡ������
				2.�Ƿ����������㿪ʼ����
				6.������㿪ʼ�����Ϳ�ʼ��Ȼ��ص�1��
				һ��Ҫ�Ȱ���������������������ȥ��黹û��ʼ��������ΪҲ�����������ϵ��
			*/

			//���û�������ˣ�ֱ�Ӳ�����ͨ�Ի�.
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
		//����б�ֵΪ0���ջ��ߴ�������б�ֱ����������ѭ��
		if (!npc->_taskIDList[i] ||gutinstance->checkTaskFinishedConfigList(npc->_taskIDList[i]))
		{
			continue;
		}

		auto taskinstance = gutinstance->getTaskInstance(npc->_taskIDList[i]);

		//���һ������id���ڽ����б���
		if (gutinstance->checkTaskDoingConfigList(npc->_taskIDList[i]))
		{
			//����������������������������1.������ɶԻ�2.��ý���3.���������б�
			if (gutinstance->checkTaskFinishCondition(npc->_taskIDList[i]))
			{
				//������ɶԻ��Ͷ���
				_baseUi->loadTaskEndUI(taskinstance, npc, &_npcVector);
				//��ý���

				////���������б�
				//gutinstance->finishiTask(npc->_taskIDList[i]);
			}
			else//�����������������������Ž����жԻ�
			{
				//���Ž����жԻ�
				_baseUi->loadTaskDoingUI(taskinstance, npc, &_npcVector);
			}
			tempBool = true;
			continue;//һ�μ��ֻ����һ�����,����ֱ�ӷ��� 
		}
		//���һ������idû���ڽ��к�����б��У��Ҳ�Ϊ0�Ϳգ�����ǰ���жϹ���
		//����Ƿ����㿪ʼ��������
		if (gutinstance->checkTaskStartCondition(npc->_taskIDList[i]))
		{
			//���ſ�ʼ����ĶԻ�

			_baseUi->loadTaskBeginUI(taskinstance,npc,&(this->_npcVector));

			//������������б�
			gutinstance->insertToTaskDoingConfigList(npc->_taskIDList[i]);

			//����������������������������1.������ɶԻ�2.��ý���3.���������б�
			if (gutinstance->checkTaskFinishCondition(npc->_taskIDList[i]))
			{
				//������ɶԻ��Ͷ���
				_baseUi->loadTaskEndUI(taskinstance,npc,&_npcVector);
				//��ý���

				////���������б�
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
//		wstrtoutf8::CreateUTF8(str.c_str()), "����", 24);
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
//�ж��Ƿ���Ҫ�л�����
bool BaseScene::mainSceneChangeCheck()
{
	std::map<std::string, std::string> collisonObjectVector = mapControllerDetection();
	if (collisonObjectVector.cbegin() != collisonObjectVector.cend())//�����ײ��object
	{
		if (collisonObjectVector["type"] == "MapController")
		{

			changeScene(collisonObjectVector["attribute"]);
			return true;
		}
	}
	return false;
}

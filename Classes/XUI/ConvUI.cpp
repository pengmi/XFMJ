#include"ConvUI.h"
#include "Item\GoodsManage.h"
#include "XUI\MerchantUI.h"

NPCNormalConvUI * NPCNormalConvUI::create(class NPC *npc,
	std::vector<NPC*> *npcVec)
{
	NPCNormalConvUI *pRet = new NPCNormalConvUI;
	if (pRet&&pRet->init(npc, npcVec))
	{
		pRet->autorelease();
		return pRet;
	}
	else {
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

bool NPCNormalConvUI::init(class NPC *npc,
	std::vector<NPC*> *npcVec)
{
	//_parentLayer = parent;
	initBackground();
	_conStr = npc->getConv();
	_operateNPC = npc;
	_npcVector = npcVec;

	_index = 0;
	_convLabel = LabelTTF::create(
		wstrtoutf8::CreateUTF8(_conStr[_index].c_str()), "宋体", 20);

	_convLabel->setColor(ccc3(0, 100, 255));
	//_convLabel->setDimensions(Size(Director::getInstance()->getWinSize().width*0.7f, 30.0f));
	_convLabel->setPosition(Director::getInstance()->getWinSize() / 2);
	//label->setPosition(0,0);
	this->addChild(_convLabel);
	initTouch();
#pragma region initTouch匿名函数加载方式
/*
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch *t, Event *e) {

		if ((_conStr.size()) - 1>_index)
		{
			_index++;
			_convLabel->initWithString(wstrtoutf8::CreateUTF8((_conStr)[_index].c_str()), "宋体", 20);
		}
		else
		{
			//this->closeMenuUI(NULL);//不能先释放本层，由此可见cocos在执行这一语句时确实释放了层内资源
			if (_operateNPC->_npcType._type == NPC::NPCTYPE::NORMAL)
			{
				if (_operateNPC->_action == NPC::ACTIONTYPE::remove)
				{
					for (std::vector<NPC*>::iterator it = _npcVector->begin();
						it != _npcVector->end(); it++)
					{
						if (_operateNPC == *it)
						{
							_npcVector->erase(it);
							break;
						}
						else
							;
					}
					_operateNPC->removeFromParentAndCleanup(true);
				}
			}

			this->closeMenuUI(NULL);

			return true;
		}
		return true;
	};
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listener, this);
*/
#pragma endregion

	return true;
}

void NPCNormalConvUI::initBackground()
{
	_backsprite = Sprite::create("/UI/convBack.png");
	_backsprite->setPosition(Director::getInstance()->getWinSize() / 2);
	
	
	this->addChild(_backsprite);
	//this->setCascadeOpacityEnabled(true);
	//_backsprite->setOpacity(180);
}

void NPCNormalConvUI::popMsgLabel(std::string str)
{
	if (str=="")
	{
		return;
	}

	auto msgLabel = LabelTTF::create(
		wstrtoutf8::CreateUTF8(str.c_str()), "隶书", 24);
	msgLabel->setPosition(Director::getInstance()->getWinSize() / 2);
	this->getParent()->addChild(msgLabel, UILAYER4th, "msgLabel");

	msgLabel->runAction(
		Sequence::create(
			Spawn::create(FadeOut::create(1.5f),
				MoveBy::create(1.5f, Vec2(0, 50)), NULL)
			//DelayTime::create(3.0f)
			,
			CallFuncN::create([](cocos2d::Node * pSender) {
		//删除这个msgLabel
		(pSender)->removeFromParentAndCleanup(true);
	})
			,
			NULL
		)
	);
}

void NPCNormalConvUI::initTouch()
{
	//auto dispatcher = Director::getInstance()->getEventDispatcher();
	//auto listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = CC_CALLBACK_2(BaseUI::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(BaseUI::onTouchMoved, this);
	//listener->onTouchEnded = CC_CALLBACK_2(BaseUI::onTouchEnded, this);
	////listener->onTouchCancelled = CC_CALLBACK_2(FirstScene::keyBackClicked,this);
	//listener->setSwallowTouches(true);
	//dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//this->setTouchEnabled(true);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(NPCNormalConvUI::onTouchBegan, this);
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listener, this);
	this->setTouchEnabled(true);
}

bool NPCNormalConvUI::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * user_event)
{

	if ((_conStr.size()) - 1>_index)
	{
		_index++;
		_convLabel->initWithString(wstrtoutf8::CreateUTF8((_conStr)[_index].c_str()), "宋体", 20);
	}
	else
	{
		//this->closeMenuUI(NULL);//不能先释放本层，由此可见cocos在执行这一语句时确实释放了层内资源
		
		//如果是移除类型动作，无论什么NPC，直接在普通对话后移除
		
		
		switch (_operateNPC->_npcType._type)
		{
		case NPC::NPCTYPE::NORMAL:
		{
			//如果是普通，什么也不做
			break;
		};
		case NPC::NPCTYPE::MERCHANT:
		{
			//如果是商人，载入售卖页面
			//如果已经存在，就不加载
			if (this->getParent()->getChildByName("merchantui"))
			{
				break;
			}

			GoodsManage::getInstance()->getGoodsInstanceList(_operateNPC);

			auto merchantUI = MerchantUI::create();

			this->getParent()->addChild(merchantUI,MENULAYER,"merchantui");

			break;
		};
		case NPC::NPCTYPE::ENEMY:
		{
			//如果是敌人，载入战斗场景
			break;
		};
		case NPC::NPCTYPE::BOX:
		{
			//如果是宝箱，得到宝箱内物品
			auto baginstance = BagManage::getInstance();
			//如果箱子内物品数量过多，背包装不下，应该有提醒
			//并且暂时取不了箱子。
			//如果可以装下，就正常获得物品。
			if (baginstance->getEmptyCellsNum() >= _operateNPC->_npcType._typeData.size())
			{
				for (int i = 0; i < _operateNPC->_npcType._typeData.size(); ++i)
				{
					auto tmp= baginstance->insertItemToBag(_operateNPC->_npcType._typeData[i]);
					popMsgLabel("获得物品:"+tmp->item->_itemName);
				}
			}
			else
			{
				popMsgLabel("背包空间不足");
				//关闭界面被返回，以避免删除箱子.
				this->closeMenuUI(NULL);

				return true;
			}
			 
			break;
		};
		default:
			break;
		}
		
		if (_operateNPC->_action == NPC::ACTIONTYPE::remove)
		{
			GutManage::getInstance()->
				insertToNPCDisableConfigList(_operateNPC->_NPCID);

			for (std::vector<NPC*>::iterator it = _npcVector->begin();
				it != _npcVector->end(); it++)
			{
				if (_operateNPC == *it)
				{
					_npcVector->erase(it);
					break;
				}
				else
					;
			}
			_operateNPC->removeFromParentAndCleanup(true);
		}

		this->closeMenuUI(NULL);

		return true;
	}
	return true;
}

//void ConvUI::initTouch()
//{
//	
//}

TaskBeginConvUI * TaskBeginConvUI::create(Task * task, NPC * npc, std::vector<NPC*> *npcVec)
{
	TaskBeginConvUI *pRet = new TaskBeginConvUI;
	if (pRet&&pRet->init(task,npc, npcVec))
	{
		pRet->autorelease();
		return pRet;
	}
	else {
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

bool TaskBeginConvUI::init(Task * task, NPC * npc, std::vector<NPC*> *npcVec)
{
	
	initBackground();

	_conStr = task->_taskConv._beginTaskConv;
	_operateNPC = npc;
	_curTask = task;
	_npcVector = npcVec;
	_index = 0;
	_convLabel = LabelTTF::create(
		wstrtoutf8::CreateUTF8(_conStr[_index].c_str()), "宋体", 22);

	_convLabel->setColor(ccc3(0, 100, 255));
	//_convLabel->setDimensions(Size(Director::getInstance()->getWinSize().width*0.7f, 30.0f));
	_convLabel->setPosition(Director::getInstance()->getWinSize() / 2);
	//label->setPosition(0,0);
	this->addChild(_convLabel);

	initTouch();
	return true;
}
//任务开始对话
bool TaskBeginConvUI::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * user_event)
{
	if ((_conStr.size()) - 1>_index)
	{
		_index++;
		_convLabel->initWithString(wstrtoutf8::CreateUTF8((_conStr)[_index].c_str()), "宋体", 20);
	}
	else
	{
		this->closeMenuUI(NULL);
		return true;
	}
	return true;
}

TaskDoingConvUI * TaskDoingConvUI::create(Task * task, NPC * npc, std::vector<NPC*>* npcVec)
{
	TaskDoingConvUI *pRet = new TaskDoingConvUI;
	if (pRet&&pRet->init(task, npc, npcVec))
	{
		pRet->autorelease();
		return pRet;
	}
	else {
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

bool TaskDoingConvUI::init(Task * task, NPC * npc, std::vector<NPC*>* npcVec)
{
	

	initBackground();

	_conStr = task->_taskConv._doingTaskConv;
	_operateNPC = npc;
	_curTask = task;
	_npcVector = npcVec;
	_index = 0;
	_convLabel = LabelTTF::create(
		wstrtoutf8::CreateUTF8(_conStr[_index].c_str()), "宋体", 22);

	_convLabel->setColor(ccc3(0, 100, 255));
	//_convLabel->setDimensions(Size(Director::getInstance()->getWinSize().width*0.7f, 30.0f));
	_convLabel->setPosition(Director::getInstance()->getWinSize() / 2);
	//label->setPosition(0,0);
	this->addChild(_convLabel);

	initTouch();
	return true;
}

bool TaskDoingConvUI::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * user_event)
{
	if ((_conStr.size()) - 1>_index)
	{
		_index++;
		_convLabel->initWithString(wstrtoutf8::CreateUTF8((_conStr)[_index].c_str()), "宋体", 20);
	}
	else
	{
		this->closeMenuUI(NULL);
		return true;
	}
	return false;
}

TaskEndConvUI * TaskEndConvUI::create(Task * task, NPC * npc, std::vector<NPC*>* npcVec)
{
	TaskEndConvUI *pRet = new TaskEndConvUI;
	if (pRet&&pRet->init(task, npc, npcVec))
	{
		pRet->autorelease();
		return pRet;
	}
	else {
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

bool TaskEndConvUI::init(Task * task, NPC * npc, std::vector<NPC*>* npcVec)
{

	initBackground();

	_conStr = task->_taskConv._finishTaskConv;
	_operateNPC = npc;
	_curTask = task;
	_npcVector = npcVec;
	_index = 0;
	_convLabel = LabelTTF::create(
		wstrtoutf8::CreateUTF8(_conStr[_index].c_str()), "宋体", 22);

	_convLabel->setColor(ccc3(0, 100, 255));
	//_convLabel->setDimensions(Size(Director::getInstance()->getWinSize().width*0.7f, 30.0f));
	_convLabel->setPosition(Director::getInstance()->getWinSize() / 2);
	//label->setPosition(0,0);
	this->addChild(_convLabel);

	initTouch();
	return true;
}

/*完成任务的ontouchBegan与之前的的不同，因为要对npc进行操作*/
bool TaskEndConvUI::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * user_event)
{

	if ((_conStr.size()) - 1>_index)
	{
		_index++;
		_convLabel->initWithString(wstrtoutf8::CreateUTF8((_conStr)[_index].c_str()), "宋体", 20);
	}
	else
	{
		/*
		判断是否有动作并选择播放
		*/
		/*如果是敌人，载入敌人，进入战斗界面*/
		/*如果是商人*/
		if (_curTask->_orderList.size())
		{
			for (int i = 0; i < _curTask->_orderList.size(); i++)
			{
				if (Task::ORDERTYPE::NONE==(_curTask->_orderList[i]))
				{
					//如果此操作为NONE，表示不需要任何操作。
					continue;
				}
				else if (Task::ORDERTYPE::REMOVE == (_curTask->_orderList[i]))
				{
					//当然，首先要更新GutManage里面的npc disable配置列表
					GutManage::getInstance()->
						insertToNPCDisableConfigList(_operateNPC->_NPCID);
					//如果此操作为REMOVE，表示任务结束后永久移除NPC。
					for (std::vector<NPC*>::iterator it = _npcVector->begin();
						it != _npcVector->end(); it++)
					{
						if (_operateNPC == *it)
						{
							_npcVector->erase(it);
							break;
						}
						else
							;
					}
					_operateNPC->removeFromParentAndCleanup(true);
				}
			}
		}
		/*____________________________*/
		//更新任务列表,释放任务实例，防止占用内存
		GutManage::getInstance()->
			finishiTask(_curTask->_taskID);
		

		this->closeMenuUI(NULL);
		return true;
	}
	return true;
}

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
		wstrtoutf8::CreateUTF8(_conStr[_index].c_str()), "����", 20);

	_convLabel->setColor(ccc3(0, 100, 255));
	//_convLabel->setDimensions(Size(Director::getInstance()->getWinSize().width*0.7f, 30.0f));
	_convLabel->setPosition(Director::getInstance()->getWinSize() / 2);
	//label->setPosition(0,0);
	this->addChild(_convLabel);
	initTouch();
#pragma region initTouch�����������ط�ʽ
/*
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch *t, Event *e) {

		if ((_conStr.size()) - 1>_index)
		{
			_index++;
			_convLabel->initWithString(wstrtoutf8::CreateUTF8((_conStr)[_index].c_str()), "����", 20);
		}
		else
		{
			//this->closeMenuUI(NULL);//�������ͷű��㣬�ɴ˿ɼ�cocos��ִ����һ���ʱȷʵ�ͷ��˲�����Դ
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
		wstrtoutf8::CreateUTF8(str.c_str()), "����", 24);
	msgLabel->setPosition(Director::getInstance()->getWinSize() / 2);
	this->getParent()->addChild(msgLabel, UILAYER4th, "msgLabel");

	msgLabel->runAction(
		Sequence::create(
			Spawn::create(FadeOut::create(1.5f),
				MoveBy::create(1.5f, Vec2(0, 50)), NULL)
			//DelayTime::create(3.0f)
			,
			CallFuncN::create([](cocos2d::Node * pSender) {
		//ɾ�����msgLabel
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
		_convLabel->initWithString(wstrtoutf8::CreateUTF8((_conStr)[_index].c_str()), "����", 20);
	}
	else
	{
		//this->closeMenuUI(NULL);//�������ͷű��㣬�ɴ˿ɼ�cocos��ִ����һ���ʱȷʵ�ͷ��˲�����Դ
		
		//������Ƴ����Ͷ���������ʲôNPC��ֱ������ͨ�Ի����Ƴ�
		
		
		switch (_operateNPC->_npcType._type)
		{
		case NPC::NPCTYPE::NORMAL:
		{
			//�������ͨ��ʲôҲ����
			break;
		};
		case NPC::NPCTYPE::MERCHANT:
		{
			//��������ˣ���������ҳ��
			//����Ѿ����ڣ��Ͳ�����
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
			//����ǵ��ˣ�����ս������
			break;
		};
		case NPC::NPCTYPE::BOX:
		{
			//����Ǳ��䣬�õ���������Ʒ
			auto baginstance = BagManage::getInstance();
			//�����������Ʒ�������࣬����װ���£�Ӧ��������
			//������ʱȡ�������ӡ�
			//�������װ�£������������Ʒ��
			if (baginstance->getEmptyCellsNum() >= _operateNPC->_npcType._typeData.size())
			{
				for (int i = 0; i < _operateNPC->_npcType._typeData.size(); ++i)
				{
					auto tmp= baginstance->insertItemToBag(_operateNPC->_npcType._typeData[i]);
					popMsgLabel("�����Ʒ:"+tmp->item->_itemName);
				}
			}
			else
			{
				popMsgLabel("�����ռ䲻��");
				//�رս��汻���أ��Ա���ɾ������.
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
		wstrtoutf8::CreateUTF8(_conStr[_index].c_str()), "����", 22);

	_convLabel->setColor(ccc3(0, 100, 255));
	//_convLabel->setDimensions(Size(Director::getInstance()->getWinSize().width*0.7f, 30.0f));
	_convLabel->setPosition(Director::getInstance()->getWinSize() / 2);
	//label->setPosition(0,0);
	this->addChild(_convLabel);

	initTouch();
	return true;
}
//����ʼ�Ի�
bool TaskBeginConvUI::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * user_event)
{
	if ((_conStr.size()) - 1>_index)
	{
		_index++;
		_convLabel->initWithString(wstrtoutf8::CreateUTF8((_conStr)[_index].c_str()), "����", 20);
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
		wstrtoutf8::CreateUTF8(_conStr[_index].c_str()), "����", 22);

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
		_convLabel->initWithString(wstrtoutf8::CreateUTF8((_conStr)[_index].c_str()), "����", 20);
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
		wstrtoutf8::CreateUTF8(_conStr[_index].c_str()), "����", 22);

	_convLabel->setColor(ccc3(0, 100, 255));
	//_convLabel->setDimensions(Size(Director::getInstance()->getWinSize().width*0.7f, 30.0f));
	_convLabel->setPosition(Director::getInstance()->getWinSize() / 2);
	//label->setPosition(0,0);
	this->addChild(_convLabel);

	initTouch();
	return true;
}

/*��������ontouchBegan��֮ǰ�ĵĲ�ͬ����ΪҪ��npc���в���*/
bool TaskEndConvUI::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * user_event)
{

	if ((_conStr.size()) - 1>_index)
	{
		_index++;
		_convLabel->initWithString(wstrtoutf8::CreateUTF8((_conStr)[_index].c_str()), "����", 20);
	}
	else
	{
		/*
		�ж��Ƿ��ж�����ѡ�񲥷�
		*/
		/*����ǵ��ˣ�������ˣ�����ս������*/
		/*���������*/
		if (_curTask->_orderList.size())
		{
			for (int i = 0; i < _curTask->_orderList.size(); i++)
			{
				if (Task::ORDERTYPE::NONE==(_curTask->_orderList[i]))
				{
					//����˲���ΪNONE����ʾ����Ҫ�κβ�����
					continue;
				}
				else if (Task::ORDERTYPE::REMOVE == (_curTask->_orderList[i]))
				{
					//��Ȼ������Ҫ����GutManage�����npc disable�����б�
					GutManage::getInstance()->
						insertToNPCDisableConfigList(_operateNPC->_NPCID);
					//����˲���ΪREMOVE����ʾ��������������Ƴ�NPC��
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
		//���������б�,�ͷ�����ʵ������ֹռ���ڴ�
		GutManage::getInstance()->
			finishiTask(_curTask->_taskID);
		

		this->closeMenuUI(NULL);
		return true;
	}
	return true;
}

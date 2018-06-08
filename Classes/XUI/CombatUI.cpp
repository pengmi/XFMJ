#include "CombatUI.h"
#include "Combat\CombatManage.h"
#include "tool\HelpTool.h"
#include "tool\WStrToUTF8.h"
#include "XData\Global.h"
#include "Player\PlayerManage.h"

bool CombatUI::init()
{
	setBackGround();
	initTouch();
	initPlayerSprite();
	initMenu();
	initMonsterSprite();
	initAction();
	setCombatTurn();//˳��ͼ��
	//_operateStatus = false;
	NotificationCenter::getInstance()->addObserver(
		this, callfuncO_selector(
			CombatUI::receiveCaclulateNotification), 
		"caclulatedamage", NULL);
	NotificationCenter::getInstance()->addObserver(
		this,callfuncO_selector(
			CombatUI::receiveMonsterAttackFinishNotification),
		"monsterattack",NULL);
	return true;
}

void CombatUI::setBackGround()
{
	_backsprite = Sprite::create("/CombatScene/grassland.png");
	_backsprite->setPosition(_backsprite->getContentSize()/2);
	//_backsprite->setOpacity(1.0f);
	this->addChild(_backsprite);
}

void CombatUI::initPlayerSprite()
{
	auto winsize = Director::getInstance()->getWinSize();
	auto combatmanage = CombatManage::getInstance();

	float xpianyi = winsize.width / 4;
	float ypianyi = winsize.height / 5;

	auto playermanage= PlayerManage::getInstance();
	auto temp = playermanage->_huangZaiLayer;
	//��ӽ���ҽ�ɫ�б�
	combatmanage->_combatCharacterList[0]=temp;
	//
	temp->createSpriteCache();
	temp->setPlayerSpriteWithInit();
	_playerOne = temp->getPlayerSprite();
	this->addChild(_playerOne);
	_playerOne->setPosition(2*xpianyi,1*ypianyi);

	if (temp=playermanage->_lianLayer)
	{
		combatmanage->_combatCharacterList[1]=temp;
		temp->createSpriteCache();
		temp->setPlayerSpriteWithInit();
		_playerTwo = temp->getPlayerSprite();
		this->addChild(_playerTwo);
		_playerTwo->setPosition(1 * xpianyi, 1 * ypianyi);
	}
	else
	{
		combatmanage->_combatCharacterList[1] = NULL;
	}

	if (temp=playermanage->_cmLayer)
	{
		combatmanage->_combatCharacterList[2] = temp;
		temp->createSpriteCache();
		temp->setPlayerSpriteWithInit();
		_playerThree = temp->getPlayerSprite();
		this->addChild(_playerThree);
		_playerThree->setPosition(3 * xpianyi, 1 * ypianyi);
	}
	else
	{
		combatmanage->_combatCharacterList[2] = NULL;
	}
}

void CombatUI::initAction()
{
	setPlayerControlDisactive(this);
	this->setScale(0.1f);
	this->setOpacity(0);
	this->setCascadeOpacityEnabled(true);
	this->runAction(
		Sequence::create(
			Spawn::create(
				ScaleTo::create(1.0f, 1.0f),
				FadeTo::create(1.0f,255),
				NULL
			),
			CallFuncN::create(this, 
				callfuncN_selector(CombatUI::setPlayerControlActive)),
			NULL
		)
	);
}

void CombatUI::setPlayerControlDisactive(cocos2d::Node * pSender)
{
	CombatManage::getInstance()->_playerControlStatus = false;
}

void CombatUI::setPlayerControlActive(cocos2d::Node * pSender)
{
	CombatManage::getInstance()->_playerControlStatus = true;
}

void CombatUI::initMonsterSprite()
{
	auto winsize = Director::getInstance()->getWinSize();
	auto combatmanage= CombatManage::getInstance();

	float xpianyi = winsize.width/4;
	float ypianyi = winsize.height / 5;

	//�����������
	combatmanage->createMonstersRandom(this);

	for (int i=0;i<3;i++)
	{
		//�������Ŀ�꣨��������ѱ����ɣ�
		if (combatmanage->_combatTargetsList[i])
		{
			//���ù���λ�ò����뵽�ڵ���
			if (i==0)
			{
				combatmanage->_combatTargetsList[i]->
					setPosition(xpianyi*(2), ypianyi * 4);
			}
			else if (1==i)
			{
				combatmanage->_combatTargetsList[i]->
					setPosition(xpianyi*(1), ypianyi * 4);
			}
			else if (2 == i)
			{
				combatmanage->_combatTargetsList[i]->
					setPosition(xpianyi*(3), ypianyi * 4);
			}
			
		};
	};
}

void CombatUI::initMenu()
{

	auto contentsize = _backsprite->getContentSize();
	auto originpoint = _backsprite->getPosition();

	float xpianyi = 20.0f;
	float ypianyi = 40.0f;
	_operateRunawayItem = MenuItemImage::create("UI/combat_runaway_off.png", "UI/combat_runaway_on.png",
		CC_CALLBACK_1(CombatUI::runawayClick, this
		));
	_operateRunawayItem->setPosition(
		contentsize.width/2 - _operateRunawayItem->
		getContentSize().width/2-xpianyi,
		contentsize.height/2 - ypianyi);

	_operateBagItem = MenuItemImage::create("UI/combat_bag_off.png", "UI/combat_bag_on.png",
		CC_CALLBACK_1(CombatUI::bagClick, this
		));
	_operateBagItem->setPosition(
		contentsize.width / 2 - _operateBagItem->
		getContentSize().width / 2 - xpianyi,
		contentsize.height / 2 - ypianyi*3);

	_operateSkillItem = MenuItemImage::create("UI/combat_skill_off.png", "UI/combat_skill_on.png",
		CC_CALLBACK_1(CombatUI::skillClick, this
		));
	_operateSkillItem->setPosition(
		contentsize.width / 2 - _operateBagItem->
		getContentSize().width / 2 - xpianyi,
		contentsize.height / 2 - ypianyi * 4);
	
	_operateAttackItem = MenuItemImage::create("UI/combat_attack_off.png", "UI/combat_attack_on.png",
		CC_CALLBACK_1(CombatUI::attackClick, this
		));
	_operateAttackItem->setPosition(
		contentsize.width / 2 - _operateBagItem->
		getContentSize().width / 2 - xpianyi,
		contentsize.height / 2 - ypianyi * 5);

	_operateMenu = Menu::create(_operateRunawayItem,_operateBagItem, _operateSkillItem,_operateAttackItem,NULL);
	/*_operateMenu->setPosition(originpoint.x+contentsize.width-xpianyi,
		originpoint.y+contentsize.height-ypianyi);*/
	this->addChild(_operateMenu);
}

void CombatUI::clearMenu()
{
	if (_operateMenu)
	{
		if (_operateMenu->getChildrenCount())
		{
			_operateMenu->removeAllChildrenWithCleanup(true);
			_operateAttackItem=NULL;//����
			_operateRunawayItem=NULL;//����
			_operateSkillItem=NULL;//����
			_operateBagItem=NULL;//����
		}
	}
}

void CombatUI::initTouch()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CombatUI::onTouchBegan, this);
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listener, this);
	this->setTouchEnabled(true);
}

void CombatUI::setCombatTurn()
{
	//���û�з�����ʼ�����Ƚ��г�ʼ��
	if (!_combatTurn)
	{
		CombatManage::getInstance()->initIndexNStatus();
		_combatTurn = Sprite::create("UI/combat_turn.png");
		this->addChild(_combatTurn);
		_combatTurn->runAction(
			RepeatForever::create(
				RotateBy::create(1.0f, Vec3(0, -90, 0))));
	}
	/*
	2017.8.12
	����BUG
	_combatTurn���ͷ�
	*/
	_combatTurn->setVisible(true);

	_combatTurn->setPosition(getTurnPosition()+
		Vec2(0,30));
	
}

Point CombatUI::getTurnPosition()
{
	auto combatinstance= CombatManage::getInstance();
	
	//�����ҿ���״̬��������Կ��ƾͰѼ�ͷ�������ͷ�ϣ������ڹ���ͷ��
	if (combatinstance->_playerControlStatus)
	{
		switch (combatinstance->_playerIndex)
		{
		case 0:
			combatinstance->_playerControlStatus = false;
			break;
		case 1:
			return _playerOne->getPosition();
			break;
		case 2:
			return _playerTwo->getPosition();
			break;
		case 3:
			return _playerThree->getPosition();
			break;
		default:
			break;
		} 
	}

	//���������Ҳ�����ʱ��
	if (!combatinstance->_playerControlStatus)
	{
		switch (combatinstance->_monsterIndex)
		{
		case 0:
			combatinstance->_playerControlStatus = true;
			break;
		case 1:
			if (combatinstance->_combatTargetsList[0])
			{
				return combatinstance->_combatTargetsList[0]->
					getPosition();
			}
			break;
		case 2:
			if (combatinstance->_combatTargetsList[1])
			{
				return combatinstance->_combatTargetsList[1]->
					getPosition();
			}
			break;
		case 3:
			if (combatinstance->_combatTargetsList[2])
			{
				return combatinstance->_combatTargetsList[2]->
					getPosition();
			}
			break;
		default:
			break;
		}
	}

	return Point(0,0);
}

void CombatUI::viewTarget(cocos2d::Ref * pSender, Monster * sprite)
{
	
}

void CombatUI::hideOperationItem()
{
	if (_operateMenu)
	{
		_operateMenu->setVisible(false);
	}
}


void CombatUI::viewOperationItem(cocos2d::Node * pSender)
{
	if (_operateMenu)
	{
		_operateMenu->setVisible(true);
	}
}

void CombatUI::hideTurnSprite()
{
	if (_combatTurn)
	{
		_combatTurn->setVisible(false);
	}
}

void CombatUI::viewTurnSprite(cocos2d::Node * pSender)
{
	if (_combatTurn)
	{
		_combatTurn->setVisible(true);
	}
}

void CombatUI::caclulatePlayerDamage(cocos2d::Node * pSender)
{
	CombatManage::getInstance()->caculatePlayerDamage();
}

void CombatUI::caclulateMonsterDamage(cocos2d::Node * pSender)
{
	CombatManage::getInstance()->caculateMonsterDamage();
}

void CombatUI::afterAttack(cocos2d::Node * pSender)
{
	auto combatmanage = CombatManage::getInstance();
	CCLOG("attack button click");
	if (combatmanage->isSuccess())
	{
		this->removeFromParentAndCleanup(true);
	}
	//bool tmpcontrolstatus = combatmanage->_playerControlStatus;
	//���һ������ʾ����һ����ɫ���߹����ж���
	combatmanage->finishOneStep();
	//��������ָʾͼ��
	this->setCombatTurn();
	
	if (combatmanage->_playerControlStatus)
	{
		//������ʾ��ť
		viewOperationItem(this);
	}
	else if (!combatmanage->_playerControlStatus)
	{
		//���ز�����ť,ֱ�����ﶯ���������
		hideOperationItem();
		//��0.5�룬�����ж�
		this->scheduleOnce(
			schedule_selector(CombatUI::monstersAct), 0.5f);
	}
}

void CombatUI::afterMonsterAttack(cocos2d::Node * pSender)
{
	auto combatmanage = CombatManage::getInstance();
	CCLOG("afterMonsterAttack");  
	//bool tmpcontrolstatus = combatmanage->_playerControlStatus;
	//���һ������ʾ����һ����ɫ���߹����ж���
	//���������ҿ���״̬
	if (combatmanage->_playerControlStatus)
	{
		this->setCombatTurn();
		viewOperationItem(this);
		return;
	}
	//�����������ҿ���״̬
	combatmanage->finishOneStep();
	//���һ������Ժ����Ҳ���
	if (combatmanage->_playerControlStatus)
	{
		this->setCombatTurn();
		viewOperationItem(this);
		//��������ָʾͼ��

		return;
	}
	this->setCombatTurn();
	//���ز�����ť,ֱ�����ﶯ���������
	hideOperationItem();
	//��0.5�룬�����ж�
	this->scheduleOnce(
		schedule_selector(CombatUI::monstersAct), 0.5f);
}

void CombatUI::receiveCaclulateNotification(Ref * data)
{
	//�ӹ������ﴫ��Ķ�����Ϣ����Ȼ�ǹ�����˺�
	caclulateMonsterDamage(this);
	CCLOG("caculate the damage");
}

void CombatUI::receiveMonsterAttackFinishNotification(Ref * data)
{
	CCLOG("monster attack finish");
	afterMonsterAttack(this);
}


void CombatUI::monstersAct(float dt)
{
	CCLOG("monster act");
	auto combatmanage= CombatManage::getInstance();
	if (combatmanage->_playerControlStatus)
	{
		return;
	}

	auto monster = combatmanage->_combatTargetsList[0];
	switch (combatmanage->_monsterIndex)
	{
	case 0:
		combatmanage->_monsterIndex=1;
	case 1:
		monster = combatmanage->_combatTargetsList[0];
		break;
	case 2:
		monster = combatmanage->_combatTargetsList[1];
		break;  
	case 3:
		monster = combatmanage->_combatTargetsList[2];
		break;
	default:
		break;
	}
	this->scheduleOnce(CC_CALLBACK_1(
		CombatUI::monsterAttack,this,monster),0,"monsteractschedule");
}

void CombatUI::monsterAttack(float dt, Monster* monster)
{
	monster->attack(0);
}

void CombatUI::popMsgLabel(std::string str)
{
	auto msgLabel = LabelTTF::create(
		wstrtoutf8::CreateUTF8(str.c_str()), "����", 24);
	msgLabel->setPosition(Director::getInstance()->getWinSize() / 2);
	this->addChild(msgLabel, UILAYER3th, "msgLabel");

	msgLabel->runAction(
		Sequence::create(
			Spawn::create(FadeOut::create(1.5f),
				MoveBy::create(1.5f, Vec2(0, 50)), NULL)
			//DelayTime::create(1.0f)
			,
			CallFuncN::create(this, callfuncN_selector(CombatUI::deleteNode))
			,
			NULL
		)
	);
}

void CombatUI::runawayClick(cocos2d::Ref * pSender)
{
	//�����ҿ���״̬Ϊfalse,�����ܿ���
	if (!CombatManage::getInstance()->_playerControlStatus)
	{
		return;
	}
	/*ע�⣬��Ϊ�ڴ�����֮�����û����ӵ��ڵ���
	�п��ܻᱻ�Զ��ͷţ����ԣ�һ��Ҫ��ӵ��ڵ��С�
	*/
	CombatManage::getInstance()->deleteMonsters();
	this->removeFromParentAndCleanup(true);
}

void CombatUI::attackClick(cocos2d::Ref * pSender)
{
	auto combatmanage = CombatManage::getInstance();
	if (!combatmanage->_playerControlStatus)
	{
		//���������Ҳ�����ʱ�䣬ֱ�ӷ���
		return;
	}
	//����
	hideTurnSprite();//�����ִ�ָʾͼ��
	hideOperationItem();//���ز�����ť

	//������������ʾ������ť
	auto tmpsprite = _playerOne;
	switch (combatmanage->_playerIndex)
	{
	case 1:
		tmpsprite = _playerOne;
		break;
	case 2:
		tmpsprite = _playerTwo;
		break;
	case 3:
		tmpsprite = _playerThree;
		break;
	default:
		break;
	}
	tmpsprite->runAction(Sequence::create(
		MoveBy::create(0.5f, Vec2(0, 50)),
		DelayTime::create(0.2f),
		CallFuncN::create(
			this, callfuncN_selector(
				CombatUI::caclulatePlayerDamage)),
		MoveBy::create(0.5f, Vec2(0, -50)),
		CallFuncN::create(
			this, callfuncN_selector(
				CombatUI::afterAttack)), NULL));
	//normalAttack(this);
}

void CombatUI::bagClick(cocos2d::Ref * pSender)
{
}

void CombatUI::skillClick(cocos2d::Ref * pSender)
{
	auto combatmanage = CombatManage::getInstance();
	if (!combatmanage->_playerControlStatus)
	{
		//���������Ҳ�����ʱ�䣬ֱ�ӷ���
		return;
	}
	CCLOG("skill button click");
}

void CombatUI::deleteNode(cocos2d::Node * pSender)
{
	(pSender)->removeFromParentAndCleanup(true);
}

void CombatUI::cleanup()
{
	Layer::cleanup();
	//������Ƴ��۲��߻��γ��ڴ�й¶
	//����ָ���Ī��������
	//����_turnSprite�������ͼ��ͻᱻ��ֵ��ͷ�
	NotificationCenter::getInstance()->
		removeAllObservers(this);
}

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
	setCombatTurn();//顺序图标
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
	//添加进玩家角色列表
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

	//随机创建怪物
	combatmanage->createMonstersRandom(this);

	for (int i=0;i<3;i++)
	{
		//如果存在目标（如果怪物已被生成）
		if (combatmanage->_combatTargetsList[i])
		{
			//设置怪物位置并加入到节点中
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
			_operateAttackItem=NULL;//攻击
			_operateRunawayItem=NULL;//逃跑
			_operateSkillItem=NULL;//技能
			_operateBagItem=NULL;//背包
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
	//如果没有发生初始化，先进行初始化
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
	发现BUG
	_combatTurn被释放
	*/
	_combatTurn->setVisible(true);

	_combatTurn->setPosition(getTurnPosition()+
		Vec2(0,30));
	
}

Point CombatUI::getTurnPosition()
{
	auto combatinstance= CombatManage::getInstance();
	
	//检查玩家控制状态，如果可以控制就把箭头设在玩家头上，否则在怪物头上
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

	//如果不是玩家操作的时间
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
	//完成一步，表示该下一个角色或者怪物行动了
	combatmanage->finishOneStep();
	//重新设置指示图标
	this->setCombatTurn();
	
	if (combatmanage->_playerControlStatus)
	{
		//重新显示按钮
		viewOperationItem(this);
	}
	else if (!combatmanage->_playerControlStatus)
	{
		//隐藏操作按钮,直到怪物动作播放完毕
		hideOperationItem();
		//过0.5秒，怪物行动
		this->scheduleOnce(
			schedule_selector(CombatUI::monstersAct), 0.5f);
	}
}

void CombatUI::afterMonsterAttack(cocos2d::Node * pSender)
{
	auto combatmanage = CombatManage::getInstance();
	CCLOG("afterMonsterAttack");  
	//bool tmpcontrolstatus = combatmanage->_playerControlStatus;
	//完成一步，表示该下一个角色或者怪物行动了
	//如果处于玩家控制状态
	if (combatmanage->_playerControlStatus)
	{
		this->setCombatTurn();
		viewOperationItem(this);
		return;
	}
	//如果不处于玩家控制状态
	combatmanage->finishOneStep();
	//如果一步完成以后该玩家操作
	if (combatmanage->_playerControlStatus)
	{
		this->setCombatTurn();
		viewOperationItem(this);
		//重新设置指示图标

		return;
	}
	this->setCombatTurn();
	//隐藏操作按钮,直到怪物动作播放完毕
	hideOperationItem();
	//过0.5秒，怪物行动
	this->scheduleOnce(
		schedule_selector(CombatUI::monstersAct), 0.5f);
}

void CombatUI::receiveCaclulateNotification(Ref * data)
{
	//从怪物类里传入的订阅消息，当然是怪物的伤害
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
		wstrtoutf8::CreateUTF8(str.c_str()), "隶书", 24);
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
	//如果玩家控制状态为false,即不能控制
	if (!CombatManage::getInstance()->_playerControlStatus)
	{
		return;
	}
	/*注意，因为在创建了之后如果没有添加到节点中
	有可能会被自动释放，所以，一定要添加到节点中。
	*/
	CombatManage::getInstance()->deleteMonsters();
	this->removeFromParentAndCleanup(true);
}

void CombatUI::attackClick(cocos2d::Ref * pSender)
{
	auto combatmanage = CombatManage::getInstance();
	if (!combatmanage->_playerControlStatus)
	{
		//如果不是玩家操作的时间，直接返回
		return;
	}
	//隐藏
	hideTurnSprite();//隐藏轮次指示图标
	hideOperationItem();//隐藏操作按钮

	//动作结束后显示操作按钮
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
		//如果不是玩家操作的时间，直接返回
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
	//如果不移除观察者会形成内存泄露
	//会出现各种莫名的问题
	//比如_turnSprite这个次序图标就会被奇怪的释放
	NotificationCenter::getInstance()->
		removeAllObservers(this);
}

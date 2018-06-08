#include "Monster.h"
#include "XData\DataManage.h"
#include "CombatManage.h"

Monster * Monster::createWithSpriteFrame(
	SpriteFrame *spriteFrame, const Monster* monster)
{
	Monster *sprite = new (std::nothrow) Monster(monster);
	if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

Monster::~Monster()
{
	//deleteRewardItemList();
}

Monster::Monster()
{
}

Monster::Monster(int id)
{
	DataManage::getInstance()->readMonsterData(this,id);
	initSprite();
}

//bool Monster::init(const Monster * monster)
//{
//	_id = monster->_id;
//	_name = monster->_name;
//	_type = monster->_type;
//	_standUrl = monster->_standUrl;
//	_attackUrl = monster->_attackUrl;
//	_hitUrl = monster->_hitUrl;
//	_intro = monster->_intro;
//
//	_rewardItemList = monster->_rewardItemList;
//	_skillList = monster->_skillList;
//	_level = monster->_level;
//	_life = monster->_life;
//	_magic = monster->_magic;
//	_attack = monster->_attack;
//	_defence = monster->_defence;
//	_exp = monster->_exp;
//	_money = monster->_money;
//
//	//初始化三个Cache
//	//由系统自动释放资源，只要MonsterManage中的资源不释放
//	//这个CombatManager中的Monster实例删除也不会释放以下资源
//	_standFrameCache = monster->_standFrameCache;
//	_attackFrameCache = monster->_attackFrameCache;
//	_hitFrameCache = monster->_hitFrameCache;
//
//	/*this->_spriteFrame=Sprite::createWithSpriteFrame(_standFrameCache->
//	getSpriteFrameByName("down1.png"));*/
//	// 初始动作
//	//stand();
//	return true;
//}

Monster::Monster(const Monster* monster)
{
	
	_id=monster->_id;
	_name = monster->_name;
	_type = monster->_type;
	_standUrl = monster->_standUrl;
	_attackUrl = monster->_attackUrl;
	_hitUrl = monster->_hitUrl;
	_intro = monster->_intro;

	_rewardItemList = monster->_rewardItemList;
	_skillList = monster->_skillList;
	_level = monster->_level;
	_life = monster->_life;
	_magic = monster->_magic;
	_attack = monster->_attack;
	_defence = monster->_defence;
	_exp = monster->_exp;
	_money = monster->_money;

	//初始化三个Cache
	//由系统自动释放资源，只要MonsterManage中的资源不释放
	//这个CombatManager中的Monster实例删除也不会释放以下资源
	_standFrameCache = monster->_standFrameCache;
	_attackFrameCache= monster->_attackFrameCache;
	_hitFrameCache= monster->_hitFrameCache;

	/*this->_spriteFrame=Sprite::createWithSpriteFrame(_standFrameCache->
		getSpriteFrameByName("down1.png"));*/
	// 初始动作
	//stand();
}


void Monster::initSprite()
{
	_standFrameCache = HelpTool::GetFrameCache(
		("player/plist.plist"), ("player/plist.png"));
	_attackFrameCache = HelpTool::GetFrameCache(
		("player/plist.plist"), ("player/plist.png"));
	_hitFrameCache = HelpTool::GetFrameCache(
		("player/plist.plist"), ("player/plist.png"));
	//_sprite = Sprite::createWithSpriteFrame(_playerFrameCache->getSpriteFrameByName("up1.png"));
	//setSprite();
	//_sprite = Sprite::create(_playerSpriteSrc);
	//this->addChild(_sprite, PLAYERLAYER);
	//this->createWithSpriteFrameName();
}

bool Monster::stand()
{
	this->setSpriteFrame(_standFrameCache->getSpriteFrameByName("down1.png"));
	return true;
}

void Monster::attack(float dt)
{
	//this->_id;
	/*auto animation = Animation::create();
	animation->addSpriteFrame(
		_attackFrameCache->getSpriteFrameByName("down1.png"));
	animation->addSpriteFrame(
		_attackFrameCache->getSpriteFrameByName("down2.png"));
	animation->addSpriteFrame(
		_attackFrameCache->getSpriteFrameByName("down3.png"));
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);*/
	this->runAction(Sequence::create(
		MoveBy::create(0.5f, Vec2(0, -50)),
		DelayTime::create(0.2f),
		CallFuncN::create(
			this, callfuncN_selector(
				Monster::postCaclulateNotification)),
		MoveBy::create(0.5f, Vec2(0, 50)),
		CallFuncN::create(
			this, callfuncN_selector(
				Monster::postAttackFinishNotification)), NULL));
	//normalAttack(this);
}


bool Monster::hit(int const & damage)
{
	this->runAction(
		Sequence::create(
			Spawn::create(
				MoveBy::create(0.2f, Vec2(0, -10))
			),
			Spawn::create(
				MoveBy::create(0.2f, Vec2(0, 10))
			)
		)
	);
	if ((_life-=damage)>0)
	{
		//减去玩家对怪物造成的伤害值
		//如果死了返回true，如果没死返回false
		return false;
	}
	return true;
}

void Monster::postCaclulateNotification(cocos2d::Node * pSender)
{
	NotificationCenter::getInstance()->postNotification("caclulatedamage",NULL);
}

void Monster::postAttackFinishNotification(cocos2d::Node * pSender)
{
	NotificationCenter::getInstance()->postNotification("monsterattack", NULL);
}

void Monster::setPlayerControlDisactive(cocos2d::Node * pSender)
{
	CombatManage::getInstance()->_playerControlStatus = false;
}

void Monster::setPlayerControlActive(cocos2d::Node * pSender)
{
	CombatManage::getInstance()->_playerControlStatus = true;
}

void Monster::deleteRewardItemList()
{
	/*if (_rewardItemList.size())
	{
		for (int i = 0; i < _rewardItemList.size(); i++)
		{
			delete _rewardItemList[i];
		}
	}*/
}

void Monster::initTouch()
{
	/*auto listener = ;
	listener->onTouchBegan = CC_CALLBACK_1(Monster::onTouchBegan, this);

	listener->onTouchMoved = CC_CALLBACK_2(Monster::onTouchMoved, this);

	listener->onTouchEnded = CC_CALLBACK_2(Monster::onTouchEnded, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);*/
}

bool Monster::onTouchBegan(Touch * tTouch, Event * eEvent)
{
	return false;
}

void Monster::onTouchMoved(Touch * tTouch, Event * eEvent)
{
}

void Monster::onTouchEnded(Touch * tTouch, Event * eEvent)
{
}

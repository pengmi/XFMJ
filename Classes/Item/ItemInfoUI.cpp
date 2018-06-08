#include "Item\ItemInfoUI.h"
#include "tool\WStrToUTF8.h"
bool ItemInfoUI::init()
{
	initTouch();
	initItemMap();
	return true;
}

bool ItemInfoUI::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * user_event)
{
	return true;
}

void ItemInfoUI::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * user_event)
{
	deleteItemMap();//先delete栈空间上无法自动释放的对象
	this->removeFromParentAndCleanup(true);
}

void ItemInfoUI::listItemInfo(ItemInBag *IIb)
{
	std::string tmpNum;
	std::string tmpStr;
	int index=6;
	//存在名字
	if (IIb->item->_itemName != "")
	{
		--index;
		tmpStr = IIb->item->_itemName;
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
	//	numLabel->setColor(ccc3(50, 50, 100));
		this->addChild(numLabel);
	}
	//物品类型
	if (IIb->item->_type!="")
	{
		--index;
		tmpStr = _map->at(IIb->item->_type);
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
	//	numLabel->setColor(ccc3(100, 50, 100));
		this->addChild(numLabel);
	}
	//物品数量
	if (IIb->num)
	{
		--index;
		tmpStr ="数量:"+ int2str(IIb->num);
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
	//	numLabel->setColor(ccc3(100,100, 100));
		this->addChild(numLabel);
	}
	//物品单价
	if (IIb->item->_price)
	{
		--index;
		tmpStr = "单价:" + int2str(IIb->item->_price);
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
	//	numLabel->setColor(ccc3(150, 0, 100));
		this->addChild(numLabel);
	}
	//物品介绍
	if (IIb->item->_itemIntro!="")
	{
		--index;
		tmpStr = IIb->item->_itemIntro;
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
	//	numLabel->setColor(ccc3(200, 0, 100));
		this->addChild(numLabel);
	}

	//增加生命魔法最大值
	if (IIb->item->_addMaxLife|| IIb->item->_addMaxMagic)
	{
		--index;
		tmpStr = "";
		if (IIb->item->_addMaxLife)
		{
			tmpStr ="活力上限:" 
				+int2str(IIb->item->_addMaxLife)
				+" ";
		}
		if (IIb->item->_addMaxMagic)
		{
			tmpStr += "法力上限:" + 
				int2str(IIb->item->_addMaxMagic);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
	//	numLabel->setColor(ccc3(250, 0, 100));
		this->addChild(numLabel);
	}
	

	//生命魔法
	if (IIb->item->_addLife|| IIb->item->_addMagic)
	{
		--index;
		tmpStr = "";
		if (IIb->item->_addLife)
		{
			tmpStr ="活力:"+ int2str(IIb->item->_addLife)+" ";	
		}
		if (IIb->item->_addMagic)
		{
			tmpStr += "法力:" + int2str(IIb->item->_addMagic);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
	//	numLabel->setColor(ccc3(200,50, 100));
		this->addChild(numLabel);
	}
	
	//属性
	if (IIb->item->_addPower || IIb->item->_addAgility 
		|| IIb->item->_addIntelligence)
	{
		--index;
		tmpStr = "";
		if (IIb->item->_addPower)
		{
			tmpStr = "蛮力:" + int2str(IIb->item->_addPower)+" ";
		}
		if (IIb->item->_addAgility)
		{
			tmpStr += "身法:" + int2str(IIb->item->_addAgility) + " ";
		}
		if (IIb->item->_addIntelligence)
		{
			tmpStr += "灵力:" + int2str(IIb->item->_addIntelligence);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
	//	numLabel->setColor(ccc3(200, 100, 100));
		this->addChild(numLabel);
	}

	//攻击防护
	if (IIb->item->_addAttack || IIb->item->_addDefence)
	{
		--index;
		tmpStr = "";
		if (IIb->item->_addAttack)
		{
			tmpStr = "攻击:" + int2str(IIb->item->_addAttack) + " ";
		}
		if (IIb->item->_addDefence)
		{
			tmpStr += "防御:" + int2str(IIb->item->_addDefence);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
		//numLabel->setColor(ccc3(200, 150, 100));
		this->addChild(numLabel);
	}

	//命中闪避
	if (IIb->item->_addHit || IIb->item->_addDodge)
	{
		--index;
		tmpStr = "";
		if (IIb->item->_addHit)
		{
			tmpStr = "命中:" + int2str(IIb->item->_addHit) + " ";
		}
		if (IIb->item->_addDodge)
		{
			tmpStr += "闪避:" + int2str(IIb->item->_addDodge);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
		//numLabel->setColor(ccc3(200, 200, 100));
		this->addChild(numLabel);
	}
}

void ItemInfoUI::listItemInfo(Item * item, int itemInBagNum)
{
	std::string tmpNum;
	std::string tmpStr;
	int index = 6;
	//存在名字
	if (item->_itemName != "")
	{
		--index;
		tmpStr = item->_itemName;
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
		//	numLabel->setColor(ccc3(50, 50, 100));
		this->addChild(numLabel);
	}
	//物品类型
	if (item->_type != "")
	{
		--index;
		tmpStr = _map->at(item->_type);
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
		//	numLabel->setColor(ccc3(100, 50, 100));
		this->addChild(numLabel);
	}
	//物品数量存在
	if (itemInBagNum)
	{
		--index;
		tmpStr = "数量:" + int2str(itemInBagNum);
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
		//	numLabel->setColor(ccc3(100,100, 100));
		this->addChild(numLabel);
	}
	//物品单价
	if (item->_price)
	{
		--index;
		tmpStr = "单价:" + int2str(item->_price);
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
		//	numLabel->setColor(ccc3(150, 0, 100));
		this->addChild(numLabel);
	}
	//物品介绍
	if (item->_itemIntro != "")
	{
		--index;
		tmpStr = item->_itemIntro;
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
		//	numLabel->setColor(ccc3(200, 0, 100));
		this->addChild(numLabel);
	}

	//增加生命魔法最大值
	if (item->_addMaxLife || item->_addMaxMagic)
	{
		--index;
		tmpStr = "";
		if (item->_addMaxLife)
		{
			tmpStr = "活力上限:"
				+ int2str(item->_addMaxLife)
				+ " ";
		}
		if (item->_addMaxMagic)
		{
			tmpStr += "法力上限:" +
				int2str(item->_addMaxMagic);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
		//	numLabel->setColor(ccc3(250, 0, 100));
		this->addChild(numLabel);
	}


	//生命魔法
	if (item->_addLife || item->_addMagic)
	{
		--index;
		tmpStr = "";
		if (item->_addLife)
		{
			tmpStr = "活力:" + int2str(item->_addLife) + " ";
		}
		if (item->_addMagic)
		{
			tmpStr += "法力:" + int2str(item->_addMagic);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
		//	numLabel->setColor(ccc3(200,50, 100));
		this->addChild(numLabel);
	}

	//属性
	if (item->_addPower || item->_addAgility
		|| item->_addIntelligence)
	{
		--index;
		tmpStr = "";
		if (item->_addPower)
		{
			tmpStr = "蛮力:" + int2str(item->_addPower) + " ";
		}
		if (item->_addAgility)
		{
			tmpStr += "身法:" + int2str(item->_addAgility) + " ";
		}
		if (item->_addIntelligence)
		{
			tmpStr += "灵力:" + int2str(item->_addIntelligence);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
		//	numLabel->setColor(ccc3(200, 100, 100));
		this->addChild(numLabel);
	}

	//攻击防护
	if (item->_addAttack || item->_addDefence)
	{
		--index;
		tmpStr = "";
		if (item->_addAttack)
		{
			tmpStr = "攻击:" + int2str(item->_addAttack) + " ";
		}
		if (item->_addDefence)
		{
			tmpStr += "防御:" + int2str(item->_addDefence);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
		//numLabel->setColor(ccc3(200, 150, 100));
		this->addChild(numLabel);
	}

	//命中闪避
	if (item->_addHit || item->_addDodge)
	{
		--index;
		tmpStr = "";
		if (item->_addHit)
		{
			tmpStr = "命中:" + int2str(item->_addHit) + " ";
		}
		if (item->_addDodge)
		{
			tmpStr += "闪避:" + int2str(item->_addDodge);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"隶书", 24);
		numLabel->setPosition(0, index * 24);
		//numLabel->setColor(ccc3(200, 200, 100));
		this->addChild(numLabel);
	}
}

void ItemInfoUI::initItemMap()
{
	//实例化对象
	_map =new std::map<std::string, std::string>();
	//药品，仙药，武器，帽子，衣服，披风，手套，裤子，鞋子，饰品
	//static const enum ITEMTYPE{medicine, forever, weapon, head
	//, clothes, cloak, glove, tasses, shoes, ornament};
	_map->insert(std::pair<std::string, std::string>("medicine","药品"));
	_map->insert(std::pair<std::string, std::string>("forever", "仙药"));
	_map->insert(std::pair<std::string, std::string>("weapon", "武器"));
	_map->insert(std::pair<std::string, std::string>("head", "帽子"));
	_map->insert(std::pair<std::string, std::string>("clothes", "衣服"));
	_map->insert(std::pair<std::string, std::string>("cloak", "披风"));
	_map->insert(std::pair<std::string, std::string>("glove", "手套"));
	_map->insert(std::pair<std::string, std::string>("tasses", "裤子"));
	_map->insert(std::pair<std::string, std::string>("shoes", "鞋子"));
	_map->insert(std::pair<std::string, std::string>("ornament", "饰品"));
		
}

void ItemInfoUI::deleteItemMap()
{
	if (_map)
	{
		delete _map;
	}
}

void ItemInfoUI::initTouch()
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ItemInfoUI::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(ItemInfoUI::onTouchEnded, this);
	listener->setSwallowTouches(true);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->setTouchEnabled(true);
}

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
	deleteItemMap();//��deleteջ�ռ����޷��Զ��ͷŵĶ���
	this->removeFromParentAndCleanup(true);
}

void ItemInfoUI::listItemInfo(ItemInBag *IIb)
{
	std::string tmpNum;
	std::string tmpStr;
	int index=6;
	//��������
	if (IIb->item->_itemName != "")
	{
		--index;
		tmpStr = IIb->item->_itemName;
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
	//	numLabel->setColor(ccc3(50, 50, 100));
		this->addChild(numLabel);
	}
	//��Ʒ����
	if (IIb->item->_type!="")
	{
		--index;
		tmpStr = _map->at(IIb->item->_type);
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
	//	numLabel->setColor(ccc3(100, 50, 100));
		this->addChild(numLabel);
	}
	//��Ʒ����
	if (IIb->num)
	{
		--index;
		tmpStr ="����:"+ int2str(IIb->num);
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
	//	numLabel->setColor(ccc3(100,100, 100));
		this->addChild(numLabel);
	}
	//��Ʒ����
	if (IIb->item->_price)
	{
		--index;
		tmpStr = "����:" + int2str(IIb->item->_price);
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
	//	numLabel->setColor(ccc3(150, 0, 100));
		this->addChild(numLabel);
	}
	//��Ʒ����
	if (IIb->item->_itemIntro!="")
	{
		--index;
		tmpStr = IIb->item->_itemIntro;
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
	//	numLabel->setColor(ccc3(200, 0, 100));
		this->addChild(numLabel);
	}

	//��������ħ�����ֵ
	if (IIb->item->_addMaxLife|| IIb->item->_addMaxMagic)
	{
		--index;
		tmpStr = "";
		if (IIb->item->_addMaxLife)
		{
			tmpStr ="��������:" 
				+int2str(IIb->item->_addMaxLife)
				+" ";
		}
		if (IIb->item->_addMaxMagic)
		{
			tmpStr += "��������:" + 
				int2str(IIb->item->_addMaxMagic);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
	//	numLabel->setColor(ccc3(250, 0, 100));
		this->addChild(numLabel);
	}
	

	//����ħ��
	if (IIb->item->_addLife|| IIb->item->_addMagic)
	{
		--index;
		tmpStr = "";
		if (IIb->item->_addLife)
		{
			tmpStr ="����:"+ int2str(IIb->item->_addLife)+" ";	
		}
		if (IIb->item->_addMagic)
		{
			tmpStr += "����:" + int2str(IIb->item->_addMagic);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
	//	numLabel->setColor(ccc3(200,50, 100));
		this->addChild(numLabel);
	}
	
	//����
	if (IIb->item->_addPower || IIb->item->_addAgility 
		|| IIb->item->_addIntelligence)
	{
		--index;
		tmpStr = "";
		if (IIb->item->_addPower)
		{
			tmpStr = "����:" + int2str(IIb->item->_addPower)+" ";
		}
		if (IIb->item->_addAgility)
		{
			tmpStr += "��:" + int2str(IIb->item->_addAgility) + " ";
		}
		if (IIb->item->_addIntelligence)
		{
			tmpStr += "����:" + int2str(IIb->item->_addIntelligence);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
	//	numLabel->setColor(ccc3(200, 100, 100));
		this->addChild(numLabel);
	}

	//��������
	if (IIb->item->_addAttack || IIb->item->_addDefence)
	{
		--index;
		tmpStr = "";
		if (IIb->item->_addAttack)
		{
			tmpStr = "����:" + int2str(IIb->item->_addAttack) + " ";
		}
		if (IIb->item->_addDefence)
		{
			tmpStr += "����:" + int2str(IIb->item->_addDefence);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
		//numLabel->setColor(ccc3(200, 150, 100));
		this->addChild(numLabel);
	}

	//��������
	if (IIb->item->_addHit || IIb->item->_addDodge)
	{
		--index;
		tmpStr = "";
		if (IIb->item->_addHit)
		{
			tmpStr = "����:" + int2str(IIb->item->_addHit) + " ";
		}
		if (IIb->item->_addDodge)
		{
			tmpStr += "����:" + int2str(IIb->item->_addDodge);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
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
	//��������
	if (item->_itemName != "")
	{
		--index;
		tmpStr = item->_itemName;
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
		//	numLabel->setColor(ccc3(50, 50, 100));
		this->addChild(numLabel);
	}
	//��Ʒ����
	if (item->_type != "")
	{
		--index;
		tmpStr = _map->at(item->_type);
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
		//	numLabel->setColor(ccc3(100, 50, 100));
		this->addChild(numLabel);
	}
	//��Ʒ��������
	if (itemInBagNum)
	{
		--index;
		tmpStr = "����:" + int2str(itemInBagNum);
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
		//	numLabel->setColor(ccc3(100,100, 100));
		this->addChild(numLabel);
	}
	//��Ʒ����
	if (item->_price)
	{
		--index;
		tmpStr = "����:" + int2str(item->_price);
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
		//	numLabel->setColor(ccc3(150, 0, 100));
		this->addChild(numLabel);
	}
	//��Ʒ����
	if (item->_itemIntro != "")
	{
		--index;
		tmpStr = item->_itemIntro;
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
		//	numLabel->setColor(ccc3(200, 0, 100));
		this->addChild(numLabel);
	}

	//��������ħ�����ֵ
	if (item->_addMaxLife || item->_addMaxMagic)
	{
		--index;
		tmpStr = "";
		if (item->_addMaxLife)
		{
			tmpStr = "��������:"
				+ int2str(item->_addMaxLife)
				+ " ";
		}
		if (item->_addMaxMagic)
		{
			tmpStr += "��������:" +
				int2str(item->_addMaxMagic);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
		//	numLabel->setColor(ccc3(250, 0, 100));
		this->addChild(numLabel);
	}


	//����ħ��
	if (item->_addLife || item->_addMagic)
	{
		--index;
		tmpStr = "";
		if (item->_addLife)
		{
			tmpStr = "����:" + int2str(item->_addLife) + " ";
		}
		if (item->_addMagic)
		{
			tmpStr += "����:" + int2str(item->_addMagic);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
		//	numLabel->setColor(ccc3(200,50, 100));
		this->addChild(numLabel);
	}

	//����
	if (item->_addPower || item->_addAgility
		|| item->_addIntelligence)
	{
		--index;
		tmpStr = "";
		if (item->_addPower)
		{
			tmpStr = "����:" + int2str(item->_addPower) + " ";
		}
		if (item->_addAgility)
		{
			tmpStr += "��:" + int2str(item->_addAgility) + " ";
		}
		if (item->_addIntelligence)
		{
			tmpStr += "����:" + int2str(item->_addIntelligence);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
		//	numLabel->setColor(ccc3(200, 100, 100));
		this->addChild(numLabel);
	}

	//��������
	if (item->_addAttack || item->_addDefence)
	{
		--index;
		tmpStr = "";
		if (item->_addAttack)
		{
			tmpStr = "����:" + int2str(item->_addAttack) + " ";
		}
		if (item->_addDefence)
		{
			tmpStr += "����:" + int2str(item->_addDefence);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
		//numLabel->setColor(ccc3(200, 150, 100));
		this->addChild(numLabel);
	}

	//��������
	if (item->_addHit || item->_addDodge)
	{
		--index;
		tmpStr = "";
		if (item->_addHit)
		{
			tmpStr = "����:" + int2str(item->_addHit) + " ";
		}
		if (item->_addDodge)
		{
			tmpStr += "����:" + int2str(item->_addDodge);
		}
		auto numLabel = LabelTTF::create(
			wstrtoutf8::CreateUTF8(tmpStr.c_str()),
			"����", 24);
		numLabel->setPosition(0, index * 24);
		//numLabel->setColor(ccc3(200, 200, 100));
		this->addChild(numLabel);
	}
}

void ItemInfoUI::initItemMap()
{
	//ʵ��������
	_map =new std::map<std::string, std::string>();
	//ҩƷ����ҩ��������ñ�ӣ��·������磬���ף����ӣ�Ь�ӣ���Ʒ
	//static const enum ITEMTYPE{medicine, forever, weapon, head
	//, clothes, cloak, glove, tasses, shoes, ornament};
	_map->insert(std::pair<std::string, std::string>("medicine","ҩƷ"));
	_map->insert(std::pair<std::string, std::string>("forever", "��ҩ"));
	_map->insert(std::pair<std::string, std::string>("weapon", "����"));
	_map->insert(std::pair<std::string, std::string>("head", "ñ��"));
	_map->insert(std::pair<std::string, std::string>("clothes", "�·�"));
	_map->insert(std::pair<std::string, std::string>("cloak", "����"));
	_map->insert(std::pair<std::string, std::string>("glove", "����"));
	_map->insert(std::pair<std::string, std::string>("tasses", "����"));
	_map->insert(std::pair<std::string, std::string>("shoes", "Ь��"));
	_map->insert(std::pair<std::string, std::string>("ornament", "��Ʒ"));
		
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

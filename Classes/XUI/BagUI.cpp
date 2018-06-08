#include "BagUI.h"
#include "Item\BagManage.h"
#include "Item\ItemInfoUI.h"

bool BagUI::init()
{
	initMenu();
	setBagBack();
	setEquipBack();

	memset(_imageItem, NULL, sizeof(_imageItem));

	loadBagData(1);//��ʼ������
	setCurHero(PlayerManage::getInstance()->
		_huangZaiLayer);
	menuClickLoadData(this,_curHero);//��ʼ��װ����������װ��

	return true;
}

void BagUI::setBagBack()
{
	_bagback = Sprite::create("UI/bagback.png");
	this->addChild(_bagback);
	_bagback->setPosition(Director::getInstance()->
		getWinSize().width/2,
		Director::getInstance()->getWinSize().height /2-20);
	/*������Ǯ����label*/
	_money = Label::create(std::string(wstrtoutf8::CreateUTF8("��Ǯ:")
		+HelpTool::int2str(
			BagManage::getInstance()->getMoney())), "����", 20);;
	_money->setColor(ccc3(200,0,0));
	_money->setPosition(_bagback->getPosition().x +
		_bagback->getContentSize().width / 2+
		_money->getContentSize().width / 2
		,
		_bagback->getPosition().y -
		_bagback->getContentSize().height / 2 -
		_money->getContentSize().height / 2
	);
	this->addChild(_money);
	///////////

	_one = MenuItemImage::create("UI/bag_one_off.png", "UI/bag_on.png",
		CC_CALLBACK_1(BagUI::menuClickLoadBag, this,1
		));
	_one->setPosition(_bagback->getPosition().x +
		_bagback->getContentSize().width / 2 -
		_one->getContentSize().width- 
		_one->getContentSize().width/2
		-20
		,
		_bagback->getPosition().y -
		_bagback->getContentSize().height / 2-
		_one->getContentSize().height / 2
	);
	_two = MenuItemImage::create("UI/bag_two_off.png", "UI/bag_on.png",
		CC_CALLBACK_1(BagUI::menuClickLoadBag, this, 2
		));

	_two->setPosition(_bagback->getPosition().x +
		_bagback->getContentSize().width / 2 -
		_one->getContentSize().width/2-10
		,
		_bagback->getPosition().y -
		_bagback->getContentSize().height / 2 -
		_one->getContentSize().height / 2
	);

	_bagIndex = Menu::create(_one,_two,NULL);

	_bagIndex->setPosition(
		Vec2::ZERO
	);
	this->addChild(_bagIndex);

	/*auto emptyItem = MenuItem::create(CC_CALLBACK_1(BagUI::menuClickEmpty, 
		this
		));*/
	_selectedMenu = Menu::create(NULL);//ѡ����Ʒʱ�Ĳ˵�����
	_selectedMenu->setPosition(Vec2::ZERO);
	this->addChild(_selectedMenu);
}

void BagUI::setEquipBack()
{
	_equipback = Sprite::create("UI/equipback.png");
	_equipback->setPosition(Director::getInstance()->
		getWinSize().width - _equipback->getContentSize().width / 2,
		Director::getInstance()->getWinSize().height - _equipback->getContentSize().height / 2 - 10);
	this->addChild(_equipback);

	_equipMenu = Menu::create(NULL);//װ���Ĳ˵�����
	_equipMenu->setPosition(Vec2::ZERO);
	this->addChild(_equipMenu);
}

void BagUI::removeItemCells()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			//ֱ��������0�ж�Ҳ���ã���Ϊ������������
			//�����жϵ�������һ����ֱ�����������жϾͺ�
			//ע��_imageItem[i][j]��Ӧ�ĵ�ַҪ��memsetΪ0�ſ�����ô��
			if (_imageItem[i][j])
			{
				_bagIndex->removeChild(_imageItem[i][j],true);
				_imageItem[i][j] = NULL;
			}
			else
			{
				/*
				ReferenceCount=0,
				�����������ָ����ڴ��ַ�Ѿ����ͷš�
				�������ͷ��ˡ�
				ֱ�Ӹ�ֵΪNULL���ɡ�
				*/
				_imageItem[i][j] = NULL;
			}
			
		}
	}
}

void BagUI::removeBagItemCell(MenuItem * itemPtr)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (itemPtr== _imageItem[i][j])
			{
				_bagIndex->removeChild(_imageItem[i][j],true);
				_imageItem[i][j] = NULL;
				return;
			}
		}
	}
}

void BagUI::loadBagData(int i)
{
	//_curBag = i;
	auto bagmanage = BagManage::getInstance();
	//auto tmpBag = bagmanage->BagOne;
	_tmpBag = bagmanage->BagOne;
	/*auto _tmpBag = &(bagmanage->BagOne);*/
	if (1==i)
	{

	}
	else
	{
		_tmpBag = bagmanage->BagTwo;
	}

	//////////

	loadItem();
}

void BagUI::loadItem()
{
	auto backsize = _bagback->getContentSize();

	float pianyix = backsize.width / 5;
	float pianyiy = backsize.height / 3;



	auto beginposition = ccp(_bagback->getPosition().x
		- backsize.width / 2 + pianyix / 2,
		_bagback->getPosition().y + backsize.height / 2 - pianyiy / 2
	);


	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			//��������ж�����������Ϊ0
			if (_tmpBag[i][j].item&&
				_tmpBag[i][j].num)
			{
				//�������е�ͼ����ʾ�ڱ�������
				_imageItem[i][j] = MenuItemImage::create(
					_tmpBag[i][j].item->_itemUrl,
					_tmpBag[i][j].item->_itemUrl,
					CC_CALLBACK_1(BagUI::itemClickLoadBagItemInfo,
						this, &_tmpBag[i][j])
				);
				_imageItem[i][j]->setPosition(
					beginposition.x + j*pianyix
					,
					beginposition.y - i*pianyiy
				);
				_bagIndex->addChild(_imageItem[i][j]);
			}
			//��������ж���������Ϊ0
			else if (_tmpBag[i][j].item &&
				!_tmpBag[i][j].num)
			{
				delete _tmpBag[i][j].item;
			}
			//�������û�ж�����������Ϊ0
			else if (!_tmpBag[i][j].item &&
				_tmpBag[i][j].num)
			{
				_tmpBag[i][j].num = 0;
			}
		}
	}
}

void BagUI::updateBagData(int & a, int & b)
{
	/*removeItemCells();
	loadItem();*/
	



}


void BagUI::clearListItemInfo()
{
}

void BagUI::listItemInfo(ItemInBag * item)
{
	if (!item->item&&!item->num)
	{
		return;
	}
	auto itemInfoUI = ItemInfoUI::create();
	this->addChild(itemInfoUI,UILAYER3th);
	itemInfoUI->setPosition(Director::getInstance()->getWinSize() / 2);
	itemInfoUI->listItemInfo(item);
}

void BagUI::clearSelectedOperationUI()
{
	if (_selectedMenu)
	{
		if (_useItem)
		{
			_selectedMenu->removeChild(_useItem, true);
			//	_selectedMenu->addChild(_useItem);//��֤���룬��Դȷʵ�ͷţ����ͱ���
			_useItem = NULL;
			
		}
		if (_deleteItem)
		{
			_selectedMenu->removeChild(_deleteItem, true);
			_deleteItem = NULL;
		}
		
	}

}

void BagUI::hideSelectedOperationUI()
{
	_selectedMenu->setVisible(false);
	_selectedMenu->setEnabled(false);
}

void BagUI::viewSelectedOperationUI()
{
	_selectedMenu->setVisible(true);
	_selectedMenu->setEnabled(true);
}

void BagUI::setSelectedOperationUI(cocos2d::Ref * pSender, ItemInBag * itemIB)
{
	if (!itemIB->item||!itemIB->num)
		return;

	if (!_selectedMenu->isVisible())
	{
		viewSelectedOperationUI();
	}
	

	if ((itemIB->item->_type=="medicine"||
		itemIB->item->_type == "forever"))
	{
		_useItem = MenuItemImage::create("UI/bag_use_off.png", "UI/bag_on.png",
			CC_CALLBACK_1(BagUI::useItem, this, itemIB, pSender
			));
		_deleteItem = MenuItemImage::create("UI/bag_delete_off.png", "UI/bag_on.png",
			CC_CALLBACK_1(BagUI::deleteItem, this, itemIB, pSender
			));
	}
	else
	{
		_useItem = MenuItemImage::create("UI/bag_equip_off.png", "UI/bag_on.png",
			CC_CALLBACK_1(BagUI::equipItem, this, itemIB, pSender
			));
		_deleteItem = MenuItemImage::create("UI/bag_delete_off.png", "UI/bag_on.png",
			CC_CALLBACK_1(BagUI::deleteItem, this, itemIB, pSender
			));
	}
	_useItem->setPosition(_bagback->getPosition().x+
		_bagback->getContentSize().width/2+5+
		_useItem->getContentSize().width/2
		,
		_bagback->getPosition().y +
		_bagback->getContentSize().height / 2-
		_useItem->getContentSize().height/2-10
	);
	_deleteItem->setPosition(_bagback->getPosition().x +
		_bagback->getContentSize().width / 2 +5+
		_deleteItem->getContentSize().width / 2
		,
		_bagback->getPosition().y +
		_bagback->getContentSize().height / 2 -
		_deleteItem->getContentSize().height -
		_deleteItem->getContentSize().height/2 -20
	);
	_selectedMenu->addChild(_useItem);
	_selectedMenu->addChild(_deleteItem);
	//_selectedMenu->setEnabled(true);
}

void BagUI::setEquipmentOperationUI(cocos2d::Ref * pSender, ItemInBag * itemIB)
{
	if (!itemIB->item||!itemIB->num)
		return;

	if (!_selectedMenu->isVisible())
	{
		viewSelectedOperationUI();
	}

	if ((itemIB->item->_type == "medicine" ||
		itemIB->item->_type == "forever"))
	{
		_useItem = MenuItemImage::create("UI/bag_use_off.png", "UI/bag_on.png",
			CC_CALLBACK_1(BagUI::useItem, this, itemIB, pSender
			));
		_deleteItem = MenuItemImage::create("UI/bag_delete_off.png", "UI/bag_on.png",
			CC_CALLBACK_1(BagUI::deleteItem, this, itemIB, pSender
			));
	}
	else
	{
		_useItem = MenuItemImage::create("UI/bag_view_off.png", "UI/bag_on.png",
			CC_CALLBACK_1(BagUI::viewItem, this, itemIB
			));
		_deleteItem = MenuItemImage::create("UI/bag_unequip_off.png", "UI/bag_on.png",
			CC_CALLBACK_1(BagUI::unequipItem, this, itemIB, pSender
			));
	}
	_useItem->setPosition(_bagback->getPosition().x +
		_bagback->getContentSize().width / 2 + 5 +
		_useItem->getContentSize().width / 2
		,
		_bagback->getPosition().y +
		_bagback->getContentSize().height / 2 -
		_useItem->getContentSize().height / 2 - 10
	);
	_deleteItem->setPosition(_bagback->getPosition().x +
		_bagback->getContentSize().width / 2 + 5 +
		_deleteItem->getContentSize().width / 2
		,
		_bagback->getPosition().y +
		_bagback->getContentSize().height / 2 -
		_deleteItem->getContentSize().height -
		_deleteItem->getContentSize().height / 2 - 20
	);
	_selectedMenu->addChild(_useItem);
	_selectedMenu->addChild(_deleteItem);
	//_selectedMenu->setEnabled(true);
}

void BagUI::clearEquipmentData()
{
	for (int i = 0; i < 8; ++i)
	{
		/*
		����������0�жϣ�Ҳ������������0�ж�
		��Ϊֻ��һ��װ����
		����bagmanage�����equipment[i]->num
		*/
		if (_equipItem[i])
		{
			_equipMenu->removeChild(_equipItem[i], true);
			_equipItem[i] = NULL;
		}
	}
	
}

void BagUI::removeEquipment(MenuItem *itemPtr)
{
	//�ҵ��˵���Ƴ�
	for (int i = 0; i < 8; i++)
	{
		if (itemPtr== _equipItem[i])
		{
			_equipMenu->removeChild(_equipItem[i],true);
			_equipItem[i] = NULL;
			return;
		}
	}
}

void BagUI::loadEquipmentData()
{
	auto backsize = _equipback->getContentSize();

	float pianyix = backsize.width / 8;



	auto beginposition = ccp(_equipback->getPosition().x
		- backsize.width / 2 + pianyix / 2,
		_equipback->getPosition().y
	);

	auto bagmanage = BagManage::getInstance();

	for (int i = 0; i < 8; ++i)
	{
		if (bagmanage->Equipment[i].item)
		{
			_equipItem[i] = MenuItemImage::create(
				bagmanage->Equipment[i].item->_itemUrl,
				bagmanage->Equipment[i].item->_itemUrl,
				CC_CALLBACK_1(BagUI::itemClickLoadEquipmentInfo, this,
					&bagmanage->Equipment[i])
			);
			_equipItem[i]->setPosition(beginposition.x+i*pianyix,
				beginposition.y);
			_equipMenu->addChild(_equipItem[i]);
		}
	}
}


void BagUI::menuClickLoadBag(cocos2d::Ref * pSender,int n)
{
	removeItemCells();
	loadBagData(n);
}

void BagUI::menuClickLoadData(cocos2d::Ref * pSender, HeroLayer * s)
{
	//this->removeAllChildren();//��������е��ӽڵ㣬Ȼ�����¼���
	//initBackground();
	//�������Ӣ����Ϊ��ʱ����
	this->setCurHero(s);
	//�������װ������bagmanagement���棬�Ա�ʹ��
	BagManage::getInstance()->loadPlayerEquipmentData(s);
	clearEquipmentData();//���װ������
	loadEquipmentData();//����װ������
}

void BagUI::itemClickLoadBagItemInfo(cocos2d::Ref * pSender, 
	ItemInBag * itemIB)
{
	CCLOG("Item click!!");
	//�����Ʒ�Ժ�
	clearSelectedOperationUI();
	listItemInfo(itemIB);//�г���Ʒ��Ϣ
	setSelectedOperationUI(pSender,itemIB);//�г�����UI
}

void BagUI::itemClickLoadEquipmentInfo(cocos2d::Ref * pSender, 
	ItemInBag* itemIB)
{
	CCLOG("Equipment click!!");
	//�����Ʒ�Ժ�
	clearSelectedOperationUI();
	listItemInfo(itemIB);//�г���Ʒ��Ϣ
	setEquipmentOperationUI(pSender, itemIB);//�г�����UI
}

void BagUI::itemClickShowInfo(cocos2d::Ref * pSender, ItemInBag * itemIB)
{
	CCLOG("itemClickShowInfo!!");
	listItemInfo(itemIB);
}

void BagUI::deleteItem(cocos2d::Ref * pSender, ItemInBag * itemIB,cocos2d::Ref * itemPtr)
{
	//������ݲ��ԣ�����
	if (!itemIB->item || !itemIB->num)
	{
		return;
	}
	/*
	���߼�����˵��������ڶ����ݵĲ��������Բ��ǽ������¡�
	����Ӧ�ý���BagManage���������ݵ��޸ġ�
	���Ǵ�Ч����Ч����������������ֱ���޸ģ������˼����������á�
	����ȥҲ�Ƚ�ֱ�ۡ�
	*/
	itemNumReduce(pSender, itemIB, itemPtr);
	popMsgLabel("ɾ���ɹ�");
}

void BagUI::itemNumReduce(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr)
{
	//itemIB->item->~Item();
	if (itemIB->num>0)
		--itemIB->num;
	if (itemIB->num == 0)
	{
		//�ͷŰ�ť����ֹ����
		//clearAllOperationItem();
		//clearSelectedOperationUI();
		hideSelectedOperationUI();//����
		//ɾ������
		delete itemIB->item;
		itemIB->item = NULL;
		//ɾ��ͼ��
		/*
		�����˺ܶ��ַ�ʽ��ֱ�����_menuItem[i][j]��ָ���ַ
		Ҳ����ʹ_menuItem[i][j]=NULL,����һֱ����ʵ�֡�
		ԭ����itemPtr��_menuItem[i][j]ָ��ĵ�ַ��
		������_menuItem[i][j]�������۶�itemPtr��β�����
		�൱��_menuItem[i][j]��ֵ�ı䣬���Ǳ���û��ָ��NULL��
		��Ȼָ��һ����ַ����ʹ�����ַ�Ѿ����ͷš�
		���Ըı���˼·����ȥ�����޸�_menuItem[i][j]=NULL��
		����ֱ�Ӹ�ֵ��Ӧ��ַ�ڴ�ֵΪ0����������������ݵ�ʱ��
		�����жϵ����ݡ�
		*/
		if (!itemPtr)
			return;
		removeBagItemCell((MenuItem*)itemPtr);
	/*	((MenuItem*)itemPtr)->removeFromParent();
		memset(itemPtr, 0, sizeof(MenuItem));*/
	}
}

void BagUI::viewItem(cocos2d::Ref * pSender, ItemInBag * itemIB)
{
	CCLOG("viewItem click!!");
	listItemInfo(itemIB);
}

void BagUI::popMsgLabel(std::string str)
{
	auto msgLabel = LabelTTF::create(
		wstrtoutf8::CreateUTF8(str.c_str()), "����", 24);
	msgLabel->setPosition(Director::getInstance()->getWinSize() / 2);
	this->addChild(msgLabel, UILAYER3th, "msgLabel");

	_msgLabelList.push_back(msgLabel);

	msgLabel->runAction(
		Sequence::create(
			Spawn::create( FadeOut::create(1.5f), 
				MoveBy::create(1.5f, Vec2(0, 50)),NULL)
			//DelayTime::create(1.0f)
			,
			CallFuncN::create(this, callfuncN_selector(BagUI::deleteMsgLabel))
			,
			NULL
		)
	);
}

void BagUI::deleteNode(cocos2d::Node * pSender)
{
	(pSender)->removeFromParentAndCleanup(true);
	
}

void BagUI::deleteMsgLabel(cocos2d::Node * pSender)
{
	//(pSender)->removeFromParentAndCleanup(true);
	auto end= _msgLabelList.end();
	for (vector<LabelTTF*>::iterator i = _msgLabelList.begin();
		i != _msgLabelList.end();)
	{
		if ((*i)==pSender)
		{
			(*i)->removeFromParentAndCleanup(true);
			i=_msgLabelList.erase(i);
		}
		else
		{
			++i;
		}
	}
}

void BagUI::cleanup()
{
	Layer::onExit();
	this->removeMsgLabelList();
	//init();
}

void BagUI::removeMsgLabelList()
{
	for (vector<LabelTTF*>::iterator i = _msgLabelList.begin(); 
		i != _msgLabelList.end(); )
	{
		if (*i)
		{
			(*i)->removeFromParentAndCleanup(true);
			i = _msgLabelList.erase(i);
		}
		else
		{
			++i;
		}
	}
}

bool BagUI::addToCellInBagAndItem(ItemInBag * itemIB)
{
	auto backsize = _bagback->getContentSize();

	float pianyix = backsize.width / 5;
	float pianyiy = backsize.height / 3;

	auto beginposition = ccp(_bagback->getPosition().x
		- backsize.width / 2 + pianyix / 2,
		_bagback->getPosition().y + backsize.height / 2 - pianyiy / 2
	);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			//�����ǰ��������Ϊ��
			if (!_tmpBag[i][j].item||!_tmpBag[i][j].num)
			{
				//��������ӵ���ǰ����
				_tmpBag[i][j].item = itemIB->item;
				_tmpBag[i][j].num = itemIB->num;
				
				//�������е�ͼ����ʾ�ڱ�������
				_imageItem[i][j] = MenuItemImage::create(
					_tmpBag[i][j].item->_itemUrl,
					_tmpBag[i][j].item->_itemUrl,
					CC_CALLBACK_1(BagUI::itemClickLoadBagItemInfo,
						this, &_tmpBag[i][j])
				);
				_imageItem[i][j]->setPosition(
					beginposition.x + j*pianyix
					,
					beginposition.y - i*pianyiy
				);
				_bagIndex->addChild(_imageItem[i][j]);
				
				//return &_tmpBag[i][j];
				return true;
			}
		}
	}
	//ֱ��ѭ��������û���ҵ��ո���
	return false;
}

void BagUI::useItem(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr)
{
	//������ݲ���ȷ������
	if (!itemIB->num||!itemIB->item||!itemPtr)
	{
		return;
	}
	/*
	ʹ����Ʒ��������Ʒ�Ĳ���Ӧ�ý�����������
	�����������Ʒ������ͬʱ����������������
	���������������Խ����޸�
	��Ʒʹ�ý���
	*/
	popMsgLabel(PlayerManage::getInstance()->useItem(_curHero,itemIB->item));
	itemNumReduce(this, itemIB, itemPtr);

	/*���Ͷ�����Ϣ���ص���PlayerStatusUI�����*/
	//���״̬�ı�
	NotificationCenter::getInstance()->postNotification("playerstatuschange",_curHero);
}

void BagUI::equipItem(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr)
{
	try
	{
		
		
		if (!itemIB->item|| !itemPtr->getReferenceCount())
		{
			return;
		}
		//����Ƿ����װ��������������Ƿ��Ѿ�װ������Ʒ���Ͳ�����װ����Ʒ
		if (!BagManage::getInstance()->checkIsCanEquipment(itemIB->item))
		{
			popMsgLabel("�Ѿ�װ����һ����Ʒ");
			return;
		}

		hideSelectedOperationUI();//���ذ�ť

		//װ����Ʒ����������ӵ����� status,herolayer�������ݷ���
		popMsgLabel(PlayerManage::getInstance()->equipItem(_curHero, itemIB->item));
		/*
		1.��bagmanage�޸ı�����װ��ֵ
		2.�ڱ����˵������Ƴ���ť*/
		//��ʵ����ӵ�װ����
		BagManage::getInstance()->insertEquipment(itemIB);
		//��������ֵ�޸�
		/*equipNumReduce(pSender, itemIB, itemPtr);*/
		itemIB->item = NULL;
		itemIB->num = 0;
		removeBagItemCell((MenuItemImage*)itemPtr);
		/*((MenuItemImage*)itemPtr)->removeFromParent();
		memset(itemPtr, 0, sizeof(MenuItemImage));*/

		//�ͷŰ�ť����ֹ����
		/*������һ����ť�����ͷ������ť��
		��ᵼ�°󶨴�������������*/
		//clearAllOperationItem();
		
		/*����װ����ť*/
		clearEquipmentData();
		loadEquipmentData();
	}
	catch (const std::exception& e)
	{
		throw e;
	}
	/*���Ͷ�����Ϣ���ص���PlayerStatusUI�����*/
	//���״̬�ı�
	NotificationCenter::getInstance()->postNotification("playerstatuschange", _curHero);
}

//void BagUI::equipNumReduce(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr)
//{
//	if (itemIB->num>0)
//		--itemIB->num;
//
//	if (itemIB->num == 0)
//	{
//		//��ɾ��ʵ��������ת�Ƶ�BagManageװ������
//		//�����е�ָ��Ϊ�գ���Ϊ�Ѿ���װ��������
//		itemIB->item = NULL;
//		//ɾ��ͼ��
//		/*
//		�����˺ܶ��ַ�ʽ��ֱ�����_menuItem[i][j]��ָ���ַ
//		Ҳ����ʹ_menuItem[i][j]=NULL,����һֱ����ʵ�֡�
//		ԭ����itemPtr��_menuItem[i][j]ָ��ĵ�ַ��
//		������_menuItem[i][j]�������۶�itemPtr��β�����
//		�൱��_menuItem[i][j]��ֵ�ı䣬���Ǳ���û��ָ��NULL��
//		��Ȼָ��һ����ַ����ʹ�����ַ�Ѿ����ͷš�
//		���Ըı���˼·����ȥ�����޸�_menuItem[i][j]=NULL��
//		����ֱ�Ӹ�ֵ��Ӧ��ַ�ڴ�ֵΪ0����������������ݵ�ʱ��
//		�����жϵ����ݡ�
//		*/
//		if (!itemPtr)
//			return;
//		((MenuItem*)itemPtr)->removeFromParent();
//		memset(itemPtr, 0, sizeof(MenuItem));
//	}
//}

void BagUI::unequipItem(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr)
{
	if (!itemIB->item|| !itemPtr->getReferenceCount())
	{
		return;
	}
	//clearSelectedOperationUI();

	//���ذ�ť
	hideSelectedOperationUI();

	//���¸���
	//1.�ҵ��ղ˵����ӣ�������ͼ��
	//2.�ҵ��ձ������ӣ�����������
	//3.����ʧ�ܣ����û�пո���
	if (!addToCellInBagAndItem(itemIB))
	{
		popMsgLabel("��������!");
	}
	//����пո��ӣ�����ִ��
	//�Ƴ�װ��ͼ��
	removeEquipment((MenuItemImage*)itemPtr);
	//_equipMenu->removeChild((MenuItemImage*)itemPtr,true);
	//((MenuItemImage*)itemPtr)->removeFromParent();
	//memset(itemPtr, 0, sizeof(MenuItemImage));
	//��װ��ͼ����ڱ�����
	//*tmpSpriteItemPtr =MenuItemImage::create("UI/bag_one_off.png", "UI/bag_on.png",
	//	CC_CALLBACK_1(BagUI::menuClickLoadBag, this, 1
	//	));
	//_bagIndex->addChild(*tmpSpriteItemPtr);

	//ж����Ʒ�������Դ����� status��ȥ��herolayer���������޸�
	popMsgLabel(PlayerManage::getInstance()->unloadEquipment(_curHero, itemIB->item));
	//ж����Ʒ,��ʵ���ӱ���װ�������Ƴ�
	itemIB->item = NULL;
	itemIB->num = 0;

	//�ͷŰ�ť����ֹ����
	//clearAllOperationItem();

	/*���Ͷ�����Ϣ���ص���PlayerStatusUI�����*/
	//���״̬�ı�
	NotificationCenter::getInstance()->postNotification("playerstatuschange",_curHero);
}

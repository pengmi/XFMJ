#include "BagUI.h"
#include "Item\BagManage.h"
#include "Item\ItemInfoUI.h"

bool BagUI::init()
{
	initMenu();
	setBagBack();
	setEquipBack();

	memset(_imageItem, NULL, sizeof(_imageItem));

	loadBagData(1);//初始化背包
	setCurHero(PlayerManage::getInstance()->
		_huangZaiLayer);
	menuClickLoadData(this,_curHero);//初始化装备栏，黄载装备

	return true;
}

void BagUI::setBagBack()
{
	_bagback = Sprite::create("UI/bagback.png");
	this->addChild(_bagback);
	_bagback->setPosition(Director::getInstance()->
		getWinSize().width/2,
		Director::getInstance()->getWinSize().height /2-20);
	/*背包金钱数量label*/
	_money = Label::create(std::string(wstrtoutf8::CreateUTF8("金钱:")
		+HelpTool::int2str(
			BagManage::getInstance()->getMoney())), "隶书", 20);;
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
	_selectedMenu = Menu::create(NULL);//选择物品时的菜单容器
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

	_equipMenu = Menu::create(NULL);//装备的菜单容器
	_equipMenu->setPosition(Vec2::ZERO);
	this->addChild(_equipMenu);
}

void BagUI::removeItemCells()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			//直接用数量0判断也不好，因为背包有两个，
			//不好判断到底是哪一个。直接用引用量判断就好
			//注意_imageItem[i][j]对应的地址要被memset为0才可以这么用
			if (_imageItem[i][j])
			{
				_bagIndex->removeChild(_imageItem[i][j],true);
				_imageItem[i][j] = NULL;
			}
			else
			{
				/*
				ReferenceCount=0,
				表明这个对象指向的内存地址已经被释放。
				不能再释放了。
				直接赋值为NULL即可。
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
			//如果格子有东西且数量不为0
			if (_tmpBag[i][j].item&&
				_tmpBag[i][j].num)
			{
				//将格子中的图标显示在背包框中
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
			//如果格子有东西但数量为0
			else if (_tmpBag[i][j].item &&
				!_tmpBag[i][j].num)
			{
				delete _tmpBag[i][j].item;
			}
			//如果格子没有东西但数量不为0
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
			//	_selectedMenu->addChild(_useItem);//验证代码，资源确实释放，这句就报错
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
		可以用数量0判断，也可以用引用量0判断
		因为只有一个装备栏
		就是bagmanage里面的equipment[i]->num
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
	//找到菜单项，移除
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
	//this->removeAllChildren();//先清除所有的子节点，然后重新加载
	//initBackground();
	//将点击的英雄作为临时对象
	this->setCurHero(s);
	//将人物的装备放在bagmanagement里面，以便使用
	BagManage::getInstance()->loadPlayerEquipmentData(s);
	clearEquipmentData();//清除装备数据
	loadEquipmentData();//传入装备数据
}

void BagUI::itemClickLoadBagItemInfo(cocos2d::Ref * pSender, 
	ItemInBag * itemIB)
{
	CCLOG("Item click!!");
	//点击物品以后
	clearSelectedOperationUI();
	listItemInfo(itemIB);//列出物品信息
	setSelectedOperationUI(pSender,itemIB);//列出操作UI
}

void BagUI::itemClickLoadEquipmentInfo(cocos2d::Ref * pSender, 
	ItemInBag* itemIB)
{
	CCLOG("Equipment click!!");
	//点击物品以后
	clearSelectedOperationUI();
	listItemInfo(itemIB);//列出物品信息
	setEquipmentOperationUI(pSender, itemIB);//列出操作UI
}

void BagUI::itemClickShowInfo(cocos2d::Ref * pSender, ItemInBag * itemIB)
{
	CCLOG("itemClickShowInfo!!");
	listItemInfo(itemIB);
}

void BagUI::deleteItem(cocos2d::Ref * pSender, ItemInBag * itemIB,cocos2d::Ref * itemPtr)
{
	//如果数据不对，返回
	if (!itemIB->item || !itemIB->num)
	{
		return;
	}
	/*
	从逻辑上来说，这里存在对数据的操作，所以不是界面层的事。
	这里应该交给BagManage来进行数据的修改。
	但是从效果和效率上来讲，在这里直接修改，减少了几个函数调用。
	看上去也比较直观。
	*/
	itemNumReduce(pSender, itemIB, itemPtr);
	popMsgLabel("删除成功");
}

void BagUI::itemNumReduce(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr)
{
	//itemIB->item->~Item();
	if (itemIB->num>0)
		--itemIB->num;
	if (itemIB->num == 0)
	{
		//释放按钮，防止出错
		//clearAllOperationItem();
		//clearSelectedOperationUI();
		hideSelectedOperationUI();//隐藏
		//删除数据
		delete itemIB->item;
		itemIB->item = NULL;
		//删除图标
		/*
		尝试了很多种方式来直接清除_menuItem[i][j]的指向地址
		也就是使_menuItem[i][j]=NULL,但是一直不能实现。
		原因是itemPtr是_menuItem[i][j]指向的地址，
		但不是_menuItem[i][j]本身，无论对itemPtr如何操作，
		相当于_menuItem[i][j]的值改变，但是本身没有指向NULL，
		仍然指向一个地址，即使这个地址已经被释放。
		所以改变了思路，不去尝试修改_menuItem[i][j]=NULL，
		而是直接赋值对应地址内存值为0，这样，在清除数据的时候，
		就有判断的依据。
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
		wstrtoutf8::CreateUTF8(str.c_str()), "隶书", 24);
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
			//如果当前背包格子为空
			if (!_tmpBag[i][j].item||!_tmpBag[i][j].num)
			{
				//将数据添加到当前背包
				_tmpBag[i][j].item = itemIB->item;
				_tmpBag[i][j].num = itemIB->num;
				
				//将格子中的图标显示在背包框中
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
	//直到循环结束，没有找到空格子
	return false;
}

void BagUI::useItem(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr)
{
	//如果数据不正确，返回
	if (!itemIB->num||!itemIB->item||!itemPtr)
	{
		return;
	}
	/*
	使用物品，对于物品的操作应该交给背包管理。
	背包管理对物品操作，同时将结果交给人物管理，
	人物管理对人物属性进行修改
	物品使用结束
	*/
	popMsgLabel(PlayerManage::getInstance()->useItem(_curHero,itemIB->item));
	itemNumReduce(this, itemIB, itemPtr);

	/*发送订阅消息，回调在PlayerStatusUI上完成*/
	//玩家状态改变
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
		//检查是否可以装备，如果格子上是否已经装备了物品，就不能再装备物品
		if (!BagManage::getInstance()->checkIsCanEquipment(itemIB->item))
		{
			popMsgLabel("已经装备了一件物品");
			return;
		}

		hideSelectedOperationUI();//隐藏按钮

		//装备物品，将属性添加到人物 status,herolayer处将数据放入
		popMsgLabel(PlayerManage::getInstance()->equipItem(_curHero, itemIB->item));
		/*
		1.在bagmanage修改背包和装备值
		2.在背包菜单项中移除按钮*/
		//将实例添加到装备栏
		BagManage::getInstance()->insertEquipment(itemIB);
		//背包数据值修改
		/*equipNumReduce(pSender, itemIB, itemPtr);*/
		itemIB->item = NULL;
		itemIB->num = 0;
		removeBagItemCell((MenuItemImage*)itemPtr);
		/*((MenuItemImage*)itemPtr)->removeFromParent();
		memset(itemPtr, 0, sizeof(MenuItemImage));*/

		//释放按钮，防止出错
		/*不能在一个按钮里面释放这个按钮，
		这会导致绑定错误，引起程序崩溃*/
		//clearAllOperationItem();
		
		/*加载装备按钮*/
		clearEquipmentData();
		loadEquipmentData();
	}
	catch (const std::exception& e)
	{
		throw e;
	}
	/*发送订阅消息，回调在PlayerStatusUI上完成*/
	//玩家状态改变
	NotificationCenter::getInstance()->postNotification("playerstatuschange", _curHero);
}

//void BagUI::equipNumReduce(cocos2d::Ref * pSender, ItemInBag * itemIB, cocos2d::Ref * itemPtr)
//{
//	if (itemIB->num>0)
//		--itemIB->num;
//
//	if (itemIB->num == 0)
//	{
//		//不删除实例，而是转移到BagManage装备栏中
//		//背包中的指针为空，因为已经到装备栏中了
//		itemIB->item = NULL;
//		//删除图标
//		/*
//		尝试了很多种方式来直接清除_menuItem[i][j]的指向地址
//		也就是使_menuItem[i][j]=NULL,但是一直不能实现。
//		原因是itemPtr是_menuItem[i][j]指向的地址，
//		但不是_menuItem[i][j]本身，无论对itemPtr如何操作，
//		相当于_menuItem[i][j]的值改变，但是本身没有指向NULL，
//		仍然指向一个地址，即使这个地址已经被释放。
//		所以改变了思路，不去尝试修改_menuItem[i][j]=NULL，
//		而是直接赋值对应地址内存值为0，这样，在清除数据的时候，
//		就有判断的依据。
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

	//隐藏按钮
	hideSelectedOperationUI();

	//更新格子
	//1.找到空菜单格子，并插入图标
	//2.找到空背包格子，并插入数据
	//3.插入失败，如果没有空格子
	if (!addToCellInBagAndItem(itemIB))
	{
		popMsgLabel("背包已满!");
	}
	//如果有空格子，正常执行
	//移除装备图标
	removeEquipment((MenuItemImage*)itemPtr);
	//_equipMenu->removeChild((MenuItemImage*)itemPtr,true);
	//((MenuItemImage*)itemPtr)->removeFromParent();
	//memset(itemPtr, 0, sizeof(MenuItemImage));
	//将装备图标放在背包里
	//*tmpSpriteItemPtr =MenuItemImage::create("UI/bag_one_off.png", "UI/bag_on.png",
	//	CC_CALLBACK_1(BagUI::menuClickLoadBag, this, 1
	//	));
	//_bagIndex->addChild(*tmpSpriteItemPtr);

	//卸载物品，将属性从人物 status减去，herolayer处将数据修改
	popMsgLabel(PlayerManage::getInstance()->unloadEquipment(_curHero, itemIB->item));
	//卸载物品,将实例从背包装备栏中移除
	itemIB->item = NULL;
	itemIB->num = 0;

	//释放按钮，防止出错
	//clearAllOperationItem();

	/*发送订阅消息，回调在PlayerStatusUI上完成*/
	//玩家状态改变
	NotificationCenter::getInstance()->postNotification("playerstatuschange",_curHero);
}

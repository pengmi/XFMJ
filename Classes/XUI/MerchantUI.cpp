#include "MerchantUI.h"
#include "tool\HelpTool.h"
#include "tool\WStrToUTF8.h"
#include "Item\ItemInfoUI.h"
#include "XData\Global.h"
#include "Item\GoodsManage.h"
#include "Item\BagManage.h"

MerchantUI * MerchantUI::create()
{
	MerchantUI *pRet = new MerchantUI;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else {
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

bool MerchantUI::init()
{
	setBackGround();
	initMenu();
	initData();
	initTouch();
	return true;
}

void MerchantUI::initData()
{
	_itemNum=1;
	_operateType=0;
	setGoodsMenuUI();
}

void MerchantUI::setBackGround()
{
	auto winsize = Director::getInstance()->
		getWinSize();

	auto bagback = Sprite::create("UI/merchantback.png");
	this->addChild(bagback);
	bagback->setPosition(winsize.width / 2,
		winsize.height / 2);

	_bagback1 = Sprite::create("UI/merchant.png");
	this->addChild(_bagback1);
	_bagback1->setPosition(winsize.width/2-_bagback1->getContentSize().width/ 2,
		winsize.height- _bagback1->getContentSize().height/2);
	
	_bagback2 = Sprite::create("UI/merchant.png");
	this->addChild(_bagback2);
	_bagback2->setPosition(winsize.width / 2+_bagback2->getContentSize().width / 2,
		winsize.height - _bagback1->getContentSize().height/2);
	
	
}

void MerchantUI::initMenu()
{
	auto winsize = Director::getInstance()->
		getWinSize();

	//数量指示标签
	_moneyLabel = Label::create(wstrtoutf8::CreateUTF8("金钱:")+
		HelpTool::int2str(BagManage::getInstance()->getMoney()), 
		"隶书", 25);
	_moneyLabel->setColor(ccc3(255,255,0));
	_moneyLabel->setPosition(_moneyLabel->getContentSize().width,
		_bagback2->getPosition().y - _bagback2->getContentSize().height / 2 - 25);
	this->addChild(_moneyLabel);

	///////////////////////////////////////////////////////////
	//切换到商品按钮
	_goodsItem = MenuItemImage::create("UI/buy_off.png", "UI/buy_on.png",
		CC_CALLBACK_1(MerchantUI::menuClickLoadGoods, this
		));
	_goodsItem->setPosition(winsize.width / 2 - _goodsItem->getContentSize().width - 50,
		_bagback2->getPosition().y - _bagback2->getContentSize().height / 2 - 60);

	//切换到背包按钮
	_bagItem = MenuItemImage::create("UI/sell_off.png", "UI/sell_on.png",
		CC_CALLBACK_1(MerchantUI::menuClickLoadBag, this,false
		));
	_bagItem->setPosition(winsize.width / 2,
		_bagback2->getPosition().y - _bagback2->getContentSize().height / 2 - 60);

	//退出商店按钮
	_closeItem = MenuItemImage::create("UI/exit_off.png", "UI/exit_on.png",
		CC_CALLBACK_1(MerchantUI::menuClickClose, this
		));
	_closeItem->setPosition(winsize.width / 2 + _closeItem->getContentSize().width + 50,
		_bagback2->getPosition().y - _bagback2->getContentSize().height / 2 - 60);

	//将以上三个按钮添加到菜单中生效
	_itemsMenu = Menu::create(_closeItem, _goodsItem, _bagItem,NULL);
	this->addChild(_itemsMenu);
	_itemsMenu->setPosition(Size::ZERO);

	///////////////////////////////////////////////////////////////

	//选择物品时的菜单容器
	_selectedMenu = Menu::create(NULL);
	this->addChild(_selectedMenu);
	_selectedMenu->setPosition(Size::ZERO);
}

void MerchantUI::initTouch()
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MerchantUI::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MerchantUI::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MerchantUI::onTouchEnded, this);
	//listener->onTouchCancelled = CC_CALLBACK_2(FirstScene::keyBackClicked,this);
	listener->setSwallowTouches(true);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->setTouchEnabled(true);
}

void MerchantUI::menuClickLoadGoods(cocos2d::Ref * pSender)
{
	//如果已经是商品界面,直接返回
	if (_operateType == 0)
	{
		return;
	}

	//初始化
	_operateType = 0;
	_itemNum = 1;

	//先清空所有UI
	clearGoodsMenuUI();
	clearOperateUI();
	//加载商品MenuItem
	setGoodsMenuUI();
	refreshMoneyLabel();
}

void MerchantUI::setGoodsMenuUI()
{
	auto goodsinstancelist = GoodsManage::getInstance()->getGoodsInstanceList();

	auto back1pos = _bagback1->getPosition();
	auto back2pos = _bagback2->getPosition();
	auto back1size = _bagback1->getContentSize();
	auto back2size = _bagback2->getContentSize();

	auto back1pianyix = back1size.width / 5;
	auto back1pianyiy = back1size.height / 3;
	auto back2pianyix = back2size.width / 5;
	auto back2pianyiy = back2size.height / 3;

	auto back1beginpos = Point(back1pos.x - back1size.width / 2+ back1pianyix/2,
		back1pos.y+ back1size.height/2- back1pianyiy/2);
	auto back2beginpos = Point(back2pos.x - back2size.width / 2+ back2pianyix/2,
		back2pos.y + back2size.height / 2+ back2pianyiy/2);

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			//if (((*goodsinstancelist)[i * 5 + j]) != NULL)
			if ((goodsinstancelist->size()>(i * 5 + j+1)))
			{
				
				_imageItemLeft[i][j]= MenuItemImage::create(
					((*goodsinstancelist)[i * 5 + j])->_itemUrl,
					((*goodsinstancelist)[i * 5 + j])->_itemUrl,
					CC_CALLBACK_1(MerchantUI::itemClickLoadOperateUI,
						this, ((*goodsinstancelist)[i * 5 + j]),0)
				);
				_imageItemLeft[i][j]->setPosition(
					back1beginpos.x + j*back1pianyix
					,
					back1beginpos.y - i*back1pianyiy
				);
				_itemsMenu->addChild(_imageItemLeft[i][j]);
			}
			else
			{
				return;
			}
		}
	}

	if (goodsinstancelist->size()>15)
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				//if (((*goodsinstancelist)[15+i * 5 + j]) != NULL)
				if ((goodsinstancelist->size()>(15+i * 5 + j + 1)))
				{
					_imageItemRight[i][j] = MenuItemImage::create(
						((*goodsinstancelist)[15 + i * 5 + j])->_itemUrl,
						((*goodsinstancelist)[15 + i * 5 + j])->_itemUrl,
						CC_CALLBACK_1(MerchantUI::itemClickLoadOperateUI,
							this, ((*goodsinstancelist)[15 + i * 5 + j]),0)
					);
					_imageItemRight[i][j]->setPosition(
						back2beginpos.x + j*back2pianyix
						,
						back2beginpos.y - i*back2pianyiy
					);
					_itemsMenu->addChild(_imageItemRight[i][j]);
				}
				else
				{
					return;
				}
			}
		}
	}
	else
	{
		return;
	}

}

void MerchantUI::menuClickLoadBag(cocos2d::Ref * pSender, bool option)
{
	//表示出售

	//如果已经是背包界面,且不进行强制刷新,不做任何操作,直接返回
	if (_operateType == 1&&!option)
	{
		return;
	}

	clearOperateUI();
	clearGoodsMenuUI();
	//初始化
	_operateType = 1;
	_itemNum = 1;
	setBagMenuUI();
	refreshMoneyLabel();
}

void MerchantUI::setBagMenuUI()
{
	ItemInBag(*bagonedata)[5]; bagonedata = &(BagManage::getInstance()->BagOne[0]);
	ItemInBag(*bagtwodata)[5]; bagtwodata = &(BagManage::getInstance()->BagTwo[0]);
	//const auto bagonedata = &(BagManage::getInstance()->BagOne);
	//const auto bagtwodata = &(BagManage::getInstance()->BagTwo);

	auto back1pos = _bagback1->getPosition();
	auto back2pos = _bagback2->getPosition();
	auto back1size = _bagback1->getContentSize();
	auto back2size = _bagback2->getContentSize();

	auto back1pianyix = back1size.width / 5;
	auto back1pianyiy = back1size.height / 3;
	auto back2pianyix = back2size.width / 5;
	auto back2pianyiy = back2size.height / 3;

	auto back1beginpos = Point(back1pos.x - back1size.width / 2 + back1pianyix / 2,
		back1pos.y + back1size.height / 2 - back1pianyiy / 2);
	auto back2beginpos = Point(back2pos.x - back2size.width / 2 + back2pianyix / 2,
		back2pos.y + back2size.height / 2 - back2pianyiy / 2);

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			//if (((*goodsinstancelist)[i * 5 + j]) != NULL)
			if (bagonedata[i][j].item&&(bagonedata[i][j].num))
			{
				//bagonedata[i][j]数据错误 WHy?
				_imageItemLeft[i][j] = MenuItemImage::create(
					bagonedata[i][j].item->_itemUrl,
					bagonedata[i][j].item->_itemUrl,
					CC_CALLBACK_1(MerchantUI::itemClickLoadOperateUI,
						this, bagonedata[i][j].item, bagonedata[i][j].num)
				);
				_imageItemLeft[i][j]->setPosition(
					back1beginpos.x + j*back1pianyix
					,
					back1beginpos.y - i*back1pianyiy
				);
				_itemsMenu->addChild(_imageItemLeft[i][j]);
			}
		}
	}
	
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{

			if (bagtwodata[i][j].item && (bagtwodata[i][j].num))
			{
				_imageItemRight[i][j] = MenuItemImage::create(
					bagtwodata[i][j].item->_itemUrl,
					bagtwodata[i][j].item->_itemUrl,
					CC_CALLBACK_1(MerchantUI::itemClickLoadOperateUI,
						this, bagtwodata[i][j].item, bagtwodata[i][j].num)
				);
				_imageItemRight[i][j]->setPosition(
					back2beginpos.x + j*back2pianyix
					,
					back2beginpos.y - i*back2pianyiy
				);
				_itemsMenu->addChild(_imageItemRight[i][j]);
			}
		}
	}
}

void MerchantUI::clearGoodsMenuUI()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (_imageItemLeft[i][j])
			{
				_imageItemLeft[i][j]->removeFromParentAndCleanup(true);
				_imageItemLeft[i][j] = NULL;
			}
			if (_imageItemRight[i][j])
			{
				_imageItemRight[i][j]->removeFromParentAndCleanup(true);
				_imageItemRight[i][j] = NULL;
			}
		}
	}
}

void MerchantUI::menuClickClose(cocos2d::Ref * pSender)
{
	this->removeFromParentAndCleanup(true);
}


void MerchantUI::popMsgLabel(std::string str)
{
	if (str == "")
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

void MerchantUI::listItemInfo(cocos2d::Ref * pSender, Item * item, int num)
{
	if (!item)
	{
		return;
	}
	auto itemInfoUI = ItemInfoUI::create();
	this->addChild(itemInfoUI, UILAYER3th);
	itemInfoUI->setPosition(Director::getInstance()->getWinSize() / 2);
	itemInfoUI->listItemInfo(item,num);
}

void MerchantUI::itemClickLoadOperateUI(cocos2d::Ref * pSender, Item * item, int num)
{
	visiableOperateUI();
	listItemInfo(this,item,num);
	//先清除UI
	clearOperateUI();

	auto winsize = Director::getInstance()->
		getWinSize();


	//数量减按钮
	_subNumItem = MenuItemImage::create("UI/sub_off.png", "UI/sub_on.png",
		CC_CALLBACK_1(MerchantUI::menuClickSubOperateNum, this
		));
	_subNumItem->setPosition(winsize.width / 2 - _subNumItem->getContentSize().width - 30,
		_closeItem->getPosition().y - _closeItem->getContentSize().height / 2 - 30);
	
	//数量指示标签
	_numLabel= Label::create(HelpTool::int2str(_itemNum), "隶书", 25);
	_numLabel->setPosition(winsize.width / 2 ,
		_closeItem->getPosition().y - _numLabel->getContentSize().height / 2 - 30);
	this->addChild(_numLabel);
	//数量加按钮
	_addNumItem = MenuItemImage::create("UI/add_off.png", "UI/add_on.png",
		CC_CALLBACK_1(MerchantUI::menuClickAddOperateNum, this, num
		));
	_addNumItem->setPosition(winsize.width / 2 + _addNumItem->getContentSize().width + 30,
		_closeItem->getPosition().y - _closeItem->getContentSize().height / 2 - 30);
	
	//如果是购买就加载确认购买按钮
	if (0== _operateType)
	{
		//购买按钮
		_confirmBuyItem = MenuItemImage::create("UI/confirm_buy_off.png",
			"UI/confirm_buy_on.png",
			CC_CALLBACK_1(MerchantUI::menuClickConfirmBuy, this, item->_itemId
			));
		_confirmBuyItem->setPosition(winsize.width / 2,
			_addNumItem->getPosition().y - _addNumItem->getContentSize().height / 2 - 30);
	

		_selectedMenu->addChild(_confirmBuyItem);
		//_selectedMenu->addChild(_confirmSellItem);
		_selectedMenu->addChild(_subNumItem);
		_selectedMenu->addChild(_addNumItem);
	}
	else	//否则就加载确认出售按钮
	{
		//出售按钮
		_confirmSellItem = MenuItemImage::create("UI/confirm_sell_off.png",
			"UI/confirm_sell_on.png",
			CC_CALLBACK_1(MerchantUI::menuClickConfirmSell, this, item
			));
		_confirmSellItem->setPosition(winsize.width / 2,
			_addNumItem->getPosition().y - _addNumItem->getContentSize().height / 2 - 30);


		//_selectedMenu->addChild(_confirmBuyItem);
		_selectedMenu->addChild(_confirmSellItem);
		_selectedMenu->addChild(_subNumItem);
		_selectedMenu->addChild(_addNumItem);
	}
}

void MerchantUI::clearOperateUI()
{
	if (_selectedMenu)
	{
		if (_selectedMenu->getChildrenCount())
		{
			_selectedMenu->removeAllChildren();
		}
	}
	_itemNum = 1;
	if (_numLabel)
	{
		_numLabel->removeFromParentAndCleanup(true);
		_numLabel = NULL;
	}

}

void MerchantUI::hideOperateUI()
{
	if (_selectedMenu)
	{
		if (_selectedMenu->getChildrenCount())
		{
			_selectedMenu->setVisible(false);
		}
	}
	_itemNum = 1;
	if (_numLabel)
	{
		_numLabel->removeFromParentAndCleanup(true);
		_numLabel = NULL;
	}
}

void MerchantUI::visiableOperateUI()
{
	if (_selectedMenu)
	{
		_selectedMenu->setVisible(true);
	}
}

void MerchantUI::menuClickConfirmBuy(cocos2d::Ref * pSender, int itemid)
{
	//如果id为0，根本没有这种物品
	if (!itemid)
	{
		popMsgLabel("无效物品!");
		return;
	}

	auto bagmanage= BagManage::getInstance();

	//如果格子不够
	if (!bagmanage->getEmptyCellsNum())
	{
		popMsgLabel("背包空间不足,无法购买!");
		return;
	};
	//如果能在商品列表中找到物品
	int totalprice=0;
	if (auto tmpitem = GoodsManage::getInstance()
		->getItemFromGoodsInstanceList(itemid))
	{
		totalprice = (tmpitem->_price*_itemNum);
		//如果金钱不够，无法继续操作，直接返回
		if (totalprice>bagmanage->getMoney())
		{
			popMsgLabel("金钱不足,无法购买!");
			return;
		}
	}
	else
	{
		//如果在商品列表中找不到此物品
		//一般不会发生这种情况，如果发生，说明出现了BUG
		popMsgLabel("商人不打算出售此物品!");
		return;
	}

	//购买时
	bagmanage->insertItemToBag(itemid,_itemNum);
	bagmanage->subMoney(totalprice);

	_moneyLabel->setString(wstrtoutf8::CreateUTF8("金钱:") + 
		HelpTool::int2str(bagmanage->getMoney()));

	popMsgLabel("购买成功!");
	CCLOG("confirm buy");
	//最后，重置物品数量
	_itemNum = 1;
	refreshNumLabel();
	refreshMoneyLabel();
}

void MerchantUI::menuClickConfirmSell(cocos2d::Ref * pSender, Item *item)
{
	if (!item->_itemId)
	{
		popMsgLabel("无效物品");
		return;
	}

	CCLOG("confirm sell");

	if (item)
	{
		auto bagmanage = BagManage::getInstance();
		//bagmanage->deleteItemFromBag(itemid,_itemNum);
		//减少背包东西数量
		auto price = item->_price;
		auto isthelastone = bagmanage->
			deleteItemFromBag(item, _itemNum);
		if (isthelastone)
		{
			//计算得到金钱
			bagmanage->addMoney(price*_itemNum);
			
			popMsgLabel("出售成功");
		}
		else if (0==isthelastone)
		{
			//最后一个物品了，不能再进行售卖
			//计算得到金钱
			bagmanage->addMoney(price*_itemNum);
			popMsgLabel("出售成功");
			hideOperateUI();
		}
		else
		{
			hideOperateUI();
		}
		
		
		//重新加载
		//clearOperateUI();

		clearGoodsMenuUI();
		////初始化
		//_operateType = 1;
		//_itemNum = 1;
		setBagMenuUI();

		//menuClickLoadBag(this,true);
		
	}
	else
	{
		popMsgLabel("商人不喜欢这件物品!");
	}

	//最后，重置物品数量
	_itemNum = 1;
	refreshNumLabel();
	refreshMoneyLabel();
}

void MerchantUI::menuClickAddOperateNum(cocos2d::Ref * pSender, int numInBag)
{ 
	

	//出售时，不能出售超过背包已有数量
	if (1==_operateType)
	{
		if (numInBag== _itemNum)
		{
			return;
		}
	}

	//不能比99高
	if (99==_itemNum)
	{
		return;
	}
	++_itemNum;
	//重设数量标签
	refreshNumLabel();
	//_numLabel->setString(HelpTool::int2str(_itemNum));
	//refreshMoneyLabel();
}

void MerchantUI::menuClickSubOperateNum(cocos2d::Ref * pSender)
{
	//不能比1低
	if (1==_itemNum)
	{
		return;
	}
	--_itemNum;
	//重设数量标签
	refreshNumLabel();
	//_numLabel->setString(HelpTool::int2str(_itemNum));
	//refreshMoneyLabel();
}

void MerchantUI::refreshNumLabel()
{
	if (!_numLabel)
	{
		return;
	}
	_numLabel->setString(HelpTool::int2str(_itemNum));
}

void MerchantUI::refreshMoneyLabel()
{
	if (!_moneyLabel)
	{
		return;
	}
	_moneyLabel->setString(HelpTool::int2str(BagManage::getInstance()->getMoney()));
}

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

	//����ָʾ��ǩ
	_moneyLabel = Label::create(wstrtoutf8::CreateUTF8("��Ǯ:")+
		HelpTool::int2str(BagManage::getInstance()->getMoney()), 
		"����", 25);
	_moneyLabel->setColor(ccc3(255,255,0));
	_moneyLabel->setPosition(_moneyLabel->getContentSize().width,
		_bagback2->getPosition().y - _bagback2->getContentSize().height / 2 - 25);
	this->addChild(_moneyLabel);

	///////////////////////////////////////////////////////////
	//�л�����Ʒ��ť
	_goodsItem = MenuItemImage::create("UI/buy_off.png", "UI/buy_on.png",
		CC_CALLBACK_1(MerchantUI::menuClickLoadGoods, this
		));
	_goodsItem->setPosition(winsize.width / 2 - _goodsItem->getContentSize().width - 50,
		_bagback2->getPosition().y - _bagback2->getContentSize().height / 2 - 60);

	//�л���������ť
	_bagItem = MenuItemImage::create("UI/sell_off.png", "UI/sell_on.png",
		CC_CALLBACK_1(MerchantUI::menuClickLoadBag, this,false
		));
	_bagItem->setPosition(winsize.width / 2,
		_bagback2->getPosition().y - _bagback2->getContentSize().height / 2 - 60);

	//�˳��̵갴ť
	_closeItem = MenuItemImage::create("UI/exit_off.png", "UI/exit_on.png",
		CC_CALLBACK_1(MerchantUI::menuClickClose, this
		));
	_closeItem->setPosition(winsize.width / 2 + _closeItem->getContentSize().width + 50,
		_bagback2->getPosition().y - _bagback2->getContentSize().height / 2 - 60);

	//������������ť��ӵ��˵�����Ч
	_itemsMenu = Menu::create(_closeItem, _goodsItem, _bagItem,NULL);
	this->addChild(_itemsMenu);
	_itemsMenu->setPosition(Size::ZERO);

	///////////////////////////////////////////////////////////////

	//ѡ����Ʒʱ�Ĳ˵�����
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
	//����Ѿ�����Ʒ����,ֱ�ӷ���
	if (_operateType == 0)
	{
		return;
	}

	//��ʼ��
	_operateType = 0;
	_itemNum = 1;

	//���������UI
	clearGoodsMenuUI();
	clearOperateUI();
	//������ƷMenuItem
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
	//��ʾ����

	//����Ѿ��Ǳ�������,�Ҳ�����ǿ��ˢ��,�����κβ���,ֱ�ӷ���
	if (_operateType == 1&&!option)
	{
		return;
	}

	clearOperateUI();
	clearGoodsMenuUI();
	//��ʼ��
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
				//bagonedata[i][j]���ݴ��� WHy?
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
	//�����UI
	clearOperateUI();

	auto winsize = Director::getInstance()->
		getWinSize();


	//��������ť
	_subNumItem = MenuItemImage::create("UI/sub_off.png", "UI/sub_on.png",
		CC_CALLBACK_1(MerchantUI::menuClickSubOperateNum, this
		));
	_subNumItem->setPosition(winsize.width / 2 - _subNumItem->getContentSize().width - 30,
		_closeItem->getPosition().y - _closeItem->getContentSize().height / 2 - 30);
	
	//����ָʾ��ǩ
	_numLabel= Label::create(HelpTool::int2str(_itemNum), "����", 25);
	_numLabel->setPosition(winsize.width / 2 ,
		_closeItem->getPosition().y - _numLabel->getContentSize().height / 2 - 30);
	this->addChild(_numLabel);
	//�����Ӱ�ť
	_addNumItem = MenuItemImage::create("UI/add_off.png", "UI/add_on.png",
		CC_CALLBACK_1(MerchantUI::menuClickAddOperateNum, this, num
		));
	_addNumItem->setPosition(winsize.width / 2 + _addNumItem->getContentSize().width + 30,
		_closeItem->getPosition().y - _closeItem->getContentSize().height / 2 - 30);
	
	//����ǹ���ͼ���ȷ�Ϲ���ť
	if (0== _operateType)
	{
		//����ť
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
	else	//����ͼ���ȷ�ϳ��۰�ť
	{
		//���۰�ť
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
	//���idΪ0������û��������Ʒ
	if (!itemid)
	{
		popMsgLabel("��Ч��Ʒ!");
		return;
	}

	auto bagmanage= BagManage::getInstance();

	//������Ӳ���
	if (!bagmanage->getEmptyCellsNum())
	{
		popMsgLabel("�����ռ䲻��,�޷�����!");
		return;
	};
	//���������Ʒ�б����ҵ���Ʒ
	int totalprice=0;
	if (auto tmpitem = GoodsManage::getInstance()
		->getItemFromGoodsInstanceList(itemid))
	{
		totalprice = (tmpitem->_price*_itemNum);
		//�����Ǯ�������޷�����������ֱ�ӷ���
		if (totalprice>bagmanage->getMoney())
		{
			popMsgLabel("��Ǯ����,�޷�����!");
			return;
		}
	}
	else
	{
		//�������Ʒ�б����Ҳ�������Ʒ
		//һ�㲻�ᷢ��������������������˵��������BUG
		popMsgLabel("���˲�������۴���Ʒ!");
		return;
	}

	//����ʱ
	bagmanage->insertItemToBag(itemid,_itemNum);
	bagmanage->subMoney(totalprice);

	_moneyLabel->setString(wstrtoutf8::CreateUTF8("��Ǯ:") + 
		HelpTool::int2str(bagmanage->getMoney()));

	popMsgLabel("����ɹ�!");
	CCLOG("confirm buy");
	//���������Ʒ����
	_itemNum = 1;
	refreshNumLabel();
	refreshMoneyLabel();
}

void MerchantUI::menuClickConfirmSell(cocos2d::Ref * pSender, Item *item)
{
	if (!item->_itemId)
	{
		popMsgLabel("��Ч��Ʒ");
		return;
	}

	CCLOG("confirm sell");

	if (item)
	{
		auto bagmanage = BagManage::getInstance();
		//bagmanage->deleteItemFromBag(itemid,_itemNum);
		//���ٱ�����������
		auto price = item->_price;
		auto isthelastone = bagmanage->
			deleteItemFromBag(item, _itemNum);
		if (isthelastone)
		{
			//����õ���Ǯ
			bagmanage->addMoney(price*_itemNum);
			
			popMsgLabel("���۳ɹ�");
		}
		else if (0==isthelastone)
		{
			//���һ����Ʒ�ˣ������ٽ�������
			//����õ���Ǯ
			bagmanage->addMoney(price*_itemNum);
			popMsgLabel("���۳ɹ�");
			hideOperateUI();
		}
		else
		{
			hideOperateUI();
		}
		
		
		//���¼���
		//clearOperateUI();

		clearGoodsMenuUI();
		////��ʼ��
		//_operateType = 1;
		//_itemNum = 1;
		setBagMenuUI();

		//menuClickLoadBag(this,true);
		
	}
	else
	{
		popMsgLabel("���˲�ϲ�������Ʒ!");
	}

	//���������Ʒ����
	_itemNum = 1;
	refreshNumLabel();
	refreshMoneyLabel();
}

void MerchantUI::menuClickAddOperateNum(cocos2d::Ref * pSender, int numInBag)
{ 
	

	//����ʱ�����ܳ��۳���������������
	if (1==_operateType)
	{
		if (numInBag== _itemNum)
		{
			return;
		}
	}

	//���ܱ�99��
	if (99==_itemNum)
	{
		return;
	}
	++_itemNum;
	//����������ǩ
	refreshNumLabel();
	//_numLabel->setString(HelpTool::int2str(_itemNum));
	//refreshMoneyLabel();
}

void MerchantUI::menuClickSubOperateNum(cocos2d::Ref * pSender)
{
	//���ܱ�1��
	if (1==_itemNum)
	{
		return;
	}
	--_itemNum;
	//����������ǩ
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

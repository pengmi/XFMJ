#include "GoodsManage.h"
#include <cocos2d.h>
#include "Gut\NPC.h"

#include "XData\DataModel.h"

GoodsManage* GoodsManage::_instance = NULL;

GoodsManage * GoodsManage::getInstance()
{
	if (NULL == _instance)
	{
		_instance = new GoodsManage();
	}
	return _instance;
}

GoodsManage::~GoodsManage()
{
	deleteGoodsInstanceList();
	delete _instance;
}


vector<class Item*>* GoodsManage::getGoodsInstanceList(NPC* merchant)
{
	//如果merchant不存在，即为直接想要获取当前商品列表
	if (!merchant)
	{
		return &_goodsInstanceList;
	}
	//判断是否是商人的商品是否已经加载
	//防止多余读取文件的动作
	if (_tempMerchantId==merchant->_NPCID&&_goodsInstanceList.size())
	{
		return &_goodsInstanceList;
	}
	//如果商人ID和现在的不同，或者商品列表为空，意味着需要重新加载数据
	//根据ID实例化(读取数据文件)
	if (_tempMerchantId != merchant->_NPCID|| !_goodsInstanceList.size())
	{
		//将商店老板ID值修改
		_tempMerchantId = merchant->_NPCID;
		if (_goodsInstanceList.size())
		{
			//如果商品列表不为空
			//先删除数据
			deleteGoodsInstanceList();
		}
		for (int i = 0; i < merchant->_npcType._typeData.size(); i++)
		{
			_goodsInstanceList.push_back(
				Item::create(merchant->_npcType._typeData[i]));
		}
	}

	//如果实例化之后还是为空数据
	if (_goodsInstanceList.size()==0|| _goodsInstanceList.size()<0)
	{
		return NULL;
	}

	return &_goodsInstanceList;
}

Item * GoodsManage::getItemFromGoodsInstanceList(int itemid)
{
	if (!itemid)
	{
		return NULL;
	}
	for (int i = 0; i < _goodsInstanceList.size(); ++i)
	{
		if (_goodsInstanceList[i]->_itemId==itemid)
		{
			return _goodsInstanceList[i];
		}
	}
	return NULL;
}

void GoodsManage::deleteGoodsInstanceList()
{
	if (!_goodsInstanceList.size())
	{
		return;
	}
	//清除内存
	for (vector<class Item*>::iterator i = _goodsInstanceList.begin(); i != _goodsInstanceList.end(); )
	{
		delete *i;
	}

}

GoodsManage::GoodsManage()
{
	_tempMerchantId = 0;
}

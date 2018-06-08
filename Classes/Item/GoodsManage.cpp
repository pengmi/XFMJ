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
	//���merchant�����ڣ���Ϊֱ����Ҫ��ȡ��ǰ��Ʒ�б�
	if (!merchant)
	{
		return &_goodsInstanceList;
	}
	//�ж��Ƿ������˵���Ʒ�Ƿ��Ѿ�����
	//��ֹ�����ȡ�ļ��Ķ���
	if (_tempMerchantId==merchant->_NPCID&&_goodsInstanceList.size())
	{
		return &_goodsInstanceList;
	}
	//�������ID�����ڵĲ�ͬ��������Ʒ�б�Ϊ�գ���ζ����Ҫ���¼�������
	//����IDʵ����(��ȡ�����ļ�)
	if (_tempMerchantId != merchant->_NPCID|| !_goodsInstanceList.size())
	{
		//���̵��ϰ�IDֵ�޸�
		_tempMerchantId = merchant->_NPCID;
		if (_goodsInstanceList.size())
		{
			//�����Ʒ�б�Ϊ��
			//��ɾ������
			deleteGoodsInstanceList();
		}
		for (int i = 0; i < merchant->_npcType._typeData.size(); i++)
		{
			_goodsInstanceList.push_back(
				Item::create(merchant->_npcType._typeData[i]));
		}
	}

	//���ʵ����֮����Ϊ������
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
	//����ڴ�
	for (vector<class Item*>::iterator i = _goodsInstanceList.begin(); i != _goodsInstanceList.end(); )
	{
		delete *i;
	}

}

GoodsManage::GoodsManage()
{
	_tempMerchantId = 0;
}

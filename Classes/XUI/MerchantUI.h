#pragma once
#ifndef _MERCHANT_UI_H_
#define _MERCHANT_UI_H_

#include<cocos2d.h>

USING_NS_CC;
using namespace std;

class MerchantUI :public Layer
{
public:
	static MerchantUI* create();

	bool init();
	//���ñ���
	void setBackGround();
	void initData();
	//���õ���¼�����Ҫ�������ε���¼�
	void initMenu();
	void initTouch();
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *user_event) { return 1; };
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *user_event) {};
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *user_evenr) {};

	//������Ʒ�˵����˵���
	void menuClickLoadGoods(cocos2d::Ref * pSender) ;
	void setGoodsMenuUI();
	//���ر����˵����˵���
	void menuClickLoadBag(cocos2d::Ref * pSender,bool option=false) ;
	void setBagMenuUI();
	//���UI����
	void clearGoodsMenuUI();
	//�رձ���
	void menuClickClose(cocos2d::Ref * pSender);


	//�����Ʒ���Ժ��ui����
	//void hideSelectedOperationUI();//����
	//void viewSelectedOperationUI();//��ʾ

	//������ʾ��Ϣ
	void popMsgLabel(std::string str);

	//�����ʾ��Ʒ��Ϣ
	void listItemInfo(cocos2d::Ref * pSender, class Item * item,int num=0);
	//�����Ʒ�Ժ󣬼�������4��������ť
	void itemClickLoadOperateUI(cocos2d::Ref * pSender, Item * item,int num=0);
	//���������ť
	void clearOperateUI();
	void hideOperateUI();
	void visiableOperateUI();
	//������Ʒ��ť�ص�����
	//���ݴ�����GoodsManage�������
	void menuClickConfirmBuy(cocos2d::Ref * pSender, int itemid);
	/*������Ʒ��ť�ص�����
	���ݴ�����BagManage�������
	*/
	void menuClickConfirmSell(cocos2d::Ref * pSender,Item *item);
	//���Ӳ�������
	void menuClickAddOperateNum(cocos2d::Ref * pSender,int numInBag=0);
	//���ٲ�������
	void menuClickSubOperateNum(cocos2d::Ref * pSender);

	void refreshNumLabel();
	void refreshMoneyLabel();
private:

	int _itemNum;

	int _operateType;

	//��Ǯ��ͼ��
	Label * _moneyLabel = NULL;
	Label * _numLabel = NULL;
						   //int _curBag=1;
	Sprite* _bagback1 = NULL;//��������
	Sprite* _bagback2 = NULL;//��������

	MenuItem * _closeItem = NULL;//�˳��̵갴ť
	MenuItem * _goodsItem = NULL;//�л�����Ʒ��ť
	MenuItem * _bagItem = NULL;//�л���������ť
	MenuItem * _imageItemLeft[3][5] = { NULL };
	MenuItem * _imageItemRight[3][5] = { NULL };
	Menu * _itemsMenu = NULL;//��ť����



	MenuItem * _confirmBuyItem = NULL;//����ť
	MenuItem * _confirmSellItem = NULL;//���۰�ť
	MenuItem * _subNumItem = NULL;//��������ť
	MenuItem * _addNumItem = NULL;//�����Ӱ�ť
	Menu * _selectedMenu = NULL;//ѡ����Ʒʱ�Ĳ˵�����
};

#endif // !1


#ifndef __Base_SCENE_H__
#define __Base_SCENE_H__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Player\HeroLayer.h"
#include "XUI\BaseUI.h"
#include "Gut\NPC.h"
#include "Player\PlayerManage.h"
#include "XData\DataManage.h"
#include <iostream>
//using namespace cocos2d;
//using namespace CocosDenshion;
USING_NS_CC;

class BaseScene : public cocos2d::Layer
{
public:
	//���ೡ����ֻ�����̳�,createScene����������
	//static cocos2d::Scene* createScene();


	//init
	//virtual bool init();
	virtual bool init(std::string curMAPNAME,std::string preMAPNAME);
	void popMsg();
	virtual bool initMap(std::string mapName) ;//��ͼ
	virtual bool getPlayerManager();//��ҹ�����
	virtual bool initPlayer() ;//���
	void setPlayerSpwanPoint();
	virtual void initBackground();
	virtual void initTouch();
	void initXData();
	void initXUI();
	//initData()
	//�ǲ��ǻ���Ҫһ����ʼ����ͼ����,�õ���������Ժ���ȥ��ʼ����ͼ�еĵ��ˣ�NPC����Ʒ
	virtual bool initEnemy() ;//����

	virtual bool initNPC() ;//�Ѻõ�λ,���ˣ������
	bool checkNPCInConfigDisableList(int id);

	//control
	
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *user_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *user_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *user_evenr);
	//virtual void keyBackClicked(Touch *touch, Event *user_evenr) {};//Android ���ؼ�
	//virtual void keyMenuClicked(Touch *touch, Event *user_evenr) {};//Android �˵���


	//���ݲ���
	cocos2d::ValueMap getObjectGroupValueMap(std::string objectName);//�ҵ�����ͼObject������Ķ�������
	//cocos2d::Vector<cocos2d::ValueMap> getObjectGroupsValueMap();
	cocos2d::ValueVector getAllObjectGroupValueMaps();//

	//���º���
	//virtual void update(float dt) {};//update����
	void updateViewPointCenter();
	//void updateBaseUIPosition(Point &point);
	void updateBaseUIPosition(Point &point);
	const std::string getCurMapName();
	virtual void changeScene(std::string mapName) {};//���ص�ͼ


	//��ײ���
	////ʵ����.h�ļ���ĺ�������Ĭ�������������������inline,��������Ϊ���Ժ󿴵ķ���.
	//��ײ�����Ƶ����ʹ�ã�����ʹ�������������������ҲӦ�þ���С.

	//�ҵ�����Ƭ�ز��е�λ��
	cocos2d::Point tileCoordForPosition(cocos2d::Point position);

	//inline
	//��ͼ�����ײ���
	bool mapCollisonDetection(cocos2d::Point position);
	
	//������ͼ�е�ͼ����������ײ
	std::map<std::string, std::string> mapControllerDetection();
	
	//�Ƿ���npc��ײ,�����ײ�Ļ����npc��Ӧ���������û������ʵ���ʹ���
	bool npcCollisonDetection(Point position);

	bool gutDisplay(NPC* npc);

	//����Ҫ�̳еĺ�����ֱ�ӿ���ʹ��
	void setPlayerPosition(cocos2d::CCPoint point)
	{
		_playerManager->_sprite->setPosition(point);
	}

	//void popMsgInfo(std::string);
	
	//�ص�����

	void menuCloseCallback(cocos2d::Ref* pSender);
	bool mainSceneChangeCheck();

protected:
	

	/*
	ΪʲôUI�಻�����������һ����ֻ��һ��ʵ���õ�β�����ǿ���ÿ�����������¼��أ�
	��ΪUI������������������������������ݣ��Ҳ���Ҫһ��ʵ����ͷ��β��ֻ��Ҫ��
	�Ҵ�UI��ʱ�����ֶ��İ��������ݴ��ݸ�UI�����ˣ�������Ҫ�����������һ����
	��Ȼ����ʵUI��ȷʵ�����������������һ����
	*/
	BaseUI * _baseUi;//�˵���


	std::string _mapName = "";//���ڵ�ͼID
	std::string _preMapName = "";//�ݴ���һ����ͼID����Ҫ����ȷ�ϳ�����
	cocos2d::experimental::TMXTiledMap *_tileMap = NULL;//��ͼ�ļ�

	//�����������ȥ����������ֱ�ӹ�������ʵ������Ϊ���������ʵ����
	//���������ҹ���������Ϸһ��ʼ��ֻ����һ��ʵ��������ȫ��ʹ������
	//��Ϊ��Ҳ�һ����ʱ�浵��������ÿһ���л��������Ҷ�ȥ��������
	//���ص�����Ҳ�������µ����ݣ�������������Ҫ�ֶ����ص�ʱ���������
	//�����ҹ����������������Ϊ��ʱ�ģ��ǳ־û������ݴ�ŵص㣬��ֻ����һ��ʵ��һʹ�á�
	PlayerManage * _playerManager=NULL;

	std::vector<NPC*> _npcVector;
};

#endif // __BASE_SCENE_H__
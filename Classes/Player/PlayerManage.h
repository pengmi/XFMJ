#pragma once
#ifndef _PLAYER_MANAGE_H_
#define _PLAYER_MANAGE_H_
#include<cocos2d.h>
#include "HeroLayer.h"
#include "tool\HelpTool.h"
#include "XData\DataModel.h"
#include "Item\BagManage.h"

//class PlayerManage;
class PlayerManage :public Layer
{
public:
	//CREATE_FUNC(PlayerManage);
	//��ʼ��
	static PlayerManage * create();
	static PlayerManage *getInstance();
	bool init();
	void createPlayer();
	void removePlayer(HeroLayer*);

	//λ�ü��ƶ�
	void checkDirection(Point &p1,Point &p2);
	void setSpriteFrame();//��Ҫ�Ǹ��ݷ�����������sprite��ʵ�����ߵ�Ч��
	void moveSprite(Point &point);
	Sprite* getPlayerSprite() { return _sprite; };
	void setSpritePosition(Point& point);

	//ս������

	//void addExperience();
	//void LeveUp();


	//���Թ���
	//void caclulatePlayerStatus(HeroLayer* hero,BagManage* bagManage);
	//void setEquipmentList(HeroLayer* hero, BagManage* bagManage);

	HeroLayer *_huangZaiLayer=NULL;//������ʵ�� ��ɫ1
	HeroLayer *_lianLayer=NULL;//����ʵ�� ��ɫ2
	HeroLayer *_cmLayer = NULL;//������ʵ�� ��ɫ3
	Sprite * _sprite=NULL;//�ڵ�ͼ���ܵľ��� 

	//���ݻ�ȡ������
	void setDirection(int i=0);
	void setStepIndex(int i=1);
	bool getCmVisualable();
	void setCmVisualable(bool b=false);
	bool getLianVisualable();
	void setLianVisualable(bool b=false);
	void setMapName(std::string m);
	std::string getMapName();

	//ʹ����Ʒ,�޸�status
	std::string useItem(HeroLayer* hero, Item* const item);
	//װ����Ʒ1.��item���Դ�status����;2.��hero�е�equipment�����޸�
	std::string equipItem(HeroLayer* hero, Item* const item);
	//ж��װ��1.��item���Դ�status��ȥ;2.��hero�е�equipment�����޸�
	std::string unloadEquipment(HeroLayer* hero, Item* const item);
private:
	PlayerManage();
	static PlayerManage*_instance;//��������ôʵ�ֵ���
	
	bool _hzVisualable = true;
	bool _lianVisualable = false;
	bool _cmVisualable = false;

	static const enum Direction
	{
		up,right,left,down
	};

	std::string _mapName;
	int _direct= Direction::up;//����0-3
	int _stepindex=1;//��������1-3
	std::string _playerSpriteSrc = "player/player.png";
	std::string _stepPlistSrc = "player/plist.plist";
	std::string _stepPngSrc = "player/plist.png";

	SpriteFrameCache *_playerFrameCache = NULL;

	
};


#endif _PLAYER_MANAGE_H_
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
	//初始化
	static PlayerManage * create();
	static PlayerManage *getInstance();
	bool init();
	void createPlayer();
	void removePlayer(HeroLayer*);

	//位置及移动
	void checkDirection(Point &p1,Point &p2);
	void setSpriteFrame();//主要是根据方向和序号设置sprite，实现行走的效果
	void moveSprite(Point &point);
	Sprite* getPlayerSprite() { return _sprite; };
	void setSpritePosition(Point& point);

	//战斗结算

	//void addExperience();
	//void LeveUp();


	//属性管理
	//void caclulatePlayerStatus(HeroLayer* hero,BagManage* bagManage);
	//void setEquipmentList(HeroLayer* hero, BagManage* bagManage);

	HeroLayer *_huangZaiLayer=NULL;//柳随风的实例 角色1
	HeroLayer *_lianLayer=NULL;//莲的实例 角色2
	HeroLayer *_cmLayer = NULL;//慈敏的实例 角色3
	Sprite * _sprite=NULL;//在地图上跑的精灵 

	//数据获取和设置
	void setDirection(int i=0);
	void setStepIndex(int i=1);
	bool getCmVisualable();
	void setCmVisualable(bool b=false);
	bool getLianVisualable();
	void setLianVisualable(bool b=false);
	void setMapName(std::string m);
	std::string getMapName();

	//使用物品,修改status
	std::string useItem(HeroLayer* hero, Item* const item);
	//装备物品1.将item属性从status加上;2.将hero中的equipment数据修改
	std::string equipItem(HeroLayer* hero, Item* const item);
	//卸载装备1.将item属性从status减去;2.将hero中的equipment数据修改
	std::string unloadEquipment(HeroLayer* hero, Item* const item);
private:
	PlayerManage();
	static PlayerManage*_instance;//单例，怎么实现到底
	
	bool _hzVisualable = true;
	bool _lianVisualable = false;
	bool _cmVisualable = false;

	static const enum Direction
	{
		up,right,left,down
	};

	std::string _mapName;
	int _direct= Direction::up;//面向0-3
	int _stepindex=1;//面向索引1-3
	std::string _playerSpriteSrc = "player/player.png";
	std::string _stepPlistSrc = "player/plist.plist";
	std::string _stepPngSrc = "player/plist.png";

	SpriteFrameCache *_playerFrameCache = NULL;

	
};


#endif _PLAYER_MANAGE_H_
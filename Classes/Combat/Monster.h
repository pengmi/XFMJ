#pragma once
#ifndef _MONSTER_H_
#define _MONSTER_H_
#include<cocos2d.h>

using namespace std;
USING_NS_CC;
class Monster:public cocos2d::Sprite
{
public:
	/*若要将Monster使用addChild添加到节点中，必须使用autorelease
	也就是最好使用create函数
	*/
	static Monster* createWithSpriteFrame(
		SpriteFrame *spriteFrame, const Monster* monster);
	~Monster();
	Monster();
	Monster(int id);
	Monster(const Monster* monster);

	//bool init(const Monster* monster);

	//主要是使怪物初始化
	void initSprite();
	//使怪物进入站立状态
	bool stand();
	//播放怪物攻击动画，完成后就进入站立状态
	void attack(float dt);
	//播放被攻击动画，完成后就进入战立状态
	//如果死了就调用战斗管理移队这个怪物
	bool hit(int const& damage);
	void postCaclulateNotification(cocos2d::Node * pSender);
	void postAttackFinishNotification(cocos2d::Node * pSender);
	void setPlayerControlDisactive(cocos2d::Node * pSender);
	void setPlayerControlActive(cocos2d::Node * pSender);

	void initTouch();
	bool onTouchBegan(Touch* tTouch, Event* eEvent);//手指按下事件
	void onTouchMoved(Touch* tTouch, Event* eEvent);//手指移动事件
	void onTouchEnded(Touch* tTouch, Event* eEvent);//手指离开事件

	int _id;
	string _name;
	int _type;
	string _standUrl;//plist文件
	string _attackUrl;
	string _hitUrl;
	string _intro ;

	struct ItemIdNRate
	{
		int _itemID;
		int _rate;
	};

	vector<ItemIdNRate> _rewardItemList;
	void deleteRewardItemList();
	vector<int> _skillList;
	int _level;
	int _life;
	int _magic;
	int _attack;
	int _defence;
	int _exp;
	int _money;

	SpriteFrameCache *_standFrameCache = NULL;
	SpriteFrameCache *_attackFrameCache = NULL;
	SpriteFrameCache *_hitFrameCache = NULL;
private:
	//Monster();
	
};



#endif // !_MONSTER_H_

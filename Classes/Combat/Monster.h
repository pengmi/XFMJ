#pragma once
#ifndef _MONSTER_H_
#define _MONSTER_H_
#include<cocos2d.h>

using namespace std;
USING_NS_CC;
class Monster:public cocos2d::Sprite
{
public:
	/*��Ҫ��Monsterʹ��addChild��ӵ��ڵ��У�����ʹ��autorelease
	Ҳ�������ʹ��create����
	*/
	static Monster* createWithSpriteFrame(
		SpriteFrame *spriteFrame, const Monster* monster);
	~Monster();
	Monster();
	Monster(int id);
	Monster(const Monster* monster);

	//bool init(const Monster* monster);

	//��Ҫ��ʹ�����ʼ��
	void initSprite();
	//ʹ�������վ��״̬
	bool stand();
	//���Ź��﹥����������ɺ�ͽ���վ��״̬
	void attack(float dt);
	//���ű�������������ɺ�ͽ���ս��״̬
	//������˾͵���ս�������ƶ��������
	bool hit(int const& damage);
	void postCaclulateNotification(cocos2d::Node * pSender);
	void postAttackFinishNotification(cocos2d::Node * pSender);
	void setPlayerControlDisactive(cocos2d::Node * pSender);
	void setPlayerControlActive(cocos2d::Node * pSender);

	void initTouch();
	bool onTouchBegan(Touch* tTouch, Event* eEvent);//��ָ�����¼�
	void onTouchMoved(Touch* tTouch, Event* eEvent);//��ָ�ƶ��¼�
	void onTouchEnded(Touch* tTouch, Event* eEvent);//��ָ�뿪�¼�

	int _id;
	string _name;
	int _type;
	string _standUrl;//plist�ļ�
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

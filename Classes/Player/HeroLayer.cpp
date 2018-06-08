#include "HeroLayer.h"

HeroLayer * HeroLayer::create()
{
	HeroLayer *pRet = new HeroLayer;
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

//bool HeroLayer::init()
//{
//
//	initPlayer();
//	initStatus();
//	return true;
//}



bool HeroLayer::initStatus()
{
	_status._level = 1;
	_status._levelExperience = 0;
	_status._needExperience = 100;
	_status._playerMaxLife=100;//�������
	_status._playerLife=300;//����ħ��
	_status._playerMaxMagic=300;//���ħ��
	_status._playerMagic=300;//����ħ��

	_status._playerPower=20;//����
	_status._playerAgility=20;//��
	_status._playerIntelligence=20;//����

	_status._playerAttack=20;//������
	_status._playerDefence=20;//������

	_status._playerHit=80;//����
	_status._playerDodge=10;//����
	return true;
}

bool HeroLayer::initEquipment()
{

	return true;
}

bool HeroLayer::initSkill()
{
	return true;
}

void HeroLayer::menuCloseCallback(cocos2d::Ref * pSender)
{
	//CCLOG("menu",);
}

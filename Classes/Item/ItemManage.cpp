#include "ItemManage.h"
ItemManage* ItemManage::_instance = NULL;

ItemManage::ItemManage()
{

}

ItemManage::~ItemManage()
{
	delete _instance;
}


ItemManage* ItemManage::getInstance()
{
	if (NULL == _instance)
	{
		_instance = new ItemManage();
	}
	return _instance;
}

void ItemManage::useItem(Item & it, Status & s)
{
	s._playerMaxLife += it._addMaxLife;
	s._playerLife += it._addLife;
	s._playerMaxMagic += it._addMaxMagic;
	s._playerMagic += it._addMagic;
	s._playerPower += it._addPower;
	s._playerAgility += it._addAgility;
	s._playerIntelligence += it._addIntelligence;
	s._playerAttack += it._addAttack;
	s._playerHit += it._addHit;
	s._playerDodge += it._addDodge;
}
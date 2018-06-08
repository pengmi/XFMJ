#include "NPC.h"
#include "XData\DataManage.h"
#include "GutManage.h"
USING_NS_CC;

bool NPC::init(int npcid)
{
//#pragma region Data
	DataManage::getInstance()->readNpcData(this, npcid);

	GutManage::getInstance()->createTaskInstance(&(this->_taskIDList));

//#pragma endregion

//#pragma region Sprite
	_npcSprite = cocos2d::Sprite::create(this->_picurl);
	this->addChild(_npcSprite);
//#pragma endregion

	return true;
}

void NPC::action()
{

}

std::vector<std::string> NPC::getConv()
{
	//_convID;
	//std::vector<std::string> strVec = {"道童：师兄，师兄！","黄载：跑这么急，是不是我出来玩被发现了？",
	//	"道童：刚才师父来练功房，没找到你。现在暴跳如雷！","黄载：哎呀，哎呀，完蛋了，我得马上回去。"};
//	bui->loadConvUI(strVec);
	return _conv;
}

Sprite * NPC::getNPCSprite()
{
	return _npcSprite;
}

NPC * NPC::create(int npcid)
{
	NPC *pRet = new NPC;
	if (pRet&&pRet->init(npcid))
	{
		pRet->autorelease();
		return pRet;
	}
	else {
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

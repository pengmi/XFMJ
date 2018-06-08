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
	//std::vector<std::string> strVec = {"��ͯ��ʦ�֣�ʦ�֣�","���أ�����ô�����ǲ����ҳ����汻�����ˣ�",
	//	"��ͯ���ղ�ʦ������������û�ҵ��㡣���ڱ������ף�","���أ���ѽ����ѽ���군�ˣ��ҵ����ϻ�ȥ��"};
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

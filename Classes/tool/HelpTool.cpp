#include "HelpTool.h"

CCAnimation* HelpTool::CreateAnimationByFile(const char*name,int hori,int vert)
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	SpriteFrame* frame = SpriteFrame::create(name,Rect(0,0,128,128));

	/*
	SpriteFrame���������CCTexture2D����
	�ҵ�����������TexturePacker����Ĵ�ͼ
	���ң�ͬһ�Ŵ�ͼ���ɵ�SpriteFrame�����getTexture�Ľ����һ�µġ�
	���仰˵��SpriteFrame��ʵ������һ��ͼƬ��������á�
	*/
	CCTexture2D* texture = frame->getTexture();

	/*
	�Һܺ��棬getOriginalSize��getOriginalSizeInPixels������ʲô����
	��΢���о�һ�£��ٺʹ�ҷ���
	*/
	CCSize frameSize = frame->getOriginalSizeInPixels();

	/*
	SpriteFrame�Ƿ�û������ĸ���ģ�
	ֻ�о���Χ����������Ҫ�������λ�ã�
	����ͨ�����ľ���Χ��ȡ��
	*/
	CCRect frameRect = frame->getRect();

	float w = frameSize.width / hori;    /* ÿ֡ͼƬ�Ŀ�*/
	float h = frameSize.height/vert;

	float x = frameRect.origin.x;
	float y = frameRect.origin.y;

	Vector<SpriteFrame*> framesArray;
	for (int i = 0; i < vert; i++)
	{
		y += h;
		for (int j=0; j < hori; j++)
		{
			/*
			��һֱ���ܵ��ģ�createWithTexture�ǲ��Ǿ��������µ��������
			������������ϸ���룬SpriteFrame������ֻ��������������󣬶������½�һ��С����
			�ҵ�����ǣ�SpriteFrame��ʵֻ�����¼���ݵ����ã���¼��ĳ��ͼƬ֡�����Ŵ�ͼƬ��λ�ã��Լ���ȡ��Χ�ȡ�
			���ԣ�createWithTextureֻ�����ǰ�SpriteFrame�ķ�Χ�ı���һ�¶��ѡ�
			*/
			auto tmpspriteframe = CCSpriteFrame::createWithTexture(texture, CCRectMake(x, y-h, w, h));
			framesArray.pushBack(tmpspriteframe);	
			x += w;		
		}	
	}

	CCAnimation* animation = CCAnimation::createWithSpriteFrames(framesArray);
	//animation->setLoops(0);
	//animation->setRestoreOriginalFrame(false);
	animation->setDelayPerUnit(1.0f);

	return animation;
}

/*ȡ����ײ���ӣ������getBoundingBox()��������ǣ�
�������һ��ƫ�ƣ���ȫ�����鶼������ײ��Χ*/
Rect HelpTool::GetSpritePosition(Sprite * sprite)
{
	Vec2 pos=sprite->getPosition();
	Rect rect=sprite->getBoundingBox();
	Rect newrect;
	newrect.size.width=rect.size.width;
	newrect.size.height=rect.size.height;
	newrect.origin.x=pos.x-rect.size.width/2;
	newrect.origin.y=pos.y-rect.size.height/2;
	return newrect;
}

SpriteFrameCache * HelpTool::GetFrameCache(const char* str1, const char* str2)
{
	SpriteFrameCache* framecache = SpriteFrameCache::getInstance();
	framecache->addSpriteFramesWithFile(str1,str2);
	return framecache;
}

Animation * HelpTool::GetHitAnimationByFileName(const char * plistname, const char * pngname,int num)
{
	auto spriteframecache = HelpTool::GetFrameCache(plistname, pngname);
	SpriteFrame *frame[9];
	string tmpstr = "";
	string str = "";
	auto animation = CCAnimation::create();
	switch (num)
	{
	case 1:
	{
		for (int i = 0; i < 8; i++)
		{
			CCString *num = CCString::createWithFormat("%d", i + 1);
			string numstr = num->_string.c_str();
			tmpstr = "00" + numstr;
			str = "a_" + tmpstr + ".png";
	
			frame[i] = spriteframecache->getSpriteFrameByName(str);
			animation->addSpriteFrame(frame[i]);
		}
		break;
	}
	case 2:
	{
		for (int i = 0; i < 8; i++)
		{
			CCString *num = CCString::createWithFormat("%d", i + 1);
			string numstr = num->_string.c_str();
			tmpstr = "00" + numstr;
			str = "b_" + tmpstr + ".png";

			frame[i] = spriteframecache->getSpriteFrameByName(str);
			animation->addSpriteFrame(frame[i]);
		}
		break;
	}
	case 3:
	{
		for (int i = 0; i < 8; i++)
		{
			CCString *num = CCString::createWithFormat("%d", i + 1);
			string numstr = num->_string.c_str();
			tmpstr = "00" + numstr;
			str = "c_" + tmpstr + ".png";

			frame[i] = spriteframecache->getSpriteFrameByName(str);
			animation->addSpriteFrame(frame[i]);
		}
		break;
	}
	case 4:
	{
		for (int i = 0; i < 9; i++)
		{
			CCString *num = CCString::createWithFormat("%d", i + 1);
			string numstr = num->_string.c_str();
			tmpstr = "0000" + numstr;
			str = "d_" + tmpstr + ".png";

			frame[i] = spriteframecache->getSpriteFrameByName(str);
			animation->addSpriteFrame(frame[i]);
		}
		break;
	}
	default:
		break;
	}
	

	animation->setDelayPerUnit(0.01f);
	return animation;
}

int HelpTool::RemoveFromArry(vector< Sprite*> m_arry, Sprite * pSender)
{
	Sprite *psender = dynamic_cast<Sprite*>(pSender);
	typedef vector<Sprite*>::iterator Iter;
	for (Iter it = m_arry.begin(); it != m_arry.end(); ++it)
	{
		if (*it == psender) {

			m_arry.erase(it);
			return 1;
		}
	}
	return 0;
}

//null not allowed,num=1 or 2
Sprite * HelpTool::GetSpriteByFileName(const char * filename,int num)
{
	//SpriteFrame* frame = SpriteFrame::create(filename, Rect(0, 0, 128, 128));
	SpriteFrame* frame = SpriteFrame::create(filename, Rect(0, 0, 128, 128));
	CCTexture2D* texture = frame->getTexture();

	CCSize frameSize = frame->getOriginalSizeInPixels();

	CCRect frameRect = frame->getRect();
	float w = 0;
	float h = 0;
		w = frameSize.width / 2;    /* ÿ֡ͼƬ�Ŀ�*/
		h = frameSize.height / 1;

	float x = frameRect.origin.x;
	float y = frameRect.origin.y;

	Sprite *sprite = NULL;
	for (int i = 0; i < num; i++)
	{
		SpriteFrame* tmpspriteframe = CCSpriteFrame::createWithTexture(texture, CCRectMake(x, y, w, h));
		sprite=Sprite::createWithSpriteFrame(tmpspriteframe);
		x += w;
	}

	return  sprite;
}

std::string HelpTool::int2str(const int & int_temp)
{

	stringstream stream;
	stream << int_temp;
	return stream.str();   //�˴�Ҳ������ stream>>string_temp
}



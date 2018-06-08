#include "HelpTool.h"

CCAnimation* HelpTool::CreateAnimationByFile(const char*name,int hori,int vert)
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	SpriteFrame* frame = SpriteFrame::create(name,Rect(0,0,128,128));

	/*
	SpriteFrame的纹理对象（CCTexture2D），
	我的理解就是那张TexturePacker打包的大图
	并且，同一张大图生成的SpriteFrame对象的getTexture的结果是一致的。
	换句话说，SpriteFrame其实保存了一份图片纹理的引用。
	*/
	CCTexture2D* texture = frame->getTexture();

	/*
	我很好奇，getOriginalSize和getOriginalSizeInPixels倒底有什么区别？
	稍微我研究一下，再和大家分享
	*/
	CCSize frameSize = frame->getOriginalSizeInPixels();

	/*
	SpriteFrame是否没有坐标的概念的，
	只有矩阵范围这个概念，所以要获得它的位置，
	必须通过它的矩阵范围来取得
	*/
	CCRect frameRect = frame->getRect();

	float w = frameSize.width / hori;    /* 每帧图片的宽*/
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
			我一直都很担心，createWithTexture是不是就生成了新的纹理对象？
			不过，我再仔细想想，SpriteFrame本来就只是引用了纹理对象，而不是新建一份小纹理。
			我的理解是，SpriteFrame其实只是其记录数据的作用，记录了某个图片帧在整张大图片的位置，以及截取范围等。
			所以，createWithTexture只不过是把SpriteFrame的范围改变了一下而已。
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

/*取得碰撞盒子，这个和getBoundingBox()的区别就是，
这个会做一个偏移，让全部精灵都进入碰撞范围*/
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
		w = frameSize.width / 2;    /* 每帧图片的宽*/
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
	return stream.str();   //此处也可以用 stream>>string_temp
}



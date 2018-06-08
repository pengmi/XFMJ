#include "DataManage.h"


DataManage *DataManage::_instance = NULL;
DataManage::DataManage()
{
}
DataManage::~DataManage()
{
	delete _instance;
	_instance = NULL;
}

DataManage * DataManage::getInstance()
{
	if (NULL ==_instance)
	{
		_instance = new DataManage();
	}
	return _instance;
}

void DataManage::initData()
{
	//对游戏玩家管理类数据读取
	DataManage::getInstance()->readPlayerManageData(
		PlayerManage::getInstance());
	PlayerManage::getInstance()->setSpriteFrame();
	//游戏管理类数据读取以后，创建人物
	PlayerManage::getInstance()->createPlayer();
	///////////////////////////////////////////////////////PlayerManage
	//对英雄数据进行读取
	DataManage::getInstance()->readHeroStatusNEquipments(
		PlayerManage::getInstance()->_huangZaiLayer);//
	if (PlayerManage::getInstance()->getLianVisualable())//如果莲存在
	{
		DataManage::getInstance()->readHeroStatusNEquipments(
			PlayerManage::getInstance()->_lianLayer);
	}
	if (PlayerManage::getInstance()->getCmVisualable())
	{
		DataManage::getInstance()->readHeroStatusNEquipments(
			PlayerManage::getInstance()->_cmLayer);
	}
	////////////////////////////////////HeroLayer

	/*读取背包数据*/

	readBagData(BagManage::getInstance());

	////////////////////////////////////////BagManage
	/*读取剧情配置数据*/
	readGutData(GutManage::getInstance());
	/////////////////////////////////GutManage
	
	//对NPC和怪物的读取应该放在Scene里，因为场景决定怪物和NPC


}

void DataManage::readPlayerManageData(PlayerManage * obj)
{
	/*
	"position" : {
			"x":0,
			"y":0
			},
	"direction" : 0,
	"stepindex" : 1,
	"mapname":1,
	"huangzai":"true",
	"cm":"false",
	"lian":"false"
	*/
	Data dat = (loadJsonFile("Player/player.json"));
	if (dat.getSize() <= 0)
	{
		// no file 
		return ;
	}
	char *buf = new char[dat.getSize() + 1];
	strncpy(buf, (char*)dat.getBytes(), dat.getSize());
	buf[dat.getSize()] = 0;  //重新分配内存就是为了这一步，否则直接用Data来解析会解析错误。

	rapidjson::Document d;
	d.Parse<0>(buf);
	delete[] buf;
	if (d.HasParseError())  //解析错误
	{
		return;
	}
	else if (d.IsObject())
	{

		rapidjson::Value & positionx  = d["position"]["x"];
		rapidjson::Value & positiony = d["position"]["y"];
		rapidjson::Value & direction = d["direction"];
		rapidjson::Value & stepindex = d["stepindex"];
		rapidjson::Value & mapname = d["mapname"];
		rapidjson::Value & huangzai = d["huangzai"];
		rapidjson::Value & cm = d["cm"];
		rapidjson::Value & lian = d["lian"];

		

		obj->setDirection(direction.GetInt());
		obj->setStepIndex(stepindex.GetInt());
		obj->setMapName(mapname.GetString());
		obj->setLianVisualable(lian.GetBool());
		obj->setCmVisualable(cm.GetBool());
		obj->setSpritePosition(Point(positionx.GetDouble(),positiony.GetDouble()));


		
	}

}

void DataManage::readHeroStatusNEquipments(HeroLayer * hero,string dataurl)
{

	/*
{
	"name" : "黄载",
	"picurl" : "player/player.png",
	"status" :{
		"maxlife":300,
		"life":300,
		"maxmagic":300,
		"magic":300,
		"power":20,
		"agility":20,
		"intelligence":20,
		"attack":20,
		"defence":20,
		"hit":80,
		"dodge":10
		}
}
	*/

	Data dat = (loadJsonFile(dataurl));
	if (dat.getSize() <= 0)
	{
		// no file 
		return;
	}
	char *buf = new char[dat.getSize() + 1];
	strncpy(buf, (char*)dat.getBytes(), dat.getSize());
	buf[dat.getSize()] = 0;  //重新分配内存就是为了这一步，否则直接用Data来解析会解析错误。

	rapidjson::Document d;
	d.Parse<0>(buf);
	delete[] buf;
	if (d.HasParseError())  //解析错误
	{
		return;
	}
	else if (d.IsObject())
	{
		rapidjson::Value & name = d["name"];
		rapidjson::Value & picurl = d["picurl"];
		rapidjson::Value & maxlife = d["status"]["maxlife"];
		rapidjson::Value & life = d["status"]["life"];
		rapidjson::Value & maxmagic = d["status"]["maxmagic"];
		rapidjson::Value & magic = d["status"]["magic"];
		rapidjson::Value & power = d["status"]["power"];
		rapidjson::Value & agility = d["status"]["agility"];
		rapidjson::Value & intelligence = d["status"]["intelligence"];
		rapidjson::Value & attack = d["status"]["attack"];
		rapidjson::Value & defence = d["status"]["defence"];
		rapidjson::Value & hit = d["status"]["hit"];
		rapidjson::Value & dodge = d["status"]["dodge"];

		
		auto s = hero->getPlayerStatus();
		hero->setHeroName(name.GetString());
		hero->setPicUrl(picurl.GetString());

		hero->_standUrl = d["standurl"].GetString();
		hero->_attackUrl = d["attackurl"].GetString();
		hero->_skillUrl = d["skillurl"].GetString();
		hero->_hitUrl = d["hiturl"].GetString();

		s->_level = d["status"]["level"].GetInt();
		s->_levelExperience = d["status"]["levelexperience"].GetInt();
		s->_needExperience= d["status"]["needexperience"].GetInt();
		s->_playerMaxLife = maxlife.GetInt();
		s->_playerLife=life.GetInt();
		s->_playerMaxMagic=maxmagic.GetInt();
		s->_playerMagic=magic.GetInt();
		s->_playerPower=power.GetInt();
		s->_playerAgility=agility.GetInt();
		s->_playerIntelligence=intelligence.GetInt();
		s->_playerAttack=attack.GetInt();
		s->_playerDefence=defence.GetInt();
		s->_playerHit=hit.GetInt();
		s->_playerDodge=dodge.GetInt();

		auto e = PlayerManage::getInstance()->_huangZaiLayer->getEquipmentsList();
		e->_weaponID = d["equipments"]["weapon"].GetInt();
		e->_headID = d["equipments"]["head"].GetInt();
		e->_clothesID = d["equipments"]["clothes"].GetInt();
		e->_cloackID = d["equipments"]["cloack"].GetInt();
		e->_gloveID = d["equipments"]["glove"].GetInt();
		e->_tassesID = d["equipments"]["tasses"].GetInt();
		e->_shoesID = d["equipments"]["shoes"].GetInt();
		e->_ornamentsID = d["equipments"]["ornaments"].GetInt();
	}
}

void DataManage::readBagData(BagManage * bagManage)
{
	bagManage->deleteBagData();

	Data dat = (loadJsonFile("Player/bag.json"));
	if (dat.getSize() <= 0)
	{
		// no file 
		return;
	}
	char *buf = new char[dat.getSize() + 1];
	strncpy(buf, (char*)dat.getBytes(), dat.getSize());
	buf[dat.getSize()] = 0;  //重新分配内存就是为了这一步，否则直接用Data来解析会解析错误。

	rapidjson::Document d;
	d.Parse<0>(buf);
	delete[] buf;
	if (d.HasParseError())  //解析错误
	{
		return;
	}
	else if (d.IsObject())
	{

		rapidjson::Value & money = d["money"];

		bagManage->setMoney(money.GetInt());

		rapidjson::Value & bagone = d["bagone"];
		rapidjson::Value & bagtwo = d["bagtwo"];

		for (int i = 0; i < 3; ++i)
		{
			for (int j=0;j<5;++j)
			{
				//int id= bagone[i][i]["id"].GetInt();
				if (bagone[i][j]["id"].GetInt())
				{
					bagManage->BagOne[i][j].item = 
						getItemData(bagone[i][j]["id"].GetInt());
					bagManage->BagOne[i][j].num = 
						bagone[i][j]["num"].GetInt();
				}
				if (bagtwo[i][j]["id"].GetInt())
				{
					bagManage->BagTwo[i][j].item =
						getItemData(bagtwo[i][j]["id"].GetInt());
					bagManage->BagTwo[i][j].num =
						bagtwo[i][j]["num"].GetInt();
				}
			}
		}
	}

}

void DataManage::readGutData(GutManage * gutManage)
{
	Data dat = (loadJsonFile("Player/gut.json"));
	if (dat.getSize() <= 0)
	{
		// no file 
		return;
	}
	char *buf = new char[dat.getSize() + 1];
	strncpy(buf, (char*)dat.getBytes(), dat.getSize());
	buf[dat.getSize()] = 0;  //重新分配内存就是为了这一步，否则直接用Data来解析会解析错误。

	rapidjson::Document d;
	d.Parse<0>(buf);
	delete[] buf;
	if (d.HasParseError())  //解析错误
	{
		return;
	}
	else if (d.IsObject())
	{
		rapidjson::Value & taskconfig_finished = d["taskconfig"]["finished"];
		rapidjson::Value & taskconfig_ongoing = d["taskconfig"]["ongoing"];
		rapidjson::Value & npcconfig_talked = d["npcconfig"]["talked"];
		rapidjson::Value & npcconfig_disable = d["npcconfig"]["disable"];
		rapidjson::Value & enemyconfig_combat = d["enemyconfig"]["combat"];

		for (int i = 0; i < taskconfig_finished.Size(); ++i)
		{
			gutManage->_taskConfigList.finished.push_back(taskconfig_finished[i].GetInt());
		}
		for (int i = 0; i < taskconfig_ongoing.Size(); ++i)
		{
			gutManage->_taskConfigList.ongoing.push_back(taskconfig_ongoing[i].GetInt());
		}
		for (int i = 0; i < npcconfig_talked.Size(); ++i)
		{
			gutManage->_npcConfigList.talked.push_back(npcconfig_talked[i].GetInt());
		}
		for (int i = 0; i < npcconfig_disable.Size(); ++i)
		{
			gutManage->_npcConfigList.disable.push_back(npcconfig_disable[i].GetInt());
		}
		for (int i = 0; i < enemyconfig_combat.Size(); ++i)
		{
			gutManage->_enemyConfigList.combat.push_back(enemyconfig_combat[i].GetInt());
		}
	}
}

void DataManage::readNpcData(NPC * npc, int id)
{
	string str = "Npc/";
	str += HelpTool::int2str(id) + ".json";
	Data dat = (loadJsonFile(str));
	//Data dat = (loadJsonFile("npc/" + HelpTool::int2str(id) + ".json"));
	if (dat.getSize() <= 0)
	{
		// no file 
		return;
	}
	char *buf = new char[dat.getSize() + 1];
	strncpy(buf, (char*)dat.getBytes(), dat.getSize());
	buf[dat.getSize()] = 0;  //重新分配内存就是为了这一步，否则直接用Data来解析会解析错误。

	rapidjson::Document d;
	d.Parse<0>(buf);
	delete[] buf;
	if (d.HasParseError())  //解析错误
	{
		return;
	}
	else if (d.IsObject())
	{
		//rapidjson::Value & id = d["id"];
		rapidjson::Value & name = d["name"];
		rapidjson::Value & picurl = d["picurl"];

		rapidjson::Value & type = d["npctype"]["type"];
		rapidjson::Value & typedata = d["npctype"]["typedata"];
		rapidjson::Value & action = d["action"];

		rapidjson::Value & taskidlist = d["taskidlist"];
		rapidjson::Value & conv = d["conv"];

		npc->_NPCID = id;
		npc->_name = name.GetString();
		npc->_picurl = picurl.GetString();
		npc->_npcType._type = type.GetInt();
		//npc->_npcType._typeForId = typeforid.GetInt();
		npc->_action = action.GetInt();
		for (int i = 0; i < taskidlist.Size(); ++i)
		{
			npc->_taskIDList.push_back(taskidlist[i].GetInt());
		}

		for (int i = 0; i < typedata.Size(); ++i)
		{
			npc->_npcType._typeData.push_back(typedata[i].GetInt());
		}

		for (int i = 0; i < conv.Size(); ++i)
		{
			npc->_conv.push_back(conv[i].GetString());
		}
	}
}

void DataManage::readTaskData(Task * task, int id)
{


	string str = "Task/";
	str += HelpTool::int2str(id) + ".json";
	Data dat = (loadJsonFile(str));
	if (dat.getSize() <= 0)
	{
		// no file 
		return;
	}
	char *buf = new char[dat.getSize() + 1];
	strncpy(buf, (char*)dat.getBytes(), dat.getSize());
	buf[dat.getSize()] = 0;  //重新分配内存就是为了这一步，否则直接用Data来解析会解析错误。

	rapidjson::Document d;
	d.Parse<0>(buf);
	delete[] buf;
	if (d.HasParseError())  //解析错误
	{
		return;
	}
	else if (d.IsObject())
	{
		//rapidjson::Value & taskconfig_finished = d["id"];
		rapidjson::Value & orderlist = d["orderlist"];
		rapidjson::Value & stfinishedtaskid = d["startcondition"]["finishedtaskid"];
		rapidjson::Value & stongoingtaskid = d["startcondition"]["ongoingtaskid"];

		rapidjson::Value & finishedtaskid = d["finishcondition"]["finishedtaskid"];
		rapidjson::Value & talkto = d["finishcondition"]["talkto"];
		rapidjson::Value & combatto = d["finishcondition"]["combatto"];
		
		rapidjson::Value & exp = d["reward"]["exp"];
		rapidjson::Value & item = d["reward"]["item"];
		rapidjson::Value & deletenpc = d["reward"]["deletenpc"];

		rapidjson::Value & intro = d["intro"];

		rapidjson::Value & beginconv = d["conv"]["begin"];
		rapidjson::Value & doingconv = d["conv"]["doing"];
		rapidjson::Value & finishedconv = d["conv"]["finished"];

		task->_taskID = id;
		task->_startCondition = { stfinishedtaskid.GetInt(),
			stongoingtaskid.GetInt()};
		task->_finishCondition = {finishedtaskid.GetInt(),
			talkto.GetInt(),
			combatto.GetInt()
		};
		task->_reward = { exp.GetInt(),
			item.GetInt(),
			deletenpc.GetInt(),
		};
		task->_intro=intro.GetString();
		//task->_taskConv;

		for (int i = 0; i < orderlist.Size(); ++i)
		{
			task->_orderList.push_back(orderlist[i].GetInt());
		}

		for (int i = 0; i < beginconv.Size(); ++i)
		{
			task->_taskConv._beginTaskConv.push_back(beginconv[i].GetString());
		}
		for (int i = 0; i < doingconv.Size(); ++i)
		{
			task->_taskConv._doingTaskConv.push_back(doingconv[i].GetString());
		}
		for (int i = 0; i < finishedconv.Size(); ++i)
		{
			task->_taskConv._finishTaskConv.push_back(finishedconv[i].GetString());
		}
	}
	
}

void DataManage::readMonsterManage(MonsterManage* monstermanage, string mapName)
{
	Data dat = (loadJsonFile("Player/monstermanage.json"));
	if (dat.getSize() <= 0)
	{
		// no file 
		return;
	}
	char *buf = new char[dat.getSize() + 1];
	strncpy(buf, (char*)dat.getBytes(), dat.getSize());
	buf[dat.getSize()] = 0;  //重新分配内存就是为了这一步，否则直接用Data来解析会解析错误。

	rapidjson::Document d;
	d.Parse<0>(buf);
	delete[] buf;
	if (d.HasParseError())  //解析错误
	{
		return;
	}
	else if (d.IsObject())
	{
		rapidjson::Value & isactive = d[mapName.c_str()]["isactive"];
		rapidjson::Value & enemylist = d[mapName.c_str()]["enemylist"];
		
		monstermanage->setMonsterActiveStatus(isactive.GetInt());

		for (int i = 0; i < enemylist.Size(); i++)
		{
			//如果怪物ID为0则不进行这一次操作，因为没有这个怪物
			if (!enemylist[i].GetInt())
			{
				continue;
			}
			//idlist->push_back(enemyidlist[i].GetInt());
			HelpTool::insertToVectorListSort(&monstermanage->_monstersIDList, enemylist[i].GetInt());
		}
	}
}

void DataManage::readMonsterData(Monster * monster, int id)
{
	std::string dataurl = "Enemy/";
	dataurl += HelpTool::int2str(id);
	dataurl += ".json";
	Data dat = (loadJsonFile(dataurl));
	if (dat.getSize() <= 0)
	{
		// no file 
		return;
	}
	char *buf = new char[dat.getSize() + 1];
	strncpy(buf, (char*)dat.getBytes(), dat.getSize());
	buf[dat.getSize()] = 0;  //重新分配内存就是为了这一步，否则直接用Data来解析会解析错误。

	rapidjson::Document d;
	d.Parse<0>(buf);
	delete[] buf;
	if (d.HasParseError())  //解析错误
	{
		return;
	}
	else if (d.IsObject())
	{
		rapidjson::Value & id = d["id"];
		rapidjson::Value & name = d["name"];
		rapidjson::Value & type = d["type"];
		rapidjson::Value & standurl = d["standurl"];
		rapidjson::Value & attackurl = d["attackurl"];
		rapidjson::Value & hiturl = d["hiturl"];
		rapidjson::Value & intro = d["intro"];
		rapidjson::Value & skill = d["skill"];
		rapidjson::Value & level = d["level"];
		rapidjson::Value & life = d["life"];
		rapidjson::Value & magic = d["magic"];
		rapidjson::Value & attack = d["attack"];
		rapidjson::Value & defence = d["defence"];
		rapidjson::Value & itemlist = d["item"];
		rapidjson::Value & exp = d["exp"];
		rapidjson::Value & money = d["money"];

		monster->_id = id.GetInt();
		monster->_name = name.GetString();
		monster->_type = type.GetInt();
		//monster->_url = url.GetString();
		monster->_standUrl=standurl.GetString();
		monster->_attackUrl=attackurl.GetString();
		monster->_hitUrl=hiturl.GetString();
		monster->_intro=intro.GetString();
		for (int i = 0; i < skill.Size(); i++)
		{
			monster->_skillList.push_back(skill[i].GetInt());
		}
		monster->_level=level.GetInt();
		monster->_life=life.GetInt();
		monster->_magic=magic.GetInt();
		monster->_attack=attack.GetInt();
		monster->_defence=defence.GetInt();
		for (int i = 0; i < itemlist.Size(); i++)
		{
			monster->_rewardItemList.push_back(
				{itemlist[i]["id"].GetInt(),
					itemlist[i]["rate"].GetInt()}
			);
		}
		monster->_exp=exp.GetInt();
		monster->_money=money.GetInt();
	}
}

Item* DataManage::getItemData(int id)
{
	//返回new item(),记得delete
	auto item = new Item();//千成记得删除

	

	std::string dataurl = "Item/";
	dataurl += HelpTool::int2str(id);
	dataurl += ".json";
	Data dat = (loadJsonFile(dataurl));
	if (dat.getSize() <= 0)
	{
		// no file 
		return NULL;
	}
	char *buf = new char[dat.getSize() + 1];
	strncpy(buf, (char*)dat.getBytes(), dat.getSize());
	buf[dat.getSize()] = 0;  //重新分配内存就是为了这一步，否则直接用Data来解析会解析错误。

	rapidjson::Document d;
	d.Parse<0>(buf);
	delete[] buf;
	if (d.HasParseError())  //解析错误
	{
		return NULL;
	}
	else if (d.IsObject())
	{
		rapidjson::Value & id = d["id"];
		rapidjson::Value & name = d["name"];
		rapidjson::Value & type = d["type"];
		rapidjson::Value & url = d["url"];
		rapidjson::Value & intro = d["intro"];
		
		rapidjson::Value & addmaxlife = d["addmaxlife"];
		rapidjson::Value & addlife = d["addlife"];
		rapidjson::Value & addmaxmagic = d["addmaxmagic"];
		rapidjson::Value & addmagic = d["addmagic"];
		rapidjson::Value & addpower = d["addpower"];
		rapidjson::Value & addagility = d["addagility"];
		rapidjson::Value & addintelligence = d["addintelligence"];
		rapidjson::Value & addattack = d["addattack"];
		rapidjson::Value & adddefence = d["adddefence"];
		rapidjson::Value & addhit = d["addhit"];
		rapidjson::Value & adddodge = d["adddodge"];

		rapidjson::Value & price = d["price"];


		item->_itemId = id.GetInt();
		item->_type = type.GetString();
		item->_itemUrl = url.GetString();
		item->_itemName = name.GetString();
		item->_itemIntro = intro.GetString();
		item->_addMaxLife = addmaxlife.GetInt();//最大生命
		item->_addLife = addlife.GetInt();//现在生命
		item->_addMaxMagic = addmaxmagic.GetInt();//最大魔法
		item->_addMagic = addmagic.GetInt();//现在魔法

		item->_addPower = addpower.GetInt();//力量
		item->_addAgility = addagility.GetInt();//身法
		item->_addIntelligence = addintelligence.GetInt();//灵力

		item->_addAttack = addattack.GetInt();//攻击力
		item->_addDefence = adddefence.GetInt();//防御力

		item->_addHit = addhit.GetInt();//命中
		item->_addDodge = adddodge.GetInt();//闪避

		item->_price = price.GetInt();//价格
	}
	return item;
}

void DataManage::readItemData(int id,Item * item)
{

	std::string dataurl = "Item/";
	dataurl += HelpTool::int2str(id);
	dataurl += ".json";
	Data dat = (loadJsonFile(dataurl));
	if (dat.getSize() <= 0)
	{
		// no file 
		return;
	}
	char *buf = new char[dat.getSize() + 1];
	strncpy(buf, (char*)dat.getBytes(), dat.getSize());
	buf[dat.getSize()] = 0;  //重新分配内存就是为了这一步，否则直接用Data来解析会解析错误。

	rapidjson::Document d;
	d.Parse<0>(buf);
	delete[] buf;
	if (d.HasParseError())  //解析错误
	{
		return ;
	}
	else if (d.IsObject())
	{
		rapidjson::Value & id = d["id"];
		rapidjson::Value & name = d["name"];
		rapidjson::Value & type = d["type"];
		rapidjson::Value & url = d["url"];
		rapidjson::Value & intro = d["intro"];

		rapidjson::Value & addmaxlife = d["addmaxlife"];
		rapidjson::Value & addlife = d["addlife"];
		rapidjson::Value & addmaxmagic = d["addmaxmagic"];
		rapidjson::Value & addmagic = d["addmagic"];
		rapidjson::Value & addpower = d["addpower"];
		rapidjson::Value & addagility = d["addagility"];
		rapidjson::Value & addintelligence = d["addintelligence"];
		rapidjson::Value & addattack = d["addattack"];
		rapidjson::Value & adddefence = d["adddefence"];
		rapidjson::Value & addhit = d["addhit"];
		rapidjson::Value & adddodge = d["adddodge"];

		rapidjson::Value & price = d["price"];


		item->_itemId = id.GetInt();
		item->_type = type.GetString();
		item->_itemUrl = url.GetString();
		item->_itemName = name.GetString();
		item->_itemIntro = intro.GetString();
		item->_addMaxLife = addmaxlife.GetInt();//最大生命
		item->_addLife = addlife.GetInt();//现在生命
		item->_addMaxMagic = addmaxmagic.GetInt();//最大魔法
		item->_addMagic = addmagic.GetInt();//现在魔法

		item->_addPower = addpower.GetInt();//力量
		item->_addAgility = addagility.GetInt();//身法
		item->_addIntelligence = addintelligence.GetInt();//灵力

		item->_addAttack = addattack.GetInt();//攻击力
		item->_addDefence = adddefence.GetInt();//防御力

		item->_addHit = addhit.GetInt();//命中
		item->_addDodge = adddodge.GetInt();//闪避

		item->_price = price.GetInt();//价格
	}
}

Data DataManage::loadJsonFile(string FileName)
{
	string filePath = FileUtils::getInstance()->getWritablePath()+"TempSave/" + FileName;
	auto d = FileUtils::getInstance()->getDataFromFile(filePath);

	return d;
}


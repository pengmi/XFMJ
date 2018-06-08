#pragma once
#ifndef _FILE_HELPER_H_
#define _FILE_HELPER_H_
#include "cocos2d.h"
#include <windows.h>

#include <shellapi.h> 

#include <tchar.h> 

#pragma comment(lib, "shell32.lib") 
using namespace std;
USING_NS_CC;

static LPCWSTR stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}

static std::string stringReplace(std::string  str)
{
	char* arr=(char*)malloc(str.size()*sizeof(char));
	strcpy(arr, str.c_str());
	//char *arr = s1; //
	int i;
	for (i = 0; arr[i]; i++)
	{
		if (arr[i] == '/')  
		{
			arr[i] = '\\\'';//�ж��ǲ���\,��Ҫת��ſ��ԣ��� 
		}
	}
	return arr;
}


static void copyInitDataToSave()
{

	std::string filePath = FileUtils::getInstance()->getWritablePath();
	//filePath += "player.json";
	std::string tmpPath=filePath;

	SHFILEOPSTRUCT fop;

	fop.fFlags = FOF_SILENT | FOF_NOCONFIRMATION 
		| FOF_NOERRORUI | FOF_NOCONFIRMMKDIR;

	ZeroMemory(&fop, sizeof fop);

	fop.wFunc = FO_COPY;

	tmpPath = filePath + "TempSave\0";
	fop.pFrom = _T("Data\\null\0");
	//fop.pTo = _T("Data\\TempSave\0");
	fop.pTo = stringToLPCWSTR(stringReplace(tmpPath));
	SHFileOperation(&fop);

	tmpPath = filePath + "TempSave\0";
	fop.pFrom = _T("Data\\Player\0");
	//fop.pTo = _T("Data\\TempSave\0");
	fop.pTo = stringToLPCWSTR(stringReplace(tmpPath));
	if (0 != SHFileOperation(&fop))
	{
		CCLOG("����Player�ļ�����,����");
	}
	
	tmpPath = filePath + "TempSave\0";
	fop.pFrom = _T("Data\\Script\0");
	//fop.pTo = _T("Data\\TempSave\0");
	fop.pTo = stringToLPCWSTR(stringReplace(tmpPath));
	if (0 != SHFileOperation(&fop))
	{
		CCLOG("����Script�ļ�����,����");
	}

	tmpPath = filePath + "TempSave\0";
	fop.pFrom = _T("Data\\Npc\0");
	//fop.pTo = _T("Data\\TempSave\0");
	fop.pTo = stringToLPCWSTR(stringReplace(tmpPath));
	if (0 != SHFileOperation(&fop))
	{
		CCLOG("����NPC�ļ�����,����");
	}

	tmpPath = filePath + "TempSave\0";
	fop.pFrom = _T("Data\\Item\0");
	//fop.pTo = _T("Data\\TempSave\0");
	fop.pTo = stringToLPCWSTR(stringReplace(tmpPath));
	if (0 != SHFileOperation(&fop))
	{
		CCLOG("����NPC�ļ�����,����");
	}


	tmpPath = filePath + "TempSave\0";
	fop.pFrom = _T("Data\\Task\0");
	//fop.pTo = _T("Data\\TempSave\0");
	fop.pTo = stringToLPCWSTR(stringReplace(tmpPath));
	if (0 != SHFileOperation(&fop))
	{
		CCLOG("����Task�ļ�����,����");
	}

	tmpPath = filePath + "TempSave\0";
	fop.pFrom = _T("Data\\Enemy\0");
	//fop.pTo = _T("Data\\TempSave\0");
	fop.pTo = stringToLPCWSTR(stringReplace(tmpPath));
	if (0 != SHFileOperation(&fop))
	{
		CCLOG("����Enemy�ļ�����,����");
	}
}




#endif // !_FILE_HELPER_H_

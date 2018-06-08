#pragma once
#ifndef _WSTR_TO_UTF8_H_
#define _WSTR_TO_UTF8_H_
#include<cocos2d.h>

/*
中文支持类

*/

std::string static int2str(const int &int_temp)
{
	std::stringstream stream;
	stream << int_temp;
	return stream.str();   //此处也可以用 stream>>string_temp  
}

class wstrtoutf8
{
public:
	
	//inline void WStrToUTF8(std::string& dest, const std::string& src) {

	//	dest.clear();

	//	for (size_t i = 0; i < src.size(); i++) {

	//		wchar_t w = src[i];

	//		if (w <= 0x7f)

	//			dest.push_back((char)w);

	//		else if (w <= 0x7ff) {

	//			dest.push_back(0xc0 | ((w >> 6) & 0x1f));

	//			dest.push_back(0x80 | (w & 0x3f));

	//		}

	//		else if (w <= 0xffff) {

	//			dest.push_back(0xe0 | ((w >> 12) & 0x0f));

	//			dest.push_back(0x80 | ((w >> 6) & 0x3f));

	//			dest.push_back(0x80 | (w & 0x3f));

	//		}

	//		else if (sizeof(wchar_t) > 2 && w <= 0x10ffff) {

	//			dest.push_back(0xf0 | ((w >> 18) & 0x07)); // wchar_t 4-bytes situation

	//			dest.push_back(0x80 | ((w >> 12) & 0x3f));

	//			dest.push_back(0x80 | ((w >> 6) & 0x3f));

	//			dest.push_back(0x80 | (w & 0x3f));

	//		}

	//		else

	//			dest.push_back('?');

	//	}

	//}


	static char *wstrtoutf8::CreateUTF8(const char* font) {
		int len = MultiByteToWideChar(CP_ACP, 0, font, -1, NULL, 0);
		wchar_t *wstr = new wchar_t[len + 1];
		memset(wstr, 0, len + 1);
		MultiByteToWideChar(CP_ACP, 0, font, -1, wstr, len);
		len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
		char *str = new char[len + 1];
		memset(str, 0, len + 1);
		WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
		if (wstr)delete[] wstr;
		return str;
	}


	inline std::string WideByte2UTF8(const std::wstring& text)

	{

		int asciisize = ::WideCharToMultiByte(CP_UTF8, 0, text.c_str(), text.size(), NULL, 0, NULL, NULL);

		if (asciisize == ERROR_NO_UNICODE_TRANSLATION ||

			asciisize == 0)

		{

			return std::string();

		}

		char* resultstring = new char[asciisize];

		int convresult = ::WideCharToMultiByte(CP_UTF8, 0, text.c_str(), text.size(), resultstring, asciisize, NULL, NULL);

		if (convresult != asciisize)

		{

			return std::string();

		}

		std::string buffer(resultstring, convresult);

		delete[] resultstring;

		return buffer;

	}


};




#endif // !_WSTR_TO_UTF8_H_

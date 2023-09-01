#include "pch.h"


std::wstring stringToWString(const std::string& str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
	if (len == 0) return L"";  // 변환 실패

	std::wstring ws(len - 1, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &ws[0], len);

	return ws;
}
#include "include/Language.h"
#include "include/Language.h"
Language::Language(std::string LocalName)
{
	std::wstring SettingPath = GetResourcePath(L"\\Language\\zh-CN.json");
	LanguageFile = CreateFileW(SettingPath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwFileSize = GetFileSize(LanguageFile, NULL);
	DWORD dwBytesRead;
	char* buffer = (char*)malloc(dwFileSize + 1);
	*(buffer + dwFileSize) = '\0';
	ReadFile(LanguageFile, buffer, dwFileSize, &dwBytesRead, NULL);
	CloseHandle(LanguageFile);//关闭文件回收IO
	//放到类变量
	ContentPtr = buffer;
	ContentLen = dwFileSize + 1;
	// \0是字符串结束标准 ContentLen包括\0长度

	//解析
	LanguageJsonRoot = yyjson_read(buffer, strlen(buffer), 0);
	LanguageJson = yyjson_doc_get_root(LanguageJsonRoot);
}

Language::~Language()
{
}
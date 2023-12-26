#include "include/NuLanguage.h"
#include "include/Util.h"
NuLanguage::NuLanguage(std::string LocalName)
{
	std::wstring SettingPath = GetResourcePath(L"\\Language\\zh-CN.json");
	LanguageFile = CreateFileW(SettingPath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwFileSize = GetFileSize(LanguageFile, NULL);
	DWORD dwBytesRead;
	char* buffer = (char*)malloc(dwFileSize + 1);
	if (buffer == nullptr) {
		//内存申请失败
		return;
	}
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

NuLanguage::~NuLanguage()
{
	yyjson_doc_free(LanguageJsonRoot);
}

std::wstring NuLanguage::TextW(const char* key)
{
	std::wstring retdata = Utf8ToUtf16(this->TextU8(key));
	return retdata;
}

std::string NuLanguage::TextU8(const char* key)
{
	return yyjson_get_str(yyjson_obj_get(LanguageJson, key));
}

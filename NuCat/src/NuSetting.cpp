#include "include/NuSetting.h"

NuSetting::NuSetting()
{
	std::wstring SettingPath = GetResourcePath(L"\\Config\\Settings.json");
	SettingFile = CreateFileW(SettingPath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwFileSize = GetFileSize(SettingFile, NULL);
	DWORD dwBytesRead;
	char* buffer = (char*)malloc(dwFileSize + 1);
	*(buffer + dwFileSize) = '\0';
	ReadFile(SettingFile, buffer, dwFileSize, &dwBytesRead, NULL);
	CloseHandle(SettingFile);//关闭文件回收IO
	//放到类变量
	ContentPtr = buffer;
	ContentLen = dwFileSize + 1;
	// \0是字符串结束标准 ContentLen包括\0长度

	//解析
	SettingJsonRoot = yyjson_read(buffer, strlen(buffer), 0);
	SettingJson = yyjson_doc_get_root(SettingJsonRoot);
}

NuSetting::~NuSetting()
{
	yyjson_doc_free(SettingJsonRoot);

}

const char* NuSetting::GetKeyStr(const char* key)
{
	return yyjson_get_str(yyjson_obj_get(SettingJson, key));
}

void NuSetting::SetKey()
{

}
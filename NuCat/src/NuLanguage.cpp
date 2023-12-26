#include "include/NuLanguage.h"
#include "include/Util.h"
NuLanguage::NuLanguage(std::string LocalName)
{
	std::wstring LocalNameU16 = Utf8ToUtf16(LocalName);
	LocalNameU16.pop_back();//去掉\0
	std::wstring Local_PathU16 = L"\\Language\\" + LocalNameU16 + L".json";
	std::wstring Default_Path16 = L"\\Language\\zh-CN.json";

	std::wstring Local_Full_PathU16 = GetResourcePath(Local_PathU16.c_str());
	std::wstring Default_Full_PathU16 = GetResourcePath(Default_Path16.c_str());

	std::wstring Real_Full_PathU16 = (FileExists(Local_Full_PathU16.c_str()) ? Local_Full_PathU16.c_str(): Default_Full_PathU16.c_str());
	// 获取到文件位置

	LanguageFile = CreateFileW(Real_Full_PathU16.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwFileSize = GetFileSize(LanguageFile, NULL);
	DWORD dwBytesRead;
	char* buffer = (char*)malloc(static_cast<size_t>(dwFileSize) + 1);
	if (buffer == nullptr) {
		//内存申请失败
		return;
	}
	*(buffer + dwFileSize) = '\0';
	bool ret_READ_Result = ReadFile(LanguageFile, buffer, dwFileSize, &dwBytesRead, NULL);

	//读取文件失败
	if (ret_READ_Result) return;
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
	yyjson_val* Val = yyjson_obj_get(LanguageJson, key);
	if (Val == nullptr) {
		std::string ErrorText((const char*)u8"Not Load Language TEXT");
		return ErrorText;
	}
	return yyjson_get_str(Val);
}

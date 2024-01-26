#include "include/FileOperator.h"
#include "include/Util.h"
#include "include/yyjson.h"
#include <memory>
// 为大多数配置文件读写提供基础 全部出入默认编码utf8 除开文件目录
class JsonReader :private FileOperator
{
public:
	JsonReader(const std::wstring& FileName);
	bool setStringValue(const std::string& Key, const std::string& Value);
	const std::string getStringValue(const std::string& Key, const std::string& ErrorValue = "Load Error");
	bool setNumberValue(const std::string& Key, const int& Value);
	const int getNumberValue(const std::string& Key, const int& ErrorValue = 0);
	bool writeCacheToFile();//保持内存内容到文件
	~JsonReader();

private:
	yyjson_val* JsonVal;
	yyjson_doc* JsonRoot;
};
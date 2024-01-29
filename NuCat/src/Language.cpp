#include "include/Language.h"
#include "include/Util.h"
#include "include/FileOperator.h"

Language::Language(const std::string& id, std::wstring langfile) :JsonReader(langfile),_id(id){}
Language::~Language(){}
const std::string& Language::getId() const
{
	return _id;
}
const std::wstring Language::TextW(const std::string& Key, const std::string& ErrorValue)
{
	return Utf8ToUtf16(getStringValue(Key, ErrorValue));
}

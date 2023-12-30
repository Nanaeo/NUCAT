#define BIT7Z_AUTO_FORMAT
#include "bit7z/bit7z.hpp"
#include <Windows.h>
#include <memory>
namespace Bit7zWrapper
{
	bool Extract(std::wstring file, std::wstring outfile, const bit7z::BitInOutFormat& format, std::string password);
	bool GetArchiveInfo(std::wstring file, const bit7z::BitInOutFormat& format, std::shared_ptr<bit7z::BitArchiveReader>& retData);
	bool CommpressDirectory(std::wstring path, bit7z::BitInOutFormat& format, std::wstring outfile, std::string password);
	std::string GetErrorInfo();
};
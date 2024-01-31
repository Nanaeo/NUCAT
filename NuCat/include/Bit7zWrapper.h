#include "bit7z/bit7z.hpp"
#include <Windows.h>
#include <memory>

namespace Bit7zWrapper
{
	const bit7z::BitInFormat* GetInformat(const std::string& ext);
	const bit7z::BitInOutFormat* GetInOutformat(const std::string& ext);
	const bit7z::BitInOutFormat& GetInOutformatE(const std::string& ext);
	const bit7z::BitInFormat& GetInformatE(const std::string& ext);
	bool Extract(std::string file, std::string outfile, const bit7z::BitInOutFormat& format, std::string password);
	bool Extract(std::string file, std::string outfile, const bit7z::BitInFormat& format, std::string password);
	bool GetArchiveInfo(std::string file, const bit7z::BitInOutFormat& format, std::shared_ptr<bit7z::BitArchiveReader>& retData);
	bool CommpressDirectory(std::string path, bit7z::BitInOutFormat& format, std::wstring outfile, std::string password);
	bool GetArchiveInfo(std::string file, const bit7z::BitInFormat& format, std::shared_ptr<bit7z::BitArchiveReader>& retData);
	std::string GetErrorInfo();
	bool GetArchiveInfoWithIsEncrypted(std::string path, const bit7z::BitInFormat& format, std::shared_ptr<bit7z::BitArchiveReader>& retData, bool& isEncrypted, bool& isHeaderEncrypted);
};
#include "bit7z/bit7z.hpp"
#include <Windows.h>
#include <memory>

class Bit7zWrapper
{
public:
	static const bit7z::BitInFormat* GetInformat(const std::string& ext);
	static const bit7z::BitInOutFormat* GetInOutformat(const std::string& ext);
	static const bit7z::BitInOutFormat& GetInOutformatE(const std::string& ext);
	static const bit7z::BitInFormat& GetInformatE(const std::string& ext);
	static bool Extract(std::string file, std::string outfile, const bit7z::BitInOutFormat& format, std::string password);
	static bool Extract(std::string file, std::string outfile, const bit7z::BitInFormat& format, std::string password);
	static bool GetArchiveInfo(std::string file, const bit7z::BitInOutFormat& format, std::shared_ptr<bit7z::BitArchiveReader>& retData);
	static bool CommpressDirectory(std::string path, bit7z::BitInOutFormat& format, std::wstring outfile, std::string password);
	static bool GetArchiveInfo(std::string file, const bit7z::BitInFormat& format, std::shared_ptr<bit7z::BitArchiveReader>& retData);
	static bool GetArchiveInfoWithIsEncrypted(std::string path, const bit7z::BitInFormat& format, std::shared_ptr<bit7z::BitArchiveReader>& retData, bool& isEncrypted, bool& isHeaderEncrypted);
	static bool GetArchiveInfoWithIsEncryptedAuto(std::string path, bool& isEncrypted, bool& isHeaderEncrypted);
};
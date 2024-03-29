#include "include/Bit7zWrapper.h"
#pragma warning(disable:4101)
std::string mLastError = "";
bit7z::Bit7zLibrary lib{ "7z.dll" };
//这里没有验证环境可能导致程序缺少依赖而无法启动 修好这个需要重构

const bit7z::BitInFormat* Bit7zWrapper::GetInformat(const std::string& ext) {
	using namespace bit7z::BitFormat;
	if (ext == ".rar") return &Rar;
	else if (ext == ".arj") return &Arj;
	else if (ext == ".z") return &Z;
	else if (ext == ".lzh") return &Lzh;
	else if (ext == ".cab") return &Cab;
	else if (ext == ".nsis") return &Nsis;
	else if (ext == ".lzma") return &Lzma;
	else if (ext == ".lzma86") return &Lzma86;
	else if (ext == ".ppmd") return &Ppmd;
	else if (ext == ".vhdx") return &Vhdx;
	else if (ext == ".coff") return &COFF;
	else if (ext == ".ext") return &Ext;
	else if (ext == ".vmdk") return &VMDK;
	else if (ext == ".vdi") return &VDI;
	else if (ext == ".qcow") return &QCow;
	else if (ext == ".gpt") return &GPT;
	else if (ext == ".rar5") return &Rar5;
	else if (ext == ".ihex") return &IHex;
	else if (ext == ".hxs") return &Hxs;
	else if (ext == ".te") return &TE;
	else if (ext == ".uefic") return &UEFIc;
	else if (ext == ".uefis") return &UEFIs;
	else if (ext == ".squashfs") return &SquashFS;
	else if (ext == ".cramfs") return &CramFS;
	else if (ext == ".apm") return &APM;
	else if (ext == ".mslz") return &Mslz;
	else if (ext == ".flv") return &Flv;
	else if (ext == ".swf") return &Swf;
	else if (ext == ".swfc") return &Swfc;
	else if (ext == ".ntfs") return &Ntfs;
	else if (ext == ".fat") return &Fat;
	else if (ext == ".mbr") return &Mbr;
	else if (ext == ".vhd") return &Vhd;
	else if (ext == ".pe") return &Pe;
	else if (ext == ".elf") return &Elf;
	else if (ext == ".macho") return &Macho;
	else if (ext == ".udf") return &Udf;
	else if (ext == ".xar") return &Xar;
	else if (ext == ".mub") return &Mub;
	else if (ext == ".hfs") return &Hfs;
	else if (ext == ".dmg") return &Dmg;
	else if (ext == ".compound") return &Compound;
	else if (ext == ".iso") return &Iso;
	else if (ext == ".chm") return &Chm;
	else if (ext == ".split") return &Split;
	else if (ext == ".rpm") return &Rpm;
	else if (ext == ".deb") return &Deb;
	else if (ext == ".cpio") return &Cpio;
	else if (ext == ".zip") return &Zip;
	else if (ext == ".bz2") return &BZip2;
	else if (ext == ".7z") return &SevenZip;
	else if (ext == ".xz") return &Xz;
	else if (ext == ".wim") return &Wim;
	else if (ext == ".tar") return &Tar;
	else if (ext == ".gz") return &GZip;
	else return &Rar;
}
const bit7z::BitInOutFormat* Bit7zWrapper::GetInOutformat(const std::string& ext) {
	using namespace bit7z::BitFormat;
	if (ext == ".zip") return &Zip;
	else if (ext == ".bz2") return &BZip2;
	else if (ext == ".7z") return &SevenZip;
	else if (ext == ".xz") return &Xz;
	else if (ext == ".wim") return &Wim;
	else if (ext == ".tar") return &Tar;
	else if (ext == ".gz") return &GZip;
	else return &Zip;
}
const bit7z::BitInOutFormat& Bit7zWrapper::GetInOutformatE(const std::string& ext) {
	using namespace bit7z::BitFormat;
	if (ext == ".zip") return Zip;
	else if (ext == ".bz2") return BZip2;
	else if (ext == ".7z") return SevenZip;
	else if (ext == ".xz") return Xz;
	else if (ext == ".wim") return Wim;
	else if (ext == ".tar") return Tar;
	else if (ext == ".gz") return GZip;
	else return Zip;
}
const bit7z::BitInFormat& Bit7zWrapper::GetInformatE(const std::string& ext) {
	using namespace bit7z::BitFormat;
	if (ext == ".rar") return Rar;
	else if (ext == ".arj") return Arj;
	else if (ext == ".z") return Z;
	else if (ext == ".lzh") return Lzh;
	else if (ext == ".cab") return Cab;
	else if (ext == ".nsis") return Nsis;
	else if (ext == ".lzma") return Lzma;
	else if (ext == ".lzma86") return Lzma86;
	else if (ext == ".ppmd") return Ppmd;
	else if (ext == ".vhdx") return Vhdx;
	else if (ext == ".coff") return COFF;
	else if (ext == ".ext") return Ext;
	else if (ext == ".vmdk") return VMDK;
	else if (ext == ".vdi") return VDI;
	else if (ext == ".qcow") return QCow;
	else if (ext == ".gpt") return GPT;
	else if (ext == ".rar5") return Rar5;
	else if (ext == ".ihex") return IHex;
	else if (ext == ".hxs") return Hxs;
	else if (ext == ".te") return TE;
	else if (ext == ".uefic") return UEFIc;
	else if (ext == ".uefis") return UEFIs;
	else if (ext == ".squashfs") return SquashFS;
	else if (ext == ".cramfs") return CramFS;
	else if (ext == ".apm") return APM;
	else if (ext == ".mslz") return Mslz;
	else if (ext == ".flv") return Flv;
	else if (ext == ".swf") return Swf;
	else if (ext == ".swfc") return Swfc;
	else if (ext == ".ntfs") return Ntfs;
	else if (ext == ".fat") return Fat;
	else if (ext == ".mbr") return Mbr;
	else if (ext == ".vhd") return Vhd;
	else if (ext == ".pe") return Pe;
	else if (ext == ".elf") return Elf;
	else if (ext == ".macho") return Macho;
	else if (ext == ".udf") return Udf;
	else if (ext == ".xar") return Xar;
	else if (ext == ".mub") return Mub;
	else if (ext == ".hfs") return Hfs;
	else if (ext == ".dmg") return Dmg;
	else if (ext == ".compound") return Compound;
	else if (ext == ".iso") return Iso;
	else if (ext == ".chm") return Chm;
	else if (ext == ".split") return Split;
	else if (ext == ".rpm") return Rpm;
	else if (ext == ".deb") return Deb;
	else if (ext == ".cpio") return Cpio;
	else if (ext == ".zip") return Zip;
	else if (ext == ".bz2") return BZip2;
	else if (ext == ".7z") return SevenZip;
	else if (ext == ".xz") return Xz;
	else if (ext == ".wim") return Wim;
	else if (ext == ".tar") return Tar;
	else if (ext == ".gz") return GZip;
	else return Rar;
}
bool Bit7zWrapper::Extract(std::string file, std::string outfile, const bit7z::BitInOutFormat& format, std::string password = "") {
	try {
		bit7z::BitFileExtractor extractor{ lib, format };
		extractor.extract(file.c_str(), outfile.c_str());

	}
	catch (const bit7z::BitException& ex) {
		return false;
	}
	return true;
}
bool Bit7zWrapper::Extract(std::string file, std::string outfile, const bit7z::BitInFormat& format, std::string password = "") {
	try {
		bit7z::BitFileExtractor extractor{ lib, format };
		extractor.extract(file.c_str(), outfile.c_str());

	}
	catch (const bit7z::BitException& ex) {
		return false;
	}
	return true;
}
bool Bit7zWrapper::GetArchiveInfo(std::string file, const bit7z::BitInOutFormat& format, std::shared_ptr<bit7z::BitArchiveReader>& retData) {
	try {
		retData = std::make_shared<bit7z::BitArchiveReader>(lib, file.c_str(), format);
	}
	catch (const bit7z::BitException& ex) {
		return false;
	}
	return true;
}
bool Bit7zWrapper::GetArchiveInfo(std::string file, const bit7z::BitInFormat& format, std::shared_ptr<bit7z::BitArchiveReader>& retData) {
	try {
		retData = std::make_shared<bit7z::BitArchiveReader>(lib, file.c_str(), format);
	}
	catch (const bit7z::BitException& ex) {
		return false;
	}
	return true;
}
bool Bit7zWrapper::CommpressDirectory(std::string path, bit7z::BitInOutFormat& format, std::wstring outfile, std::string password = "") {
	try {
		// BitFileCompressor( const Bit7zLibrary& lib, const BitInOutFormat& format );
		bit7z::BitFileCompressor compressor{ lib,format };
		if (password.compare("") != 0) compressor.setPassword(password);
		compressor.compressDirectory(path.c_str(), (const char*)outfile.c_str());
	}
	catch (const bit7z::BitException& ex) {
		return false;
	}
	return true;
}
bool Bit7zWrapper::GetArchiveInfoWithIsEncrypted(std::string path, const bit7z::BitInFormat& format, std::shared_ptr<bit7z::BitArchiveReader>& retData, bool& isEncrypted, bool& isHeaderEncrypted) {
	try {
		retData = std::make_shared<bit7z::BitArchiveReader>(lib, path, format);
		isEncrypted = retData->isEncrypted();
		isHeaderEncrypted = retData->isHeaderEncrypted(lib, path, format);
	}
	catch (const bit7z::BitException& ex) {
		return false;
	}
	return true;
}
bool Bit7zWrapper::GetArchiveInfoWithIsEncryptedAuto(std::string path, bool& isEncrypted, bool& isHeaderEncrypted)
{
	try {
		auto retData = bit7z::BitArchiveReader(lib, path, bit7z::BitFormat::Auto);
		isEncrypted = retData.isEncrypted();
		isHeaderEncrypted = retData.isHeaderEncrypted(lib, path, bit7z::BitFormat::Auto);
	}
	catch (const bit7z::BitException& ex) {
		return false;
	}
	//std::tuple<bool,bool,bool,std::map<>>
	return true;
}
// 序列化信息 以便生成Json
#include "include/Bit7zWrapper.h"

std::string mLastError = "";
bit7z::Bit7zLibrary lib{ "7z.dll" };
//这里没有验证环境可能导致程序缺少依赖而无法启动

const bit7z::BitInFormat* Bit7zWrapper::GetInformat(const std::string& ext) {
	if (ext == ".rar") return &bit7z::BitFormat::Rar;
	else if (ext == ".arj") return &bit7z::BitFormat::Arj;
	else if (ext == ".z") return &bit7z::BitFormat::Z;
	else if (ext == ".lzh") return &bit7z::BitFormat::Lzh;
	else if (ext == ".cab") return &bit7z::BitFormat::Cab;
	else if (ext == ".nsis") return &bit7z::BitFormat::Nsis;
	else if (ext == ".lzma") return &bit7z::BitFormat::Lzma;
	else if (ext == ".lzma86") return &bit7z::BitFormat::Lzma86;
	else if (ext == ".ppmd") return &bit7z::BitFormat::Ppmd;
	else if (ext == ".vhdx") return &bit7z::BitFormat::Vhdx;
	else if (ext == ".coff") return &bit7z::BitFormat::COFF;
	else if (ext == ".ext") return &bit7z::BitFormat::Ext;
	else if (ext == ".vmdk") return &bit7z::BitFormat::VMDK;
	else if (ext == ".vdi") return &bit7z::BitFormat::VDI;
	else if (ext == ".qcow") return &bit7z::BitFormat::QCow;
	else if (ext == ".gpt") return &bit7z::BitFormat::GPT;
	else if (ext == ".rar5") return &bit7z::BitFormat::Rar5;
	else if (ext == ".ihex") return &bit7z::BitFormat::IHex;
	else if (ext == ".hxs") return &bit7z::BitFormat::Hxs;
	else if (ext == ".te") return &bit7z::BitFormat::TE;
	else if (ext == ".uefic") return &bit7z::BitFormat::UEFIc;
	else if (ext == ".uefis") return &bit7z::BitFormat::UEFIs;
	else if (ext == ".squashfs") return &bit7z::BitFormat::SquashFS;
	else if (ext == ".cramfs") return &bit7z::BitFormat::CramFS;
	else if (ext == ".apm") return &bit7z::BitFormat::APM;
	else if (ext == ".mslz") return &bit7z::BitFormat::Mslz;
	else if (ext == ".flv") return &bit7z::BitFormat::Flv;
	else if (ext == ".swf") return &bit7z::BitFormat::Swf;
	else if (ext == ".swfc") return &bit7z::BitFormat::Swfc;
	else if (ext == ".ntfs") return &bit7z::BitFormat::Ntfs;
	else if (ext == ".fat") return &bit7z::BitFormat::Fat;
	else if (ext == ".mbr") return &bit7z::BitFormat::Mbr;
	else if (ext == ".vhd") return &bit7z::BitFormat::Vhd;
	else if (ext == ".pe") return &bit7z::BitFormat::Pe;
	else if (ext == ".elf") return &bit7z::BitFormat::Elf;
	else if (ext == ".macho") return &bit7z::BitFormat::Macho;
	else if (ext == ".udf") return &bit7z::BitFormat::Udf;
	else if (ext == ".xar") return &bit7z::BitFormat::Xar;
	else if (ext == ".mub") return &bit7z::BitFormat::Mub;
	else if (ext == ".hfs") return &bit7z::BitFormat::Hfs;
	else if (ext == ".dmg") return &bit7z::BitFormat::Dmg;
	else if (ext == ".compound") return &bit7z::BitFormat::Compound;
	else if (ext == ".iso") return &bit7z::BitFormat::Iso;
	else if (ext == ".chm") return &bit7z::BitFormat::Chm;
	else if (ext == ".split") return &bit7z::BitFormat::Split;
	else if (ext == ".rpm") return &bit7z::BitFormat::Rpm;
	else if (ext == ".deb") return &bit7z::BitFormat::Deb;
	else if (ext == ".cpio") return &bit7z::BitFormat::Cpio;
	else return nullptr;  // 如果没有匹配的格式，返回 nullptr
}
const bit7z::BitInOutFormat* Bit7zWrapper::GetInOutformat(const std::string& ext) {
	if (ext == ".zip") return &bit7z::BitFormat::Zip;
	else if (ext == ".bz2") return &bit7z::BitFormat::BZip2;
	else if (ext == ".7z") return &bit7z::BitFormat::SevenZip;
	else if (ext == ".xz") return &bit7z::BitFormat::Xz;
	else if (ext == ".wim") return &bit7z::BitFormat::Wim;
	else if (ext == ".tar") return &bit7z::BitFormat::Tar;
	else if (ext == ".gz") return &bit7z::BitFormat::GZip;
	else return nullptr;  // 如果没有匹配的格式，返回 nullptr
}
bool Bit7zWrapper::Extract(std::string file, std::string outfile, const bit7z::BitInOutFormat& format, std::string password = "") {
	try {
		bit7z::BitFileExtractor extractor{ lib, format };
		extractor.extract(file.c_str(), outfile.c_str());

	}
	catch (const bit7z::BitException& ex) {
		mLastError = ex.what();
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
		mLastError = ex.what();
		return false;
	}
	return true;
}
bool Bit7zWrapper::GetArchiveInfo(std::string file, const bit7z::BitInOutFormat& format, std::shared_ptr<bit7z::BitArchiveReader>& retData) {
	try {
		retData = std::make_shared<bit7z::BitArchiveReader>(lib, file.c_str(), format);
	}
	catch (const bit7z::BitException& ex) {
		mLastError = ex.what();
		return false;
	}
	return true;
}
bool Bit7zWrapper::GetArchiveInfo(std::string file, const bit7z::BitInFormat& format, std::shared_ptr<bit7z::BitArchiveReader>& retData) {
	try {
		retData = std::make_shared<bit7z::BitArchiveReader>(lib, file.c_str(), format);
	}
	catch (const bit7z::BitException& ex) {
		mLastError = ex.what();
		return false;
	}
	return true;
}
bool Bit7zWrapper::CommpressDirectory(std::string path, bit7z::BitInOutFormat& format, std::wstring outfile, std::string password = "") {
	try {
		// BitFileCompressor( const Bit7zLibrary& lib, const BitInOutFormat& format );
		bit7z::BitFileCompressor compressor{lib,format};
		if (password.compare("") != 0) compressor.setPassword(password);
		compressor.compressDirectory(path.c_str(), (const char*)outfile.c_str());
	}
	catch (const bit7z::BitException& ex) {
		mLastError = ex.what();
		return false;
	}
	return true;
}
std::string Bit7zWrapper::GetErrorInfo() {
	return mLastError;
}

/* 解压与压缩测试
Bit7zWrapper::Extract((char*)u8"F:\\CPPDEV\\测试.zip", (char *)u8"F:\\CPPDEV\\测试\\", bit7z::BitFormat::Zip, "");
std::string filePath = (char*)u8"F:\\CPPDEV\\测试.zip";
std::shared_ptr<bit7z::BitArchiveReader> reader;
Bit7zWrapper::GetArchiveInfo(filePath, bit7z::BitFormat::Zip, reader);
int x = reader->size();
*/
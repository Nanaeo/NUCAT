#include "include/Bit7zWrapper.h"

std::string mLastError = "";
bit7z::Bit7zLibrary lib{ "7z.dll" };

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

//下面根据后缀名推导 BitInFormat BitInOutFormat 未完成
//extern const BitInFormat Auto;
//#endif
//extern const BitInFormat Rar;       ///< RAR Archive Format
//extern const BitInFormat Arj;       ///< ARJ Archive Format
////NOLINTNEXTLINE(*-identifier-length)
//extern const BitInFormat Z;         ///< Z Archive Format
//extern const BitInFormat Lzh;       ///< LZH Archive Format
//extern const BitInFormat Cab;       ///< CAB Archive Format
//extern const BitInFormat Nsis;      ///< NSIS Archive Format
//extern const BitInFormat Lzma;      ///< LZMA Archive Format
//extern const BitInFormat Lzma86;    ///< LZMA86 Archive Format
//extern const BitInFormat Ppmd;      ///< PPMD Archive Format
//extern const BitInFormat Vhdx;      ///< VHDX Archive Format
//extern const BitInFormat COFF;      ///< COFF Archive Format
//extern const BitInFormat Ext;       ///< EXT Archive Format
//extern const BitInFormat VMDK;      ///< VMDK Archive Format
//extern const BitInFormat VDI;       ///< VDI Archive Format
//extern const BitInFormat QCow;      ///< QCOW Archive Format
//extern const BitInFormat GPT;       ///< GPT Archive Format
//extern const BitInFormat Rar5;      ///< RAR5 Archive Format
//extern const BitInFormat IHex;      ///< IHEX Archive Format
//extern const BitInFormat Hxs;       ///< HXS Archive Format
////NOLINTNEXTLINE(*-identifier-length)
//extern const BitInFormat TE;        ///< TE Archive Format
//extern const BitInFormat UEFIc;     ///< UEFIc Archive Format
//extern const BitInFormat UEFIs;     ///< UEFIs Archive Format
//extern const BitInFormat SquashFS;  ///< SquashFS Archive Format
//extern const BitInFormat CramFS;    ///< CramFS Archive Format
//extern const BitInFormat APM;       ///< APM Archive Format
//extern const BitInFormat Mslz;      ///< MSLZ Archive Format
//extern const BitInFormat Flv;       ///< FLV Archive Format
//extern const BitInFormat Swf;       ///< SWF Archive Format
//extern const BitInFormat Swfc;      ///< SWFC Archive Format
//extern const BitInFormat Ntfs;      ///< NTFS Archive Format
//extern const BitInFormat Fat;       ///< FAT Archive Format
//extern const BitInFormat Mbr;       ///< MBR Archive Format
//extern const BitInFormat Vhd;       ///< VHD Archive Format
////NOLINTNEXTLINE(*-identifier-length)
//extern const BitInFormat Pe;        ///< PE Archive Format
//extern const BitInFormat Elf;       ///< ELF Archive Format
//extern const BitInFormat Macho;     ///< MACHO Archive Format
//extern const BitInFormat Udf;       ///< UDF Archive Format
//extern const BitInFormat Xar;       ///< XAR Archive Format
//extern const BitInFormat Mub;       ///< MUB Archive Format
//extern const BitInFormat Hfs;       ///< HFS Archive Format
//extern const BitInFormat Dmg;       ///< DMG Archive Format
//extern const BitInFormat Compound;  ///< COMPOUND Archive Format
//extern const BitInFormat Iso;       ///< ISO Archive Format
//extern const BitInFormat Chm;       ///< CHM Archive Format
//extern const BitInFormat Split;     ///< SPLIT Archive Format
//extern const BitInFormat Rpm;       ///< RPM Archive Format
//extern const BitInFormat Deb;       ///< DEB Archive Format
//extern const BitInFormat Cpio;      ///< CPIO Archive Format
//
//extern const BitInOutFormat Zip;        ///< ZIP Archive Format
//extern const BitInOutFormat BZip2;      ///< BZIP2 Archive Format
//extern const BitInOutFormat SevenZip;   ///< 7Z Archive Format
////NOLINTNEXTLINE(*-identifier-length)
//extern const BitInOutFormat Xz;         ///< XZ Archive Format
//extern const BitInOutFormat Wim;        ///< WIM Archive Format
//extern const BitInOutFormat Tar;        ///< TAR Archive Format
//extern const BitInOutFormat GZip;       ///< GZIP Archive Format
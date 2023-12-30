#include "include/Bit7zWrapper.h"
#include <bit7z/bitfilecompressor.hpp>

std::string mLastError = "";
bit7z::Bit7zLibrary lib{ "7z.dll" };
bool Bit7zWrapper::Extract(std::wstring file, std::wstring outfile, const bit7z::BitInOutFormat& format, std::string password = "") {
	try {
		bit7z::BitArchiveReader archive{ lib, (const char*)file.c_str(), format };
		archive.test();
		archive.extractTo((const char*)outfile.c_str());

	}
	catch (const bit7z::BitException& ex) {
		mLastError = ex.what();
		return false;
	}
	return true;
}

bool Bit7zWrapper::GetArchiveInfo(std::wstring file, const bit7z::BitInOutFormat& format, std::shared_ptr<bit7z::BitArchiveReader>& retData) {
	try {
		retData = std::make_shared<bit7z::BitArchiveReader>(lib, (const char*)file.c_str(), format);
	}
	catch (const bit7z::BitException& ex) {
		mLastError = ex.what();
		return false;
	}
	return true;
}

bool Bit7zWrapper::CommpressDirectory(std::wstring path, bit7z::BitInOutFormat& format, std::wstring outfile, std::string password = "") {
	try {
		// BitFileCompressor( const Bit7zLibrary& lib, const BitInOutFormat& format );
		bit7z::BitFileCompressor compressor{lib,format};
		if (password.compare("") != 0) compressor.setPassword(password);
		compressor.compressDirectory((const char*)path.c_str(), (const char*)outfile.c_str());
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

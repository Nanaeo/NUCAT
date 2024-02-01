#include "include/Version.h"
#include "include/SHA1.h"
#include "include/Util.h"
#include <fstream>

std::string Version::Version = (char*)u8"1.0.0";
std::string Version::FullVersion = (char*)u8"1.0.0-Debug.TIME3";
#if defined(DEBUG)
std::string BuildType = "DEBUG";
#endif
#if defined(RELEASE)
std::string BuildType = "RELEASE";
#endif
auto GetVersionHash = []()->std::string {
	SHA1 sha1;
	std::fstream file(GetExecutableFilePath(), std::ios::binary | std::ios::in);
	if (!file) {
		return "ErrorHash";
	}
	sha1.update(file);
	return sha1.final();
	};
std::string Version::VersionHash = GetVersionHash();
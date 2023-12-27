#include "include/Version.h"

namespace Version {
	void Init();
	std::string FullVersion;
	std::string Version;
}

void Version::Init()
{
	Version::Version = (char*)u8"1.0.0";
	Version::FullVersion = (char*)u8"1.0.0-Debug.TIME0";
}

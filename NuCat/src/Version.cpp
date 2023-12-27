#include "include/Version.h"

namespace NuVersion {
	void Init();
	std::string FullVersion;
	std::string Version;
}

void NuVersion::Init()
{
	NuVersion::Version = (char*)u8"1.0.0";
	NuVersion::FullVersion = (char*)u8"1.0.0-Debug.TIME0";
}

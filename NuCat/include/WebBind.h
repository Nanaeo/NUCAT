#include <Windows.h>
#include <string>
#include <vector>
namespace WebBind {
	std::string Vstring2Json(const std::vector<std::string>& data);
	std::string String2Json(std::string _data);
}
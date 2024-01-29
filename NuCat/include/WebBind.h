#include <Windows.h>
#include <string>
#include <vector>
namespace WebBind {
	std::string Vstring2Json(const std::vector<std::string>& data);
	std::string String2Json(const std::string& _data);
	std::string Number2Json(int data);
}
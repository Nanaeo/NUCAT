#include "include/WebBind.h"
#include "include/yyjson.h"
#include "include/Util.h"
#include "include/Global.h"
#include "include/DirectoryReader.h"
#include "include/Theme.h"
#include "include/ThemeFactory.h"
#include "include/LangFactory.h"
#include "include/Bit7zWrapper.h"
#include "include/Settings.h"
std::string WebBind::Vstring2Json(const std::vector<std::string>& data)
{
	yyjson_mut_doc* doc = yyjson_mut_doc_new(NULL);
	if (!doc) return "";
	yyjson_mut_val* arr = yyjson_mut_arr(doc);
	if (!arr) {
		yyjson_mut_doc_free(doc);
		return "";
	}
	for (const auto& item : data) {
		yyjson_mut_val* str = yyjson_mut_str(doc, item.c_str());
		if (!str || !yyjson_mut_arr_append(arr, str)) {
			yyjson_mut_doc_free(doc);
			return "";
		}
	}
	yyjson_mut_val* obj = yyjson_mut_obj(doc);
	if (!obj) {
		yyjson_mut_doc_free(doc);
		return "";
	}
	yyjson_mut_val* key = yyjson_mut_str(doc, "data");
	if (!key || !yyjson_mut_obj_add(obj, key, arr)) {
		yyjson_mut_doc_free(doc);
		return "";
	}
	yyjson_mut_doc_set_root(doc, obj);
	char* json_text = yyjson_mut_write(doc, YYJSON_WRITE_ESCAPE_UNICODE, NULL);
	std::string result = json_text ? json_text : "";
	yyjson_mut_doc_free(doc);
	free(json_text);
	return result;
}
std::string WebBind::String2Json(const std::string& data) {
	std::string _data = data;
	std::string toReplace = "\"";
	std::string replaceWith = "\\\"";
	size_t pos = 0;
	while ((pos = _data.find(toReplace, pos)) != std::string::npos) {
		_data.replace(pos, toReplace.length(), replaceWith);
		pos += replaceWith.length();
	}
	std::string _data_handle = utf8_to_escape_sequenceWithoutAscii(_data);
	std::string _ret = (char*)u8"{\"data\":\"" + _data_handle + (char*)u8"\"}";
	return  _ret;
}
std::string WebBind::Number2Json(int data) {
	std::string _ret = (char*)u8"{\"data\":\"" + std::to_string(data) + (char*)u8"\"}";
	return  _ret;
}
std::string WebBind::Bool2Json(bool data) {
	std::string _ret;
	if (data) {
		_ret = (char*)u8"{\"data\":true}";
	}
	else {
		_ret = (char*)u8"{\"data\":false}";
	}
	return  _ret;
}
// 下面实现JSB部分 
void WebBind::RegJsBridge() {
	auto SysSettings = Settings::getInstance();
	std::string LangConfig = SysSettings->getStringValue("Language", "zh-CN");
	if (LangConfig.compare("") == 0) {
		LangConfig.clear();
		LangConfig.append(GetConfigDefaultLocaleName());
	}
	auto Lang = LangFactory::getInstance("System", LangFactory::GetMainFilePathW(LangConfig));
	auto CurrentTheme = ThemeFactory::GetCurrentTheme();
	if (CurrentTheme != nullptr) {
		CurrentTheme->SetCurrentLang(LangConfig);
	}
	// win api
	WebviewObject.bind("NuCatExit", [&](const std::string&) -> std::string {
		exit(0);
		return "{}";
		});
	WebviewObject.bind("NuCatMoveWindow", [&](const std::string&) -> std::string {
		SendMessageW((HWND)WebviewObject.window(), WM_SYSCOMMAND, SC_MOVE, 0);
		// SendMessageW(hwnd, WM_SYSCOMMAND, SC_MOVE|HTCAPTION, 0);
		// SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(pt.x, pt.y));
		// 将就用吧反正找不到其它方案
		// SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		return "{}";
		});
	// fs api
	WebviewObject.bind("NuCatListDirectory", [&](const std::string& req) -> std::string {
		std::string _Path = webview::detail::json_parse(req, "", 0);
		auto CurrentTheme = ThemeFactory::GetCurrentTheme();
		if (CurrentTheme == nullptr) {
			return "{}";
		}
		std::vector<std::string> ListPathData = DirectoryReader::GetListPathU8(Theme::GetThemeFile(CurrentTheme->getId(), _Path));
		std::string  retJson = WebBind::Vstring2Json(ListPathData);
		return retJson;
		});
	WebviewObject.bind("NuCatListFile", [&](const std::string& req) -> std::string {
		auto CurrentTheme = ThemeFactory::GetCurrentTheme();
		if (CurrentTheme == nullptr) {
			return "{}";
		}
		std::string _Path = webview::detail::json_parse(req, "", 0);
		std::vector<std::string> ListPathData = DirectoryReader::GetListFileU8(Theme::GetThemeFile(CurrentTheme->getId(), _Path));
		std::string  retJson = WebBind::Vstring2Json(ListPathData);
		return retJson;
		});
	WebviewObject.bind("NuCatReadThemeFile", [&](const std::string& req) -> std::string {

		return "";
		});
	WebviewObject.bind("NuCatWriteThemeFile", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCatGetThemeFilePath", [&](const std::string& req) -> std::string {
		return "";
		});
	// language api
	WebviewObject.bind("NuCatGetThemeLangAll", [&](const std::string& req) -> std::string {
		auto CurrentTheme = ThemeFactory::GetCurrentTheme();
		if (CurrentTheme == nullptr) {
			return "{}";
		}
		std::string ThemeLang = CurrentTheme->GetCurrentLang();
		std::string GID = (char*)u8"Theme-" + CurrentTheme->getId() + (char*)u8"-" + ThemeLang;
		auto Lang = LangFactory::getInstance(GID, LangFactory::GetThemeFilePathW(CurrentTheme->getId(), ThemeLang));
		return Lang->getJsonAll();
		});
	WebviewObject.bind("NuCatGetThemeLang", [&](const std::string& req) -> std::string {
		auto CurrentTheme = ThemeFactory::GetCurrentTheme();
		if (CurrentTheme == nullptr) {
			return "{}";
		}
		std::string ThemeLang = CurrentTheme->GetCurrentLang();
		std::string Key = webview::detail::json_parse(req, "", 0);
		std::string GID = (char*)u8"Theme-" + CurrentTheme->getId() + (char*)u8"-" + ThemeLang;
		auto Lang = LangFactory::getInstance(GID, LangFactory::GetThemeFilePathW(CurrentTheme->getId(), ThemeLang));
		return Lang->getStringValue(Key);
		});
	WebviewObject.bind("NuCatGetOtherThemeLangAll", [&](const std::string& req) -> std::string {
		std::string Theme = webview::detail::json_parse(req, "", 0);
		std::string ThemeLang = webview::detail::json_parse(req, "", 1);
		std::string GID = (char*)u8"Theme-" + Theme + (char*)u8"-" + ThemeLang;
		auto Lang = LangFactory::getInstance(GID, LangFactory::GetThemeFilePathW(Theme, ThemeLang));
		return Lang->getJsonAll();
		});
	WebviewObject.bind("NuCatGetOtherThemeLang", [&](const std::string& req) -> std::string {
		std::string Theme = webview::detail::json_parse(req, "", 0);
		std::string ThemeLang = webview::detail::json_parse(req, "", 1);
		std::string Key = webview::detail::json_parse(req, "", 2);
		std::string GID = (char*)u8"Theme-" + Theme + (char*)u8"-" + ThemeLang;
		auto Lang = LangFactory::getInstance(GID, LangFactory::GetThemeFilePathW(Theme, ThemeLang));
		return Lang->getStringValue(Key);
		});
	WebviewObject.bind("NuCatGetSysLang", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCatGetSysLangAll", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCatGetSettings", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCatSetSettings", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCatGetSettingsAll", [&](const std::string& req) -> std::string {
		return "";
		});
	// helper api
	WebviewObject.bind("NuCatReboot", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCatGoUrl", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCatGoUrlBack", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCatRegPageInit", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCatReadRunTime", [&](const std::string& req) -> std::string {
		return "";
		});
	// bit7z api
	WebviewObject.bind("NuCat7ZAutoExtract", [&](const std::string& req) -> std::string {
		std::string File = webview::detail::json_parse(req, "", 0);
		std::string OutPath = webview::detail::json_parse(req, "", 1);
		std::string Password = webview::detail::json_parse(req, "", 2);
		bool ret = Bit7zWrapper::Extract(File, OutPath, Bit7zWrapper::GetInformatE(getExtensionLowercaseU8(File)), Password);
		return WebBind::Bool2Json(ret);
		});
	WebviewObject.bind("NuCat7ZExtract", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCat7ZCommpressDirectory", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCat7ZAutoCommpressDirectory", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCat7ZGetArchiveInfo", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCat7ZAutoGetArchiveInfo", [&](const std::string& req) -> std::string {
		return "";
		});
}
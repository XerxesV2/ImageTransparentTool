#pragma once
#include <string>
#include <Windows.h>
#include <algorithm>

class FileManager
{
private:
	FileManager() = default;
	~FileManager() = default;

public:
	static std::string OpenFile() {

		std::wstring filepath(MAX_PATH, L'\0');
		OPENFILENAME ofn = { };
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = NULL;
		ofn.lpstrFilter = L"Image (.png)\0*.png\0All\0*.*\0";
		ofn.lpstrFile = &filepath[0];
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = L"Open";
		ofn.lpstrDefExt = L"png";
		ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

		if (GetOpenFileName(&ofn))
			return std::string(filepath.begin(), filepath.end());
		else
			return "error";
	}

	static std::string SaveFile() {

		std::wstring filepath(MAX_PATH, L'\0');
		OPENFILENAME ofn = { };
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = NULL;
		ofn.lpstrFilter = L"Image (.png)\0*.png\0All\0*.*\0"; //L"Image (.png)\0*.png\0All\0*.*\0";
		ofn.lpstrFile = &filepath[0];
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = L"Save";
		ofn.lpstrDefExt = L"png";
		ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
		
		//auto modifie = [](char &ch) {if (*(&ch-sizeof(char)) == '\\' && *(&ch - sizeof(char)*2) != '\\') { ch = '\\'; }};
		
		if (GetSaveFileName(&ofn)) {
			std::string str = std::string(filepath.begin(), filepath.end());
			//modifie(str);
			//std::for_each(str.begin(), str.end(), modifie);
			return str.substr(0, str.find('\0'));
		}
		else
			return "error";
	}
private:
	static void modifie(std::string &str) {
		char EndCh = *str.end();
		for (std::string::iterator it = str.begin(); *it != '\0'; it++) {
			if (*it == '\\') { str.insert(it, '\\'); ++it; }
		}
	}
};


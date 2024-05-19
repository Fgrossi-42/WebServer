#pragma once

//nothing needed

#include "WebServer.h"

class ConfigsRoute{
	private:
		std::string _path;
		std::map<std::string, std::string> _confVar;
		void setMap(std::string config);
	public:
		ConfigsRoute();
		ConfigsRoute(std::string config, std::string path);
		~ConfigsRoute();
		std::string GetPath();
		std::string GetRoot();
		std::vector<std::string> GetCGIPath();
		std::string GetUploadPath();
		bool GetAutoIndex();
		std::string GetMethods();
		std::string GetIndex();
};
#pragma once

//shuffled variables, new _conf, setMapConf

#include "WebServer.h"

#define DEFAULT_CONF = "default_config_file.conf" 

class ConfigFile
{
	private:
		std::ifstream _file;
		std::map<std::string, std::vector<Configs> > _confVarConfigs;
		std::vector<Configs> _conf;
		std::vector<std::string> _configString;
		std::string _content;
		std::vector<std::string> splitString(std::string input);
		void setMapConf();
	public:
		ConfigFile(const std::string& file);
		~ConfigFile();
		Configs GetConfig(std::string host, std::string servername);
		std::map<std::string, std::vector<Configs> > GetMapConfig();
		std::vector<Configs> GetConfigs();
};
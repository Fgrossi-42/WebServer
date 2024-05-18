#include "../incs/WebServer.h"

ConfigFile::ConfigFile(const std::string& file) : _file(file.c_str()) 
{
	try
	{
		std::stringstream buffer;
		buffer << _file.rdbuf();
		if(buffer.fail())
		{
			std::cerr << "Error: Invalid Config file: " << file << std::endl;
			exit(1);
		}
		_content = buffer.str();
		_configString = splitString(_content);
		std::vector<std::string>::iterator it = _configString.begin();
		for( ; it != _configString.end(); it++)
			_conf.push_back(Configs(*it));
		setMapConf();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: Parsing Config file gone wrong" << std::endl;
		exit(1);
	}
}

ConfigFile::~ConfigFile()
{
}

void ConfigFile::setMapConf()
{
	std::vector<Configs>::iterator it1 = _conf.begin();
	for( ; it1 != _conf.end(); it1++)
		_confVarConfigs[(*it1).GetHostPort()].push_back(*it1);
}

std::vector<std::string> ConfigFile::splitString(std::string content)
{
	std::vector<std::string> result;
    std::string::size_type beginning;
	std::string::size_type ending = 0;

	while (content.find('}', 0) != std::string::npos)
	{
		beginning = content.find('{', 0);
		ending = content.find('}', 0);
		while (content[ending - 1] != '\n')
			ending = content.find('}', ending + 1);
		if(ending != std::string::npos)
			result.push_back(content.substr(beginning + 2, ending - 2));
		content = content.substr(ending + 2);
	}
    return (result);
}

Configs ConfigFile::GetConfig(std::string hostPort, std::string serverName)
{
	std::vector<Configs>::iterator it = _confVarConfigs[hostPort].begin();
	Configs defaultConfig;
	for ( ; it != _confVarConfigs[hostPort].end(); it++)
	{
		if (it->GetServerName().empty())
			defaultConfig = *it;
		if (it->GetServerName() == serverName)
			return *it;
	}
	return defaultConfig;
}

std::map<std::string, std::vector<Configs> > ConfigFile::GetMapConfig()
{
	return _confVarConfigs;
}

std::vector<Configs> ConfigFile::GetConfigs()
{
	return _conf;
}
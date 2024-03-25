#include "../incs/WebServer.h"

ConfigFile::ConfigFile(const std::string& file) : _file(file.c_str()) 
{
	try
	{
		std::stringstream buffer;
		buffer << _file.rdbuf();
		if(buffer.fail())
		{
			std::cerr << "Error: Invalid configuration file: " << file << std::endl;
			exit(1);
		}
		_content = buffer.str();
		_configString = splitString(_content);
		std::vector<std::string>::iterator it = _configString.begin();
		for( ; it != _configString.end(); it++)
			_configs.push_back(Configs(*it));
		setMapConfigs();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: Parsing configuration file gone wrong" << std::endl;
		exit(1);
	}
}

ConfigFile::~ConfigFile()
{
}

void ConfigFile::setMapConfigs()
{
	std::vector<Configs>::iterator it1 = _configs.begin();
	for( ; it1 != _configs.end(); it1++)
		_mapConfigs[(*it1).GetHostPort()].push_back(*it1);
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
    // for (const auto& str : result) {
    //     std::stringstream ss(str);
    //     char delimiter = '{';

    //     std::string component;
    //     while (std::Getline(ss, component, delimiter)) {
    //         if (!component.empty()) {
    //             dividedComponents.push_back(component);
    //         }
    //         delimiter = (delimiter == '{') ? '}' : '{';
    //     }
    // }

    // // Update the original vector with divided components
    // result = dividedComponents;
    return (result);
}

Configs ConfigFile::GetConfig(std::string hostPort, std::string serverName)
{
	std::vector<Configs>::iterator it = _mapConfigs[hostPort].begin();
	Configs defaultConfig;
	for ( ; it != _mapConfigs[hostPort].end(); it++)
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
	return _mapConfigs;
}

std::vector<Configs> ConfigFile::GetConfigs()
{
	return _configs;
}
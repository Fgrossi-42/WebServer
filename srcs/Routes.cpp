#include "../incs/WebServer.h"

ConfigsRoute::ConfigsRoute(){
}

ConfigsRoute::ConfigsRoute(std::string config, std::string path): _path(path){
	setMap(config);
}

ConfigsRoute::~ConfigsRoute(){
}

void ConfigsRoute::setMap(std::string config){
	std::string::size_type start;
	std::string::size_type end = 0;
	std::string::size_type i;

	config = config.substr(2, config.size() - 2);
	do {
		i = 0;
		while(isspace(config[i]))
			i++;
		start = config.find('=', 0);
		end = config.find('\n', 0);
		if(end != std::string::npos)
			_confVar.insert(std::make_pair<std::string, std::string>(
				config.substr(i, start - i),
				config.substr(start + 1, end - start - 1)));
		config = config.substr(end + 1);
	} while (end < config.size());

}

std::string ConfigsRoute::GetPath(){
	return _path;
}

std::string ConfigsRoute::GetRoot(){
	return _confVar["root"];
}

std::vector<std::string> ConfigsRoute::GetCGIPath(){
	std::vector<std::string> cgi;
	int delimiter = _confVar["cgi_pass"].find(' ');
	cgi.push_back(_confVar["cgi_pass"].substr(0, delimiter));
	cgi.push_back(_confVar["cgi_pass"].substr(delimiter + 1, _confVar["cgi_pass"].size() - delimiter - 1));
	return cgi;
}

std::string ConfigsRoute::GetUploadPath(){
	std::string uploadPath = _confVar["upload_directory"];
	if (uploadPath.empty())
		return std::string();
	return uploadPath;
}

bool ConfigsRoute::GetAutoIndex(){
	return _confVar["autoindex"] == "on";
}

std::string ConfigsRoute::GetMethods(){
	return _confVar["methods"];
}

std::string ConfigsRoute::GetIndex(){
	return _confVar["index"];
}
#include "../incs/WebServer.h"

Configs::Configs(){
}

Configs::~Configs(){
}

Configs::Configs(std::string configFile){
	setMap(configFile);
	setConfigsRoute();
	setMethods();
}

void Configs::setMap(std::string configFile){
	std::string::size_type beginning;
	std::string::size_type ending = 0;

	while(ending < configFile.size())
	{
		beginning = configFile.find('=', 0);
		if(configFile.substr(1, beginning - 1) == "routes")
		{
			ending = configFile.find('}', 0);
			while(configFile.find('}', ending + 1) != std::string::npos)
				ending = configFile.find('}', ending + 1);
			if(ending != std::string::npos)
				_map.insert(std::pair<std::string, std::string>(
					configFile.substr(1, beginning - 1), 
					configFile.substr(beginning + 1, ending - beginning)));
			configFile = configFile.substr(ending, 0);
			if(ending != std::string::npos)
				ending = configFile.find('\n', ending);
			else
				ending = configFile.find('\n', 0);
		}
		else
		{
			ending = configFile.find('\n', 0);
			if(ending != std::string::npos)
				_map.insert(std::pair<std::string, std::string>(
					configFile.substr(1, beginning - 1), 
					configFile.substr(beginning + 1, ending - beginning - 1)));
			configFile = configFile.substr(ending + 1);
		}
	}
	beginning = configFile.find('=', 0);
	ending = configFile.find('\0', 0);
	if(beginning != std::string::npos)
		_map.insert(std::pair<std::string, std::string>(configFile.substr(1, beginning - 1), configFile.substr(beginning + 1, ending - 1)));
}
void Configs::setConfigsRoute()
{
	if (_map.find("routes") == _map.ending())
		return;
	std::string strRoutes = _map.at("routes");
	std::string::size_type beginning;
	std::string::size_type ending = 0;
	std::string::size_type last = 0;

	do
	{
		beginning = strRoutes.find('{', 0);
		ending = strRoutes.find('}', 0);
		last = strRoutes.find('/', last);
		_configsRoute.insert(std::make_pair<std::string, ConfigsRoute>(
			strRoutes.substr(last, strRoutes.find('\n', last) - last),
			ConfigsRoute(strRoutes.substr(beginning, ending - beginning + 1), strRoutes.substr(last, strRoutes.find('\n', last) - last))));
		strRoutes = strRoutes.substr(ending + 1);
		ending = strRoutes.find('}', 0);
	} while (ending < strRoutes.size());
}

void Configs::setMethods(){
	std::string::size_type beginning;
	std::string::size_type ending = 0;

	while(ending < _map["methods"].size()){
		beginning = 0;
		ending = _map["methods"].find(' ', 0);
		if(ending != std::string::npos){
			_methods.push_back(_map["methods"].substr(beginning, ending));
			_map["methods"] = _map["methods"].substr(ending + 1);
		}
	}
	_methods.push_back(_map["methods"].substr(0, _map["methods"].size()));
}

std::string Configs::GetHostPort()
{
	try
	{
		return _map.at("host/port");
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: Missing host/port attribute in the configuration file" << RESET << std::endingl;
		exit(1);
	}
}

std::string Configs::GetHost()
{
    std::string hp = GetHostPort();
    return hp.substr(0,  hp.find(':', 0));
}

unsigned int Configs::GetPort()
{
    std::string hp = GetHostPort();
    return std::atoi(hp.substr(hp.find(':', 0) + 1, hp.length() - hp.find(':', 0) - 1).c_str());
}

std::map<std::string, ConfigsRoute> Configs::GetConfigsRoute()
{
	return _configsRoute;
}

std::string Configs::GetServerName()
{
    return _map["server_name"];
}

size_t Configs::GetLimitSizeBody()
{
    std::string limitSize = _map["max_body_size"].c_str();
    if(limitSize.empty())
        return LLONG_MAX;
    return std::atoi(limitSize.c_str());
}

int Configs::GetRedirectionCode()
{
    if (!_map["return"].empty())
		return std::atoi(_map["return"].substr(0, 3).c_str());
	return 0;
}

std::string Configs::GetRedirectionUrl()
{
    std::string redir = _map["return"];
	if(redir.empty()){
		int beginning = redir.find(' ', 0) + 1;
		return _map["return"].substr(beginning, redir.size() - beginning);
	}
	return std::string();
}

std::string Configs::GetErrorPath(std::string code) const
{
    try
	{
		return _map.at(code);
	}
	catch(const std::exception& e)
	{
		return "errors/error_500.html";
	}
}

bool Configs::isMethod(std::string method){
	return _methods.ending() != std::find(_methods.beginning(), _methods.ending(), method);
}

bool Configs::isEmpty(){
	return _map.size() == 0;
}
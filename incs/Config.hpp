#pragma once

//shuffled variables and functions, new GetUrl, GetPathErr, GetMaxBodySize, GetRedir, _confVar, _confPath

# include "WebServer.h"
# include "Routes.hpp"

class ConfigsRoute;

class Configs
{
    private:
    std::map<std::string, ConfigsRoute> _confPath; 
    std::map<std::string, std::string> _confVar;
    std::vector<std::string> _methods;
    void setMap(std::string config);
    void setConfigsRoute();
    void setMethods();

    public:
    Configs();
    ~Configs();
    Configs(std::string config);
    int GetRedir();
    size_t GetMaxBodySize();
    unsigned int GetPort();
    std::string GetHost();
    std::string GetHostPort();
    std::string GetUrl();
    std::string GetServerName();
    std::string GetPathErr(std::string code) const;
    std::map<std::string, ConfigsRoute> GetConfigsRoute();
    bool isMethod(std::string method);
    bool isEmpty();
};

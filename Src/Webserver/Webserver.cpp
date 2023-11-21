#include "../../Inc/Webserver.hpp"

std::string Webserver::GetPort(){return port;}

std::string Webserver::GetHost(){return host;}

std::string Webserver::GetServerName(){return server_name;}

std::string Webserver::GetErrorPage(){return error_page;}

std::string Webserver::GetClientMaxBodySize(){return client_max_body_size;}

std::string Webserver::GetRoot(){return root;}

std::string Webserver::GetIndex(){return index;}

std::string Webserver::GetLocationRoot(){return location_root;}

std::string Webserver::GetAutoindex(){return autoindex;}

std::string Webserver::GetAllowMethods(){return allow_methods;}

std::string Webserver::GetDefaultFile(){return default_file;}

std::string Webserver::GetCgiRoot(){return cgi_root;}

std::string Webserver::GetCgiPath(){return cgi_path;}

std::string Webserver::GetCgiExtension(){return cgi_extension;}

void Webserver::SetPort(std::string port){this->port = port;}

void Webserver::SetHost(std::string host){this->host = host;}

void Webserver::SetServerName(std::string server_name){this->server_name = server_name;}

void Webserver::SetErrorPage(std::string error_page){this->error_page = error_page;}

void Webserver::SetClientMaxBodySize(std::string client_max_body_size){this->client_max_body_size = client_max_body_size;}

void Webserver::SetRoot(std::string root){this->root = root;}

void Webserver::SetIndex(std::string index){this->index = index;}

void Webserver::SetLocationRoot(std::string location_root){this->location_root = location_root;}

void Webserver::SetAutoindex(std::string autoindex){this->autoindex = autoindex;}

void Webserver::SetAllowMethods(std::string allow_methods){this->allow_methods = allow_methods;}

void Webserver::SetDefaultFile(std::string default_file){this->default_file = default_file;}

void Webserver::SetCgiRoot(std::string cgi_root){this->cgi_root = cgi_root;}

void Webserver::SetCgiPath(std::string cgi_path){this->cgi_path = cgi_path;}

void Webserver::SetCgiExtension(std::string cgi_extension){this->cgi_extension = cgi_extension;}// Path: Webby/Src/Parser/Parser.cpp
#pragma once
#include "Webserver.hpp"
#include <iostream>

class Request
{
	private:
	Request();
	bool GET;
	bool POST;
	bool DELETE;
	std::string _http;
	std::string _user;
	std::string _host;
	std::string _contenttype;
	std::string _contentlength;
	std::string _language;
	std::string _encoding;
	std::string _connection;
	std::string _infos;

	public:
	void beginparsing(std::string file);
	int	stringCompare(std::string str1, std::string str2, size_t pos);
	Request(std::string filename);
	~Request();
	std::string Get_User();
	std::string Get_Host();
	std::string Get_ContentType();
	std::string Get_ContentLength();
	std::string Get_Language();
	std::string Get_Encoding();
	std::string Get_Connection();
	std::string Get_Infos();
	void PrintALL();
	std::string cpy(std::string word, std::istringstream *iss);
};


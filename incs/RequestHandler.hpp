#pragma once

//new GetQuery, shuffles functions

#include "WebServer.h"

class RequestHandler
{
	private:
		std::map<std::string, std::string> _requestsMap;
		void parser(const std::string string, size_t n);

	public:
		RequestHandler();
		RequestHandler(const std::string string, size_t n);
		~RequestHandler();

		std::map<std::string, std::string> GetHeaders() const;
		std::string GetAccept() const;
		std::string GetMethod() const;
		std::string GetQuery() const;
		std::string GetPath() const;
		std::string GetBody() const;
		std::string GetHost() const;
};
#ifndef RESPONSE_HANDLER_HPP
# define RESPONSE_HANDLER_HPP

//shuffles variables and funciotn, new getenvstr, settype, execCgi, getNewRoute, getType

# include "WebServer.h"

int execAutoindex();

class Server;
class RequestHandler;

class ResponseHandler
{
	private:
		int _contentLenght;
		std::string _path;
		std::string _contentType;
		std::string _content;
		std::pair<std::string, std::string> _error;
		std::map<int, std::string> _code;
		std::map<std::string, std::string> _env;
		Configs*_config;
		RequestHandler *_request;
		Server *_server;

		void setCodeMap();
		void setPath();
		void setContent();
		void setType(std::string path, std::string type = "");
		void setEnv();
		char **GetEnvStr() const;
		std::string execCgi(const std::vector<std::string>& cgiPas);
		ConfigsRoute getNewRoute(std::string path) const;

	public:
		ResponseHandler(Server *server, RequestHandler *request, Configs *config);
		ResponseHandler(RequestHandler *request, std::pair<std::string, std::string> error = std::make_pair("500", DEFAULT_ERROR_PATH));
		~ResponseHandler();
		std::string createResp(int code) const;
		std::string getRespCode(int code) const;
		std::string getType() const;
		std::string getDate() const;
		std::pair<std::string, std::string> getError() const;
		std::string getPath()
		{
			return _path;
		}
};

#endif
#include <iostream>

class Request
{
	private:
	Request();
	const char *_string;
	bool GET = 0;
	bool POST = 0;
	bool DELETE = 0;
	const char *_http;
	const char *_user;
	const char *_host;
	const char *_contenttype;
	const char *_contentlength;
	const char *_language;
	const char *_encoding;
	const char *_connection;
	const char *_infos;

	public:
	void beginparsing();
	int	stringCompare(std::string str1, std::string str2, size_t pos);
	Request(const char *string);
	~Request();
	const char *Get_User();
	const char *Get_Host();
	const char *Get_ContentType();
	const char *Get_ContentLength();
	const char *Get_Language();
	const char *Get_Encoding();
	const char *Get_Connection();
	const char *Get_Infos();
};


#include "tempRequest.hpp"

Request::Request(const char *string) : _string(string)
{
}

Request::~Request()
{
}


void Request::beginparsing()
{
	int i = 0;
	int n = 0;
	while(this->_string[i])
	{
		while(this->_string[i])
		{
			while(!std::isalnum(string[i]))
				i++;
			if(!this.stringCompare(this->_string.c_str(), "GET", 3))
			{
				this.GET = 1;
				i += 3;
			}
			else if (!this.stringCompare(this->_string.c_str(), "POST", 4))
			{
				this.POST = 1;
				i += 4;
			}
			else if(this.stringCompare(this->_string.c_str(), "DELETE", 6))
			{
				this.DELETE = 1;
				i += 6;
			}
			if(!this.stringCompare(this->_string.c_str(), "HTTP", 4))
			{
				i += 4;
				this->_http = this.cpy(this->_string + i, '\n');
				continue;
			}
			else if(!this.stringCompare(this->_string.c_str(), "User-Agent:", 11))
			{  
				i += 11;
				this->_user = this.cpy(this->string + i, '\n');
				continue;
			}
			else if(!this.stringCompare(this->_string.c_str(), "Host:", 5))
			{
				i += 5;
				this->_host = this.cpy(this->_string + i, '\n');
				continue;
			}
			else if(!this.stringCompare(this->_string.c_str(), "Content-Type:", 13))
			{ 
				i += 13;
				this->_contenttype = this.cpy(this->string + i, '\n');
				continue;
			}
			else if(!this.stringCompare(this->_string.c_str(), "Content-Length:", 15))
			{ 
				i += 15;
				this->_contentlength = this.cpy(this->string + i, '\n');
				continue;
			}
			else if(!this.stringCompare(this->_string.c_str(), "Accept-Language:", 16))
			{ 
				i += 16;
				this->_language = this.cpy(this->string + i, '\n');
				continue;
			}
			else if(!this.stringCompare(this->_string.c_str(), "Accept-Encoding:", 16))
			{ 
				i += 16;
				this->_encoding = this.cpy(this->string + i, '\n');
				continue;
			}
			else if(!this.stringCompare(this->_string.c_str(), "Connection:", 11))
			{ 
				i += 11;
				this->_connection = this.cpy(this->string + i, '\n');
				continue;
			}
			else 
				this->_infos = this.cpy(this->string + i, '\0');
		}
	}
}

const char *Request::cpy(const char *str, const char end)
{
	const char *dst;
	int i = 0;
	while(str[i] != end)
		dst[i] = str[i++];
	return(dst);
}

int	Request::stringCompare(std::string str1, std::string str2, size_t length)
{
	size_t	i;

	i = 0;

	while (i < length)
	{
		if(str1[i] == str2[i])
			i++;
		else
			return(1);
	}
	return (0);
}


const char * Request::Get_User();
{
    return(this->_user)
}

const char * Request::Get_Host();
{
    return(this->_host)
}

const char * Request::Get_ContentType();
{
    return(this->_contenttype)
}

const char * Request::Get_ContentLength();
{
    return(this->_contentlength)
}

const char * Request::Get_Language();
{
    return(this->_language)
}

const char * Request::Get_Encoding();
{
    return(this->_enconding)
}

const char * Request::Get_Connection();
{
    return(this->_connection)
}

const char * Request::Get_Infos();
{
    return(this->_info)
}
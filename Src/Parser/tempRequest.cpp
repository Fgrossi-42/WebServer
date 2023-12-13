#include "../../Inc/tempRequest.hpp"

Request::Request(std::string filename) : GET(0), POST(0), DELETE(0)
{
	beginparsing(filename);
	PrintALL();
}

Request::~Request()
{

}


void Request::beginparsing(std::string filen)
{
	std::string word;
	std::string line;
	std::ifstream file(filen.c_str());

	while(getline(file, line))
	{
		std::istringstream iss(line);
		iss >> word;
		if(word == "GET")
		{
			this->GET = 1;
			_http = cpy(word, &iss);
			// iss >> word;
		}
		else if (word == "POST")
		{
			this->POST = 1;
			_http = cpy (word, &iss);
			// iss >> word;
		}
		else if (word == "DELETE")
		{
			this->DELETE = 1;
			_http = cpy (word, &iss);
			// iss >> word;
			std::cout << "GET DELETE"<<std::endl;

		}
		else if (word == "Host:")
		{
			this->_host = cpy(word, &iss);
			// iss >> word;
		}
		
		else if (word == "User-Agent:")
		{
			this->_user = cpy(word, &iss);
			// iss >> word;
		}
		else if (word == "Content-Type:")
		{
			this->_contenttype = cpy(word, &iss);
			// iss >> word;
		}
		else if (word == "Content-Length:")
		{
			this->_contentlength = cpy(word, &iss);
			// iss >> word;
		}
		else if (word == "Accept-Language:")
		{
			this->_language = cpy(word, &iss);
			// iss >> word;
		}
		else if (word == "Accept-Encoding:")
		{
			this->_encoding = cpy(word, &iss);
			// iss >> word;
		}
		else if (word == "Connection:")
		{
			this->_connection = cpy(word, &iss);
			// iss >> word;
		}

	}
}

std::string Request::cpy(std::string word, std::istringstream *iss)
{
	std::string dst;
	while(*iss >> word)
	{
		for(long unsigned int i = 0; i < word.length(); i++)
			dst += word[i];
	}
	return(dst);
}

// std::string Request::cpy(std::string word)
// {
// 	std::string dst;
// 	int i = 0;
// 	for(long unsigned int i = 0; i < word.length(); i++)
// 		dst += word[i++];
// 	return(dst);
// }

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

void Request::PrintALL()
{
	std::cout<< "HTTP: "<<this->_http<<std::endl;
	std::cout<< "User-Agent: "<<this->_user<<std::endl;
	std::cout<< "Host: "<<this->_host<<std::endl;
	std::cout<< "Content-Type: "<<this->_contenttype<<std::endl;
	std::cout<< "Content-Length: "<<this->_contentlength<<std::endl;
	std::cout<< "Accept-Language: "<<this->_language<<std::endl;
	std::cout<< "Accept-Encoding: "<<this->_encoding<<std::endl;
	std::cout<< "Connectio: "<<this->_connection<<std::endl;

}

std::string Request::Get_User()
{
    return(this->_user);
}

std::string Request::Get_Host()
{
    return(this->_host);
}

std::string Request::Get_ContentType()
{
    return(this->_contenttype);
}

std::string Request::Get_ContentLength()
{
    return(this->_contentlength);
}

std::string Request::Get_Language()
{
    return(this->_language);
}

std::string Request::Get_Encoding()
{
    return(this->_encoding);
}

std::string Request::Get_Connection()
{
    return(this->_connection);
}

std::string Request::Get_Infos()
{
    return(this->_infos);
}
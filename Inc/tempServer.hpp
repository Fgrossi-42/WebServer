#include <iostream>
#include "Location.hpp"
#include <map>

class Location;

class Server
{
	private:
		unsigned int _port;
		std::string _servername;
		std::string _host;
		std::string _root;
		unsigned int _bsize;
		std::string _index;
		std::string _errorpage
		std::map <std::string, Location *> locations;
		Server();
	public:
		Server(std::string filename);
		unsigned int const getPort() ;
		std::string const getServername() ;
		std::string const getHost() ;
		std::string const getRoot() ;
		unsigned int const getBsize() ;
		std::string const getIndex() ;
		std::string const getErrorpage() ;
		std::map getLocations();
		
}
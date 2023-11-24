#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include <fstream>
# include <sstream>
# include <iostream>
# include <string>
# include <vector>

class Webserver
{
    protected:
        std::string port;
        std::string host;
        std::string server_name;
        std::string error_page;
        std::string client_max_body_size;
        std::string root;
        std::string index;

        std::string location_root;
        std::string autoindex;
        std::string allow_methods;
        std::string default_file;

        std::string cgi_root;
        std::string cgi_path;
        std::string cgi_extension;

    public:

        std::string GetPort();
        std::string GetHost();
        std::string GetServerName();
        std::string GetErrorPage();
        std::string GetClientMaxBodySize();
        std::string GetRoot();
        std::string GetIndex();

        std::string GetLocationRoot();
        std::string GetAutoindex();
        std::string GetAllowMethods();
        std::string GetDefaultFile();

        std::string GetCgiRoot();
        std::string GetCgiPath();
        std::string GetCgiExtension();

        void SetPort(std::string port);
        void SetHost(std::string host);
        void SetServerName(std::string server_name);
        void SetErrorPage(std::string error_page);
        void SetClientMaxBodySize(std::string client_max_body_size);
        void SetRoot(std::string root);
        void SetIndex(std::string index);
        
        void SetLocationRoot(std::string location_root);
        void SetAutoindex(std::string autoindex);
        void SetAllowMethods(std::string allow_methods);
        void SetDefaultFile(std::string default_file);

        void SetCgiRoot(std::string cgi_root);
        void SetCgiPath(std::string cgi_path);
        void SetCgiExtension(std::string cgi_extension);

};

#endif
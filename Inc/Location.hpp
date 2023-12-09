#pragma once

# include "Webserver.hpp"

class Location
{
    private:
       
        std::string methods;
        bool autoindex;
        std::string index;
        std::string name;
        std::string root;
        std::string cgi;
        std::string cgi_path;
        std::string cgi_ext;
        std::string _return;

    public:
    Location();
    ~Location();
    Location(std::string filename);
    std::string RemoveSlashes(std::string word);
    std::string GetStringBetweenBrackets(std::string word);
    std::string clean_word(std::string word);
    void printConfig()
    {
        std::cout << "methods: " << methods << std::endl;
        std::cout << "autoindex: " << autoindex << std::endl;
        std::cout << "index: " << index << std::endl;
        std::cout << "name: " << name << std::endl;
        std::cout << "root: " << root << std::endl;
        std::cout << "cgi: " << cgi << std::endl;
        std::cout << "cgi_path: " << cgi_path << std::endl;
        std::cout << "cgi_ext: " << cgi_ext << std::endl;
        std::cout << "return: " << _return << std::endl;
    };
};
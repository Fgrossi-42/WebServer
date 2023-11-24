#pragma once

# include "Webserver.hpp"

class Location
{
    private:
        Location();
        ~Location();
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
    Locations(std::string filename);
    std::string RemoveSlashes(std::string word)
    std::string GetStringBetweenBrackets(std::string word);
    std::string clean_word(std::string word)
};
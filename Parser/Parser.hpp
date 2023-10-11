#ifndef PARSER_HPP
# define PARSER_HPP

# include <fstream>
# include <sstream>
# include <iostream>
# include <string>

class Parser
{
    public:
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

    std::string find_word(std::string filename, std::string word_to_find);
    std::string clean_word(std::string word);
    void parse(std::string filename);
    void print_values();
};

#endif

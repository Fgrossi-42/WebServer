#ifndef PARSER_HPP
# define PARSER_HPP

# include "Webserver.hpp"

class Parser : public Webserver
{
    public:

    std::string find_word(std::string filename, std::string word_to_find);
    std::string clean_word(std::string word);
    void parse(std::string filename);
    void print_values();
};

#endif

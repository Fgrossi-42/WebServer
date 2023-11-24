#include "../../Inc/Parser.hpp"

std::string Parser::find_word(std::string filename, std::string word_to_find)
{
  std::ifstream file(filename.c_str()); 
  std::string word;
  std::string line;

  while (getline(file, line))
  {
    std::istringstream iss(line);
    iss >> word;
    if (word == word_to_find)
    {
      iss >> word;
      return clean_word(word);
    }
  }
  return "0";
}

void Parser::parse(std::string filename)
{
  std::string word;
  std::string line;
  std::ifstream file(filename.c_str()); 

  while (getline(file, line))
  {
    std::istringstream iss(line);
    iss >> word;
    if (word == "port")
    {
      iss >> word;
      port = clean_word(word);
    }
    else if (word == "host")
    {
      iss >> word;
      host = clean_word(word);
    }
    else if (word == "server_name")
    {
      iss >> word;
      server_name = clean_word(word);
    }
    else if (word == "error_page")
    {
      iss >> word;
      error_page = clean_word(word);
    }
    else if (word == "client_max_body_size")
    {
      iss >> word;
      client_max_body_size = clean_word(word);
    }
    else if (word == "root")
    {
      iss >> word;
      root = clean_word(word);
    }
    else if (word == "index")
    {
      iss >> word;
      index = clean_word(word);
    }
    else if (word == "location_root")
    {
      iss >> word;
      location_root = clean_word(word);
    }
    else if (word == "autoindex")
    {
      iss >> word;
      autoindex = clean_word(word);
    }
    else if (word == "allow_methods")
    {
      iss >> word;
      allow_methods = clean_word(word);
    }
    else if (word == "default_file")
    {
      iss >> word;
      default_file = clean_word(word);
    }
    else if (word == "cgi_root")
    {
      iss >> word;
      cgi_root = clean_word(word);
    }
    else if (word == "cgi_path")
    {
      iss >> word;
      cgi_path = clean_word(word);
    }
    else if (word == "cgi_extension")
    {
      iss >> word;
      cgi_extension = clean_word(word);
    }
  }
}

std::string Parser::clean_word(std::string word)
{
  std::string clean_word = "";
  for (long unsigned int i = 0; i < word.length(); i++)
  {
    if (word[i] == ';' || word[i] == '\t')
    {
      continue;
    }
    else
    {
      clean_word += word[i];
    }
  }
  return clean_word;
}

void Parser::print_values()
{
  std::cout << "port: \t\t\t" << port << std::endl;
  std::cout << "host: \t\t\t" << host << std::endl;
  std::cout << "server_name: \t\t\t" << server_name << std::endl;
  std::cout << "error_page: \t\t\t" << error_page << std::endl;
  std::cout << "client_max_body_size: \t\t\t" << client_max_body_size << std::endl;
  std::cout << "root: \t\t\t" << root << std::endl;
  std::cout << "index: \t\t\t" << index << std::endl;
  std::cout << "autoindex: \t\t\t" << autoindex << std::endl;
  std::cout << "allow_methods: \t\t\t" << allow_methods << std::endl;
  std::cout << "cgi_path: \t\t\t" << cgi_path << std::endl;
  std::cout << "cgi_extension: \t\t\t" << cgi_extension << std::endl;
}
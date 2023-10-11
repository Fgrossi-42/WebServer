#include "Parser.hpp"

std::string Parser::find_word(std::string filename, std::string word_to_find)
{
  std::ifstream file(filename);
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
  std::ifstream file(filename);

  while (getline(file, line))
  {
    std::istringstream iss(line);
    iss >> word;
    if (word == "listen")
      while ((iss.peek()!='\n') && (iss>>word))
        port.append(clean_word(word));
    else if (word == "host")
      while ((iss.peek()!='\n') && (iss>>word))
        host.append(clean_word(word));
    else if (word == "server_name")
      while ((iss.peek()!='\n') && (iss>>word))
        server_name.append(clean_word(word));
    else if (word == "error_page")
      while ((iss.peek()!='\n') && (iss>>word))
        error_page.append(clean_word(word));
    else if (word == "client_max_body_size")
      while ((iss.peek()!='\n') && (iss>>word))
        client_max_body_size.append(clean_word(word));
    else if (word == "root")
      while ((iss.peek()!='\n') && (iss>>word))
        root.append(clean_word(word));
    else if (word == "index")
      while ((iss.peek()!='\n') && (iss>>word))
        index.append(clean_word(word));
    else if (word == "autoindex")
      while ((iss.peek()!='\n') && (iss>>word))
        autoindex.append(clean_word(word));
    else if (word == "allow_methods")
      while ((iss.peek()!='\n') && (iss>>word))
        allow_methods.append(clean_word(word));
    else if (word == "cgi_path")
      while ((iss.peek()!='\n') && (iss>>word))
        cgi_path.append(clean_word(word));
    else if (word == "cgi_ext")
      while ((iss.peek()!='\n') && (iss>>word))
        cgi_extension.append(clean_word(word));
  }
  file.close();
}

std::string Parser::clean_word(std::string word)
{
  std::string clean_word = "";
  for (int i = 0; i < word.length(); i++)
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
#include "../../Inc/Location.hpp"

Location::Location()
{
}

Location::~Location()
{
}

Location::Locations(std::string filename)
{
	std::string line;
	std::string word;
	std::ifstream file(filename.c_str());

	while (getline(file, line))
	{
		std::istringstream iss(line);
		iss >> word;
		if (word == "location")
		{
			iss >> word;
			name = word;
			iss >> word;
			if (word == "{")
			{
				while (getline(file, line))
				{E\\E
					std::istringstream iss(line);
					iss >> word;
					if (word == "methods")
					{
						while (word != NULL)
						{
							iss >> word;
							methods += clean_word(word);
						}
					}
					else if (word == "autoindex")
					{
						iss >> word;
						if (word == "on")
							autoindex = true;
						else
							autoindex = false;
					}
					else if (word == "index")
					{
						iss >> word;
						index = clean_word(word);
					}
					else if (word == "root")
					{
						iss >> word;
						root = clean_word(word);
					}
					else if (word == "cgi")
					{
						iss >> word;
						cgi = clean_word(word);
					}
					else if (word == "cgi_path")
					{
						while(word != NULL)
						{
							iss >> word;
							cgi_path = clean_word(word);
						}
					}
					else if (word == "cgi_ext")
					{
						while(word != NULL)
						{
							iss >> word;
							cgi_ext = clean_word(word);
						}
					}
					else if (word == "return")
					{
						iss >> word;
						_return = clean_word(word);
					}
					else if (word == "}")
						break;
				}
			}
		}
	}
}

std::string Location::RemoveSlashes(std::string word)
{
	std::string new_word;
	int i = 0;

	while (word[i])
	{
		if (word[i] != '/')
			new_word += word[i];
		i++;
	}
	return (new_word);
}

std::string Location::GetStringBetweenBrackets(std::string word)
{
	std::string new_word;
	int i = 0;

	while (word[i])
	{
		if (word[i] == '{')
		{
			i++;
			while (word[i] != '}')
			{
				new_word += word[i];
				i++;
			}
		}
		i++;
	}
	return (new_word);
}

std::string Location::clean_word(std::string word)
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
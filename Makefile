NAME = webserv

SRCS = Src/Parser/Parser.cpp Src/Webserver/main.cpp Src/Webserver/Webserver.cpp Src/Parser/Location.cpp

# HEADERS	= Inc/Webserv.hpp Inc/Parser.hpp Inc/Request.hpp Inc/Response.hpp Inc/Server.hpp Inc/Location.hpp Inc/CGI.hpp Inc/Utils.hpp Inc/Config.hpp Inc/ConfigParser.hpp Inc/ConfigParserUtils.hpp Inc/ConfigParserException.hpp Inc/ConfigP

OBJS = $(SRCS:.cpp=.o)

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98
CXXFLAGS += -g3 

RM = rm -rf

RESET = "\033[0m"
BLACK = "\033[1m\033[37m"

all:
	@$(MAKE) $(NAME) -j5
$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo $(BLACK)-webserv compiled 🌐 $(RESET)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: 	fclean all

.PHONY: all clean fclean re
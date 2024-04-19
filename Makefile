NAME = ircserv

SRCS = main.cpp \
		srcs/Server.cpp	\
		srcs/User.cpp \
		srcs/utils.cpp \
		srcs/Channel.cpp \
		srcs/commands/nick.cpp \
		srcs/commands/join.cpp \
		srcs/commands/quit.cpp \
		srcs/commands/kick.cpp \
		srcs/commands/privmsg.cpp \
		srcs/commands/topic.cpp \
		srcs/commands/mode.cpp \
		srcs/commands/errors.cpp \
		srcs/commands/invite.cpp \
		srcs/commands/pass.cpp \
		srcs/Commands.cpp

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

RM = rm -f

OBJS = $(SRCS:.cpp=.o)

GREEN = \033[32m
YELLOW = \033[33m
WHITE = \033[37m
RED = \033[0;31m

%.o	:	%.cpp
		@echo "${WHITE}Compiling object $<"
		@$(CC) $(CFLAGS) -c $< -o $@
		@tput cuu1 && tput dl1

all:	$(NAME)

$(NAME):	$(OBJS)
			@echo "${WHITE}Compiling ft_irc..."
			@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
			@tput cuu1 && tput dl1
			@echo "${GREEN}ft_irc OK${WHITE}"
			

debug: CFLAGS+=-g
debug: re

clean:
		@echo "${WHITE}Cleaning objects..."
		@$(RM) $(OBJS)
		@tput cuu1 && tput dl1
		@echo "${YELLOW}Objects cleaned"

fclean: clean
		@echo "${WHITE}Cleaning ft_irc"
		@$(RM) $(NAME)
		@tput cuu1 && tput dl1
		@echo "${YELLOW}ft_irc cleaned${WHITE}"

re: fclean all

.PHONY: all fclean clean re debug bonus
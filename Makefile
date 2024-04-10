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

NAME = irc


RM = rm -f

OBJS = $(SRCS:.cpp=.o)

%.o	:	%.cpp
		$(CC) $(CFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) 

debug: CFLAGS+=-g
debug: re

clean:
		$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
		$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all fclean clean re debug bonus
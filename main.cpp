
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "includes/Server.hpp"
#include "includes/User.hpp"
#include <signal.h>
#include <termios.h>
#include <cstdio>

void ft_exit(int signal)
{
	(void)signal;
    exit(0);
}

void	ft_init_signals(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &term);
	signal(SIGQUIT, ft_exit);
	signal(SIGINT, ft_exit);
}

int main(int argc, char **argv) {

    Server server(std::atoi(argv[1]));
    (void) argc;
    
    return 0;
}
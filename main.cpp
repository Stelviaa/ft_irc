
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
#include <cstdio>

int ft_exit()
{
    return (0);
}

int main(int argc, char **argv) {

    Server server(std::atoi(argv[1]));
    (void) argc;
    
    return 0;
}
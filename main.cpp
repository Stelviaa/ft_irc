/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:56:48 by mboyer            #+#    #+#             */
/*   Updated: 2024/04/20 15:16:47 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include <signal.h>
#include <termios.h>
#include <cstdio>

bool	close_server = false;

void	ft_exit(int signal) {
	(void)signal;
	close_server = true;
}

int	main(int argc, char **argv) {
	signal(SIGQUIT, ft_exit);
	signal(SIGINT, ft_exit);
	if (argc >= 3)
		Server server(std::atoi(argv[1]), argv[2]);
	else if (argc == 2)
		Server server(std::atoi(argv[1]), "");
	(void) argc;
	return 0;
}

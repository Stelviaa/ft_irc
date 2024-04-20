/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:58:21 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/20 11:30:28 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "bot.hpp"
#include "../includes/Server.hpp"

int main(Server *server)
{
	Bot	bot;

	if ((bot.set_fd(accept(server->getFd(), (struct sockaddr *)server->getAddress(), (socklen_t*)server->getLenAddress()))) < 0) {
		std::perror("Erreur lors de l'acceptation de la connexion");
		exit(EXIT_FAILURE);
	}
	std::cout << "Connexion acceptée" << std::endl;
	std::string	welcome_message = "Welcome to the server !\r\n";
	server->AddUsers();
	usr->_id = server->_nbUsers;
	server->_fds[server->_nbUsers].fd = usr->getFd();
	server->_fds[server->_nbUsers].events = POLLIN;
	fcntl(server->_fds[server->_nbUsers].fd, F_SETFL, O_NONBLOCK);
	send(server->_fds[server->_nbUsers].fd, welcome_message.c_str(), welcome_message.length(), 0);
	server->_users.push_back(usr);
}*/

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 4444
 
int main(int argc, char const* argv[])
{
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    char* hello = "Hello from client\n";
    char buffer[1024] = { 0 };
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
    if ((status
         = connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(client_fd, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read(client_fd, buffer,
                   1024 - 1); // subtract 1 for the null
                              // terminator at the end
    printf("%s\n", buffer);
 
    // closing the connected socket
    //close(client_fd);
    while (1)
    {
        
    }
    return 0;
}
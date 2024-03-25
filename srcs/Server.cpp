/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:11:22 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/25 18:37:17 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

Server::Server(int port)
{
	this->_nbUsers = 0;
	int option = 1;
	_lenAddress = sizeof(_address);
	if ((this->_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("Erreur lors de la création du socket");
		exit(EXIT_FAILURE);
	}
	setsockopt(this->_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
	fcntl(this->_fd, F_SETFL, O_NONBLOCK);
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = htons(INADDR_ANY);
	_address.sin_port = htons(port);
	
	if (bind(_fd, (struct sockaddr *)&_address, sizeof(_address)) < 0) {
		perror("Erreur lors de l'attachement du socket à l'adresse et au port spécifiés");
		exit(EXIT_FAILURE);
	}
	if (listen(_fd, 3) < 0) {
		perror("Erreur lors de l'écoute des connexions entrantes");
		exit(EXIT_FAILURE);
	}
	std::cout << "Serveur IRC en attente de connexions..." << std::endl;
	
	//this->CheckConnection();
	this->CheckSocket();
}

void    Server::CheckConnection()
{
	User	*usr = new User();
	char buffer[1024] = {0};

	if ((usr->setFd(accept(this->getFd(), (struct sockaddr *)this->getAddress(), (socklen_t*)this->getLenAddress()))) < 0)
	{
		std::perror("Erreur lors de l'acceptation de la connexion");
		exit(EXIT_FAILURE);
	}
	std::cout << "Connexion acceptée" << std::endl;
	std::string welcome_message = "Welcome to the server !\r\n";
	send(usr->getFd(), welcome_message.c_str(), welcome_message.length(), 0);
	recv(usr->getFd(), buffer, 1024, 0);

	fcntl(usr->getFd(), F_SETFL, O_NONBLOCK);
	usr->parseName(buffer);
	this->_users.push_back(usr);
	this->AddUsers();
}

void    Server::CheckSocket()
{
	struct pollfd fds[4096];
	int				i = 1;

	fds[0].fd = this->_fd;
	fds[0].events = POLLIN;
	
	while (poll(fds, this->getNbUsers() + 1, -1) != -1)
	{
		char buffer[1024] = {0};

		if (fds[0].revents & POLLIN)
		{
			this->CheckConnection();
			fds[this->_nbUsers].fd = this->_users[this->_nbUsers - 1]->getFd();
			fds[this->_nbUsers].events = POLLIN;
		}
		while (i <= this->getNbUsers())
		{
			if(fds[i].revents & POLLIN)
			{
				recv(fds[i].fd, buffer, 1024, 0);
				std::cout << "Message du client : " << buffer << std::endl;
				if (std::string(buffer).find("JOIN") != std::string::npos)
				{
					std::string join_response = ":";
					join_response += this->_users[i - 1]->getUsername();
					join_response += " JOIN #blabla : Welcome to #channel\r\n";
					
					send(fds[i].fd, join_response.c_str(), join_response.length(), 0);
				}
			}
			i ++;
		}
		i = 1;
	}
}




/****************    GETTER    ***********************/

int Server::getFd() const
{
	return (_fd);
}

struct sockaddr_in *Server::getAddress()
{
	return (&_address);
}

int Server::getNbUsers()
{
	return (this->_nbUsers);
}

void Server::AddUsers()
{
	this->_nbUsers ++;
}

int *Server::getLenAddress()
{
	return (&_lenAddress);
}

Server::~Server()
{
	close(_fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:11:22 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/30 21:00:06 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

Server::Server(int port, std::string pass)
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
	this->_pass = pass;
	if (bind(_fd, (struct sockaddr *)&_address, sizeof(_address)) < 0) {
		perror("Erreur lors de l'attachement du socket à l'adresse et au port spécifiés");
		exit(EXIT_FAILURE);
	}
	if (listen(_fd, 3) < 0) {
		perror("Erreur lors de l'écoute des connexions entrantes");
		exit(EXIT_FAILURE);
	}
	std::cout << "Serveur IRC en attente de connexions..." << std::endl;
	
	this->CheckSocket();
}

void    Server::CheckConnection()
{
	User	*usr = new User();

	if ((usr->setFd(accept(this->getFd(), (struct sockaddr *)this->getAddress(), (socklen_t*)this->getLenAddress()))) < 0)
	{
		std::perror("Erreur lors de l'acceptation de la connexion");
		exit(EXIT_FAILURE);
	}
	std::cout << "Connexion acceptée" << std::endl;
	std::string welcome_message = "Welcome to the server !\r\n";
	fcntl(this->_fds[this->_nbUsers].fd, F_SETFL, O_NONBLOCK);

	this->AddUsers();
	this->_fds[this->_nbUsers].fd = usr->getFd();
	this->_fds[this->_nbUsers].events = POLLIN;

	send(this->_fds[this->_nbUsers].fd, welcome_message.c_str(), welcome_message.length(), 0);

	this->_users.push_back(usr);
}

void Server::send_all_fd(std::string msg, int i)
{
	int n = 1;
	std::vector<std::string> split_msg;
	std::string join_response = ":";
	
	join_response += this->_users[i - 1]->getUsername();
	join_response += " ";
	join_response += msg;
	split_msg = ft_split(msg, ' ');

	std::string target = split_msg[1];
	while (n <= this->getNbUsers())
	{
		if (n != i && (this->_users[n - 1]->getUsername() == target || this->_users[n - 1]->getChannel() == target))
			send(this->_fds[n].fd, join_response.c_str(), join_response.length(), 0);
		n ++;
	}
}

void	Server::close_serv()
{
	std::cout << "Closing server ..." << std::endl;
	int i = 1;
	while (i <= this->_nbUsers)
	{
		delete(this->_users[i]);
		i ++;
	}

	close(this->_fd);
	std::cout << "Server is closed" << std::endl;
}

void Server::commands(char buffer[1024], int i)
{
	if (std::string(buffer).find("NICK") != std::string::npos)
	{
		this->_users[i - 1]->parseName(buffer);
	}
	if (std::string(buffer).find("JOIN") != std::string::npos)
	{
		std::vector<std::string> splitted;
		std::string	name;
		int			index;
		
		splitted = ft_split(buffer, ' ');
		if (splitted[1][0] == '#')
		{
			name = get_name(splitted[1]);
			std::string join_response = ":";
			join_response += this->_users[i - 1]->getUsername();
			join_response += " JOIN ";
			join_response += name;
			join_response += "\r\n";
			this->_users[i - 1]->setChannel(name);
			index = find_channel(this->_channels, name);
			if (index == -1)
				this->_channels.push_back(new Channel(name, this->_users[i - 1]));
			else
				this->_channels[index]->AddUsers(this->_users[i - 1]);
			send(this->_fds[i].fd, join_response.c_str(), join_response.length(), 0);
		}
	}
	if (std::string(buffer).find("QUIT") != std::string::npos)
	{
		delete this->_users[i - 1];
		if (i != this->_nbUsers)
		{
			this->_users[i -1] = this->_users[this->_nbUsers - 1];
			this->_users[this->_nbUsers - 1] = 0;
			this->_fds[i] = this->_fds[this->_nbUsers];
		}
		this->_nbUsers --;
	}
	if (std::string(buffer).find("PRIVMSG") != std::string::npos)
	{
		if (std::string(buffer).find(":") != std::string::npos)
			this->send_all_fd(buffer, i);
	}
	if (std::string(buffer).find("KICK") != std::string::npos)
	{
		std::vector<std::string> splitted;
		std::string	name;
		
		splitted = ft_split(buffer, ' ');
		if (splitted[1][0] == '#')
		{
			name = get_name(splitted[1]);
			std::string kick_msg = ":";
			kick_msg += this->_users[i - 1]->getUsername();
			kick_msg += " KICK ";
			kick_msg += name;
			kick_msg += "\r\n";
			send(this->_fds[i].fd, kick_msg.c_str(), kick_msg.length(), 0);
		}
	}
}

void	Server::log_in(std::string buffer, int i)
{
	std::vector<std::string> msg = ft_split(buffer, ' ');
	std::string	response;
	int	index;

	index = find_index(msg, "PASS");
	if (index != -1)
	{
		if (size_t(index) != msg.size() - 1 && msg[index + 1].find(this->_pass) != std::string::npos)
		{
			this->_users[i - 1]->setStatus(1);
			response = "Connection Successful\n";
			send(this->_fds[i].fd, response.c_str(), response.length(), 0);
		}
		else
		{
			response = "Wrong password try again\n";
			send(this->_fds[i].fd, response.c_str(), response.length(), 0);
		}
	}
	else
	{
		response = "You have to connect using the command : PASS <password>\n";
		send(this->_fds[i].fd, response.c_str(), response.length(), 0);
	}
}

void    Server::CheckSocket()
{
	int				i = 1;

	this->_fds[0].fd = this->_fd;
	this->_fds[0].events = POLLIN;
	
	while (poll(this->_fds, this->getNbUsers() + 1, -1) != -1 && close_server == false)
	{
		char buffer[1024] = {0};

		if (this->_fds[0].revents & POLLIN)
		{
			this->CheckConnection();
		}
		while (i <= this->getNbUsers())
		{
			if(this->_fds[i].revents & POLLIN)
			{
				recv(this->_fds[i].fd, buffer, 1024, 0);
				std::cout << "Message du client : " << buffer << std::endl;
				if (this->_users[i - 1]->getStatus() == 0 && !this->_pass.empty())
					this->log_in(buffer, i);
				if (this->_users[i - 1]->getStatus() != 0 || this->_pass.empty())
					this->commands(buffer, i);
			}
			i ++;
		}
		i = 1;
	}
	this->close_serv();
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

void Server::RemoveUser()
{
	this->_nbUsers --;
}

int *Server::getLenAddress()
{
	return (&_lenAddress);
}

Server::~Server()
{
	close(_fd);
}
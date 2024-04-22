/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:11:22 by sforesti          #+#    #+#             */
/*   Updated: 2024/04/22 13:58:05 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/Commands.hpp"
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

Server::Server(int port, std::string pass) {
	this->_nbUsers = 0;
	int	option = 1;
	this->_lenAddress = sizeof(_address);
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

void	Server::CheckConnection() {
	User	*usr = new User();

	if ((usr->setFd(accept(this->getFd(), (struct sockaddr *)this->getAddress(), (socklen_t*)this->getLenAddress()))) < 0) {
		std::perror("Erreur lors de l'acceptation de la connexion");
		exit(EXIT_FAILURE);
	}
	std::cout << "Connexion acceptée" << std::endl;
	std::string	welcome_message = "Welcome to the server !\r\n";
	this->AddUsers();
	usr->_id = this->_nbUsers;
	this->_fds[this->_nbUsers].fd = usr->getFd();
	this->_fds[this->_nbUsers].events = POLLIN;
	fcntl(this->_fds[this->_nbUsers].fd, F_SETFL, O_NONBLOCK);
	send(this->_fds[this->_nbUsers].fd, welcome_message.c_str(), welcome_message.length(), 0);
	this->_users.push_back(usr);
}

void	Server::close_serv() {
	std::cout << "Closing server ..." << std::endl;
	int i = 0;
	while (i < this->_nbUsers) {
		delete this->_users[i];
		i ++;
	}
	std::map<std::string, Channel *>::iterator it;
	for (it = this->_channels.begin(); it != this->_channels.end(); it ++)
		delete it->second;
	close(this->_fd);
	std::cout << "Server is closed" << std::endl;
}

void	Server::log_in(std::string buffer, int i) {
	std::vector<std::string>	msg = ft_split(buffer, ' ');
	std::string					response;
	int							index;

	index = find_index(msg, "PASS");
	if (index != -1) {
		if (size_t(index) != msg.size() - 1 && (!msg[index + 1].compare(this->_pass + "\n") || !msg[index + 1].compare(this->_pass + "\r\n"))) {
			this->_users[i - 1]->setStatus(1);
			response = "Connection Successful\n";
			send(this->_fds[i].fd, response.c_str(), response.length(), 0);
		}
		else {
			response = "Wrong password try again\n";
			send(this->_fds[i].fd, response.c_str(), response.length(), 0);
		}
		return ;
	}
	else if (this->_users[i - 1]->getStatus() == 0 && !this->_pass.empty()) {
		response = "You have to connect using the command : PASS <password>\n";
		send(this->_fds[i].fd, response.c_str(), response.length(), 0);
		return ;
	}
}

void	Server::CheckSocket() {
	int	i = 1;
	int ret = 0;
	this->_fds[0].fd = this->_fd;
	this->_fds[0].events = POLLIN;

	while (close_server == false && poll(this->_fds, this->getNbUsers() + 1, -1) != -1) {
		char	buffer[1024] = {0};
		if (this->_fds[0].revents & POLLIN)
			this->CheckConnection();
		while (i <= this->getNbUsers()) {
			if(this->_fds[i].revents & POLLIN) {
				int f = recv(this->_fds[i].fd, buffer, 1024, 0);
				std::cout << f << " " << i <<std::endl;
				this->_users[i - 1]->buffer += buffer;
				while (ret == 0 && this->_users[i - 1]->buffer.find('\n') != std::string::npos) {
					size_t newline = this->_users[i - 1]->buffer.find('\n');
					std::string cmd = this->_users[i - 1]->buffer.substr(0, newline + 1);
					if (cmd.substr(0, 3) == "CAP") {
						this->_users[i - 1]->buffer = this->_users[i - 1]->buffer.substr(newline + 1);
						continue ;
					}
					std::cout << "Message du client : " << cmd << std::endl;
					ret = commands(this, cmd, i);
					if (ret == 0 && this->_users[i - 1]->buffer.size() > 0)
						this->_users[i - 1]->buffer = this->_users[i - 1]->buffer.substr(newline + 1);
				}
				ret = 0;
				if (f == 0) {
					std::vector<std::string>	tmp;
					tmp.push_back("Interrupted connection");
					quit_cmd(this, tmp, i);
				}
			}
			i ++;
		}
		i = 1;
	}
	this->close_serv();
}

void	Server::kickUser(int id, std::string msg) {
	size_t		i = 0;
	std::string	name = this->_users[id]->getNickname();
	while (i < this->_users[id]->_channels.size()) {
		std::string chan = this->_users[id]->_channels[i];
		std::map<std::string, User *>::iterator it = this->_channels[chan]->_users.begin();
		while (it != this->_channels[chan]->_users.end()) {
			if (it->second->_id - 1 != id)
				std::string tmp = "QUIT " + chan + " :" + msg;
				send(this->_fds[it->second->_id].fd, tmp.c_str(), tmp.length(), 0);
			it ++;
		}
		this->_channels[chan]->_users.erase(name);
		i ++;
	}
}

/****************    GETTER    ***********************/

int Server::is_Users(std::string _nick) {
	size_t	i = 0;

	while (i < this->_users.size()) {
		if (this->_users[i]->getNickname() == _nick)
			return (i + 1);
		i ++;
	}
	return (0);
}

int Server::getFd() const {
	return (_fd);
}

struct sockaddr_in *Server::getAddress() {
	return (&_address);
}

int	Server::getNbUsers() {
	return (this->_nbUsers);
}

void	Server::AddUsers() {
	this->_nbUsers ++;
}

void	Server::RemoveUser() {
	this->_nbUsers --;
}

int	*Server::getLenAddress() {
	return (&_lenAddress);
}

Server::~Server() {
	close(_fd);
}

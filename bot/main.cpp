/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:58:21 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/19 23:07:17 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

int main(void)
{
	Bot	bot;

	if ((bot->set_fd(accept(this->getFd(), (struct sockaddr *)this->getAddress(), (socklen_t*)this->getLenAddress()))) < 0) {
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:52:48 by sforesti          #+#    #+#             */
/*   Updated: 2024/04/11 12:54:09 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"
#include "../includes/irc.hpp"
#include <unistd.h>

User::User() {
	this->_status = 0;
	this->buffer = "";
	this->_username = "";
}

int User::setFd(int value) {
	if (value < 0)
		return (value);
	_fd = value;
	return (value);
}

void	User::setUsername(std::string username) {
	_username = username;
}

void	User::setNickname(std::string nickname) {
	_nickname = nickname;
}

std::string User::getUsername() {
	return (this->_username);
}

void User::removeChannel(std::string chan) {
	std::vector<std::string>::iterator	it;

	it = this->_channels.begin();
	while (it != this->_channels.end()) {
		if (*it == chan) {
			this->_channels.erase(it);
			return ;
		}
		it ++;
	}
}

std::string User::getNickname() {
	return (this->_nickname);
}

int User::getStatus() {
	return (this->_status);
}

void User::setStatus(int i) {
	this->_status = i;
}

int User::getFd() const{
	return (_fd);
}

User::~User(){
	close(_fd);
}

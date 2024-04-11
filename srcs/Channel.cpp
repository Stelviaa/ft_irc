/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:08:42 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/11 12:37:09 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

Channel::Channel(std::string name, User *op) : _name(name) {
	this->_op.push_back(op);
	this->_users[op->getNickname()] = op;
	op->_channels.push_back(name);
	this->_topic = "";
	this->_mode = 0;
}

void	Channel::AddUsers(User *usr) {
	this->_users[usr->getNickname()] = usr;
}

int	Channel::is_op(User *usr) {
	size_t i = 0;

	while (i < this->_op.size())
	{
		if (this->_op[i] == usr)
			return (i);
		i ++;
	}
	return (-1);
}

void	Channel::setPassword(std::string pass) {
	this->_password = pass;
}

std::string Channel::getPassword() {
	return (this->_password);
}

std::string	Channel::getName() {
	return (this->_name);
}

Channel::~Channel() {}

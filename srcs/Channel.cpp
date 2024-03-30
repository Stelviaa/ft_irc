/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:08:42 by luxojr            #+#    #+#             */
/*   Updated: 2024/03/30 18:10:24 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

Channel::Channel(std::string name, User *op) : _name(name)
{
	this->_op.push_back(op);
	this->_users.push_back(op);
}

void	Channel::AddUsers(User *usr)
{
	this->_users.push_back(usr);
}

std::string	Channel::getName()
{
	return (this->_name);
}

Channel::~Channel()
{
	
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:08:42 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/01 08:32:06 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

Channel::Channel(std::string name, User *op) : _name(name)
{
	this->_op.push_back(op);
	this->_users[op->getUsername()] = op;
}

void	Channel::AddUsers(User *usr)
{
	this->_users[usr->getUsername()] = usr;
}

int	Channel::is_op(User *usr)
{
	size_t i = 0;

	while (i < this->_op.size())
	{
		if (this->_op[i] == usr)
			return (1);
		i ++;
	}
	return (0);
}

std::string	Channel::getName()
{
	return (this->_name);
}

Channel::~Channel()
{
	
}

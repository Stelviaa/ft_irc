/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:43:14 by mboyer            #+#    #+#             */
/*   Updated: 2024/03/31 12:20:02 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"
#include "../../includes/irc.hpp"

void	join_cmd(Server *server, std::string buffer, int i)
{
	std::vector<std::string> splitted;
	std::string	name;
	int			index;
	
	splitted = ft_split(buffer, ' ');
	if (splitted[1][0] == '#')
	{
		name = get_name(splitted[1]);
		std::string join_response = ":";
		join_response += server->_users[i - 1]->getUsername();
		join_response += " JOIN ";
		join_response += name;
		join_response += "\r\n";
		server->_users[i - 1]->setChannel(name);
		index = find_channel(server->_channels, name);
		if (index == -1)
			server->_channels.push_back(new Channel(name, server->_users[i - 1]));
		else
			server->_channels[index]->AddUsers(server->_users[i - 1]);
		send(server->_fds[i].fd, join_response.c_str(), join_response.length(), 0);
	}
}
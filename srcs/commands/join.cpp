/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:43:14 by mboyer            #+#    #+#             */
/*   Updated: 2024/04/05 09:43:40 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"
#include "../../includes/irc.hpp"

void	join_cmd(Server *server, std::vector<std::string> splitted, int i)
{
	std::string	name;

	if (splitted.empty()) {
		send(server->_fds[i].fd, "JOIN error: missing parameters\n", 31, 0);
		//<canal>{,<canal>} [<key>{,<key>}] 
		return ;
	}
	if (splitted[0][0] == '#')
	{
		name = splitted[0];
		std::string join_response = ":";
		join_response += server->_users[i - 1]->getUsername();
		join_response += " JOIN ";
		join_response += name;
		join_response += "\r\n";
		if (server->_channels.find(name) == server->_channels.end())
			server->_channels[name] = new Channel(name, server->_users[i - 1]);
		else
		{
			std::cout << "Channel mode :" << server->_channels[name]->_mode << std::endl;
			if (server->_channels[name]->_mode & K_PASS)
			{
				if (splitted.size() <= 1)
				{
					send(server->_fds[i].fd, "You need a password to join this channel\n" , 42, 0);
					return ;
				}
				if (splitted[1].find(server->_channels[name]->getPassword()) == std::string::npos)
				{
					send(server->_fds[i].fd, "Wrong password\n" , 16, 0);
					return ;
				}
			}
			if ((server->_channels[name]->_mode & U_LIMITS) && (server->_channels[name]->_userLimit >= server->_channels[name]->_users.size()))
			{
				send(server->_fds[i].fd, "The channel is full\n", 21, 0);
				return ;
			}
			server->_channels[name]->AddUsers(server->_users[i - 1]);
		}
		send(server->_fds[i].fd, join_response.c_str(), join_response.length(), 0);
	}
}
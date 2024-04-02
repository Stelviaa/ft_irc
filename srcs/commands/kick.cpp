/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 12:26:14 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/02 18:11:11 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	kick_cmd(Server *server, std::string buffer, int i)
{

	std::vector<std::string> splitted;
	std::string	chan;
	std::string name;

	splitted = ft_split(buffer, ' ');
	if (splitted[1][0] == '#')
	{
		chan = get_name(splitted[1]);
		name = get_name(splitted[2]);
		std::string kick_msg = ":";
		kick_msg += server->_users[i - 1]->getUsername();
		kick_msg += " KICK ";
		kick_msg += chan;
		kick_msg += "\r\n";
		if (server->_channels.find(chan) != server->_channels.end())
		{
			if (server->_channels[chan]->is_op(server->_users[i - 1]))
			{
				if (server->_channels[chan]->_users.find(name) != server->_channels[chan]->_users.end())
				{
					send(server->_fds[i].fd, "This user has been kicked\n", 27, 0);
					if (splitted.size() == 4)
					{
						std::string msg = "You have been kicked ";
						msg += splitted[3];
						msg += "\n";
						send(server->_fds[server->_channels[chan]->_users[name]->_id].fd, msg.c_str(), msg.size(), 0);
					}
					else
						send(server->_fds[server->_channels[chan]->_users[name]->_id].fd, "You have been kicked\n", 22, 0);
					server->_channels[chan]->_users.erase(name);
				}
				else
					send(server->_fds[i].fd, "This user is not in this channel\n", 34, 0);
			}
			else
				send(server->_fds[i].fd, "You are not operator of this channel\n", 38, 0);
		}
		else
			send(server->_fds[i].fd, "This channel doesn't exist\n", 28, 0);
		send(server->_fds[i].fd, kick_msg.c_str(), kick_msg.length(), 0);
	}
}
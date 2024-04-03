/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 12:26:14 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/03 14:49:45 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	kick_cmd(Server *server, std::vector<std::string> splitted, int i)
{
	std::string	chan;
	std::string name;

	//if (splitted.empty())
	// Missing parameters
	// return ;
	if (splitted[0][0] == '#')
	{
		chan = get_name(splitted[0]);
		name = get_name(splitted[1]);
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
					if (splitted.size() == 3)
					{
						std::string msg = "You have been kicked ";
						msg += splitted[2];
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
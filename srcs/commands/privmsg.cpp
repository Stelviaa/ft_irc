/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:43:37 by mboyer            #+#    #+#             */
/*   Updated: 2024/04/05 09:47:13 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"
#include <map>

void	privmsg_cmd(Server *server, std::vector<std::string> param, int i)
{
	if (param.empty()) {
		send(server->_fds[i].fd, "PRIVMSG error: missing parameters\n", 34, 0);
		return ;
	}
	// param[0] == <destinataire>{,<destinataire>}
	if (std::string(param[1]).find(":") != std::string::npos)
		send_all_fd(server, param, i);
}

void send_all_fd(Server *server, std::vector<std::string> split_msg, int i)
{
	int n = 1;
	std::string join_response = ":";
	
	join_response += server->_users[i - 1]->getUsername();
	join_response += " PRIVMSG ";
	join_response += split_msg[0];
	join_response += ' ';
	join_response += split_msg[1];
	join_response += '\n';

	std::string target = split_msg[0];
	if (target[0] == '#')
	{
		std::map<std::string, User *>::iterator it = server->_channels[target]->_users.begin();
		while (it != server->_channels[target]->_users.end())
		{
			std::cout << it->second->_id << std::endl;
			if (it->second->_id != i - 1)
				send(server->_fds[it->second->_id + 1].fd, join_response.c_str(), join_response.length(), 0);
			it ++;
		}
	}
	else
	{
		while (n <= server->getNbUsers())
		{
			if (n != i && (server->_users[n - 1]->getUsername() == target))
				send(server->_fds[n].fd, join_response.c_str(), join_response.length(), 0);
			n ++;
		}
	}
}
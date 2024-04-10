/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:43:14 by mboyer            #+#    #+#             */
/*   Updated: 2024/04/08 18:44:32 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"
#include "../../includes/irc.hpp"

void	process_join_cmd(Server *server, std::vector<std::string> splitted, int i)
{
	if (splitted[0][0] == '#')
	{
		std::string	name = splitted[0];
		std::string	join_response = ":";
		join_response += server->_users[i - 1]->getNickname();
		join_response += " JOIN ";
		join_response += name;
		join_response += "\r\n";
		if (server->_channels.find(name) == server->_channels.end())
			server->_channels[name] = new Channel(name, server->_users[i - 1]);
		else
		{
			if (server->_channels[name]->_mode & K_PASS)
			{
				if (splitted.size() <= 1)
				{
					err_cannot_join_chan(server, splitted[0], i, 'i'); //need pass
					return ;
				}
				if (splitted[1] != server->_channels[name]->getPassword())
				{
					err_cannot_join_chan(server, splitted[0], i, 'k'); //wrong pass
					return ;
				}
			}
			if ((server->_channels[name]->_mode & U_LIMITS) && (server->_channels[name]->_userLimit >= server->_channels[name]->_users.size()))
			{
				err_cannot_join_chan(server, splitted[0], i, 'l'); //channel full
				return ;
			}
			server->_channels[name]->AddUsers(server->_users[i - 1]);
			server->_users[i - 1]->_channels.push_back(name);
		}
		send(server->_fds[i].fd, join_response.c_str(), join_response.length(), 0);
	}
}

void	join_cmd(Server *server, std::vector<std::string> splitted, int i)
{
	std::string	name;

	if (splitted.empty()) {
		err_need_more_params(server, "JOIN", i);
		return ;
	}
	if (splitted[0].find(',') != std::string::npos) {
		std::istringstream	iss1(splitted[0]);
		std::string			word;
		while (std::getline(iss1, word, ',')) {
			std::vector<std::string> tmp;
			tmp.push_back(word);
			if (splitted.size() > 1 && !splitted[1].empty()) {
				std::istringstream	iss2(splitted[1]);
				std::getline(iss2, word, ',');
				tmp.push_back(word);
			}
			process_join_cmd(server, tmp, i);
		}
	}
	else
		process_join_cmd(server, splitted, i);
}

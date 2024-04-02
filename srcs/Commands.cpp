/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 12:54:49 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/02 19:52:00 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Commands.hpp"

void commands(Server *server, char buffer[1024], int i)
{
	if (std::string(buffer).find("NICK") != std::string::npos)
	{
		server->_users[i - 1]->parseName(buffer);
	}
	if (std::string(buffer).find("JOIN") != std::string::npos)
		join_cmd(server, buffer, i);
	if (std::string(buffer).find("QUIT") != std::string::npos)
	{
		delete server->_users[i - 1];
		if (i != server->getNbUsers())
		{
			server->_users[i -1] = server->_users[server->getNbUsers() - 1];
			server->_users[i - 1]->_id = i - 1;
			server->_users[server->getNbUsers() - 1] = 0;
			server->_fds[i] = server->_fds[server->getNbUsers()];
		}
		server->RemoveUser();
	}
	if (std::string(buffer).find("PRIVMSG") != std::string::npos)
		privmsg_cmd(server, buffer, i);
	if (std::string(buffer).find("KICK") != std::string::npos)
		kick_cmd(server, buffer, i);
	if (std::string(buffer).find("TOPIC") != std::string::npos)
		topic_cmd(server, buffer, i);
	if (std::string(buffer).find("MODE") != std::string::npos)
		mode_cmd(server, buffer, i);
}
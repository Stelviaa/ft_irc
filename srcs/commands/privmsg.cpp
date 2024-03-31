/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:43:37 by mboyer            #+#    #+#             */
/*   Updated: 2024/03/31 12:50:24 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	privmsg_cmd(Server *server, std::string buffer, int i)
{
	if (std::string(buffer).find(":") != std::string::npos)
		send_all_fd(server, buffer, i);
}

void send_all_fd(Server *server, std::string msg, int i)
{
	int n = 1;
	std::vector<std::string> split_msg;
	std::string join_response = ":";
	
	join_response += server->_users[i - 1]->getUsername();
	join_response += " ";
	join_response += msg;
	split_msg = ft_split(msg, ' ');

	std::string target = split_msg[1];
	while (n <= server->getNbUsers())
	{
		if (n != i && (server->_users[n - 1]->getUsername() == target || server->_users[n - 1]->getChannel() == target))
			send(server->_fds[n].fd, join_response.c_str(), join_response.length(), 0);
		n ++;
	}
}
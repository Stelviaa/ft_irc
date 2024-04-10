/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:39:10 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/10 17:58:55 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void pass_cmd(Server *server, std::vector<std::string> split_msg, int i)
{
	std::string	response;

	if (split_msg.empty())
	{
		response = "You have to connect using the command : PASS <password>\n";
		send(server->_fds[i].fd, response.c_str(), response.length(), 0);
		return ;
	}
	if (!split_msg[0].compare(server->_pass) || !split_msg[0].compare(server->_pass + "\r\n"))
	{
		server->_users[i - 1]->setStatus(1);
		response = "Connection Successful\n";
		send(server->_fds[i].fd, response.c_str(), response.length(), 0);
	}
	else if (server->_pass != "\0")
	{
		response = "Wrong password try again\n";
		send(server->_fds[i].fd, response.c_str(), response.length(), 0);
	}
}
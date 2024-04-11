/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:35:15 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/10 17:52:24 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"
#include <memory>

void quit_cmd(Server *server, std::vector<std::string> split_msg, int i)
{
	(void)split_msg;
	server->kickUser(i - 1);
	server->_usersToDel.push_back(server->_users[i - 1]);
	server->_users.erase(server->_users.begin() + i - 1);
	if (i != server->getNbUsers())
	{
		server->_users[i - 1] = server->_users[server->getNbUsers() - 1];
		server->_users[i - 1]->_id = i - 1;
		server->_users[server->getNbUsers() - 1] = 0;
		server->_fds[i] = server->_fds[server->getNbUsers()];
	}
	server->RemoveUser();
}
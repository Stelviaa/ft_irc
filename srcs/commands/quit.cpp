/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:17:03 by mboyer            #+#    #+#             */
/*   Updated: 2024/04/29 16:11:03 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"
#include <memory>

void	quit_cmd(Server *server, std::vector<std::string> param, int i) {
	for (std::map<std::string , Channel *>::iterator it = server->_channels.begin(); it != server->_channels.end(); it++){
		std::string name = it->first;
		for (size_t j = 0; j < server->_channels[name]->_invitedUsers.size(); j++)
			if (server->_channels[name]->_invitedUsers[j] == server->_users[i - 1]->getNickname())
				server->_channels[name]->_invitedUsers[j].erase();
	}
	if (param.empty())
		server->kickUser(i - 1, server->_users[i - 1]->getNickname() + " :has left the channel\n");
	else
		server->kickUser(i - 1, server->_users[i - 1]->getNickname() + " :" + param[0] + "\n");
	User *tmp = server->_users[i - 1];
	server->_users.erase(server->_users.begin() + i - 1);
	while (i < server->getNbUsers()) {
		server->_fds[i] = server->_fds[i + 1];
		server->_users[i - 1]->_id = i;
		i++; 
	}
	server->RemoveUser();
	delete tmp;
}

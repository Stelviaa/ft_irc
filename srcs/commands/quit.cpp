/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:17:03 by mboyer            #+#    #+#             */
/*   Updated: 2024/04/26 15:18:16 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"
#include <memory>

void	quit_cmd(Server *server, std::vector<std::string> param, int i) {
	
	for (size_t l = 0; l < server->_users.size(); l++){
		for (size_t k = 0; k < server->_users[l]->_channels.size(); k++){
			std::string name = server->_users[l]->_channels[k];
			for (size_t j = 0; j < server->_channels[name]->_invitedUsers.size(); j ++)
				if (server->_channels[name]->_invitedUsers[j] == server->_users[i - 1]->getNickname())
					server->_channels[name]->_invitedUsers[j].erase();
		}
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

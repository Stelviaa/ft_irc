/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:35:15 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/19 10:22:56 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"
#include <memory>

void	quit_cmd(Server *server, int i) {
	server->kickUser(i - 1);
	server->_usersToDel.push_back(server->_users[i - 1]);
	server->_users.erase(server->_users.begin() + i - 1);
	if (i != server->getNbUsers()) {
		server->_users[i - 1] = server->_users[server->getNbUsers() - 1];
		server->_users[i - 1]->_id = i - 1;
		server->_users[server->getNbUsers() - 1] = 0;
		server->_fds[i] = server->_fds[server->getNbUsers()];
	}
	server->RemoveUser();
}

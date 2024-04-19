/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:35:15 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/19 12:03:03 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"
#include <memory>

void	quit_cmd(Server *server, int i) {
	server->kickUser(i - 1);
	delete server->_users[i - 1];
	if (i != server->getNbUsers()) {
		server->_users[i - 1] = server->_users[server->getNbUsers() - 1];
		server->_users[i - 1]->_id = i - 1;
		server->_users[server->getNbUsers() - 1] = 0;
		server->_fds[i] = server->_fds[server->getNbUsers()];
	}
	server->RemoveUser();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:17:03 by mboyer            #+#    #+#             */
/*   Updated: 2024/04/20 11:17:18 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"
#include <memory>

void	quit_cmd(Server *server, int i) {
	server->kickUser(i - 1);
	User *tmp = server->_users[i - 1];
	server->_users.erase(server->_users.begin() + i - 1);
	server->_fds[i] = server->_fds[server->getNbUsers()];
	server->RemoveUser();
	delete tmp;
}

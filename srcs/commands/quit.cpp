/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:35:15 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/19 15:30:44 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"
#include <memory>

void    quit_cmd(Server *server, int i) {
    server->kickUser(i - 1);
    User *tmp = server->_users[i - 1];
    server->_users.erase(server->_users.begin() + i - 1);
    server->_fds[i] = server->_fds[server->getNbUsers()];
    server->RemoveUser();
    delete tmp;
}

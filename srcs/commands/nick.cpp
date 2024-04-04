/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:44:10 by mboyer            #+#    #+#             */
/*   Updated: 2024/04/04 11:30:23 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"
#include "../../includes/irc.hpp"

void	nick_cmd(Server *server, std::vector<std::string> param, int i)
{
	if (param.empty()) {
		send(server->_fds[i].fd, "NICK error: Missing parameters\n", 27, 0);
		return ;
	}
	//<pseudo> [ <distance> ] (distance is only send by server so blc)
	server->_users[i - 1]->setUsername(param[0]);
}

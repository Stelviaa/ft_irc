/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 12:26:14 by luxojr            #+#    #+#             */
/*   Updated: 2024/03/31 12:28:24 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	kick_cmd(Server *server, std::string buffer, int i)
{

	std::vector<std::string> splitted;
	std::string	name;

	splitted = ft_split(buffer, ' ');
	if (splitted[1][0] == '#')
	{
		name = get_name(splitted[1]);
		std::string kick_msg = ":";
		kick_msg += server->_users[i - 1]->getUsername();
		kick_msg += " KICK ";
		kick_msg += name;
		kick_msg += "\r\n";
		send(server->_fds[i].fd, kick_msg.c_str(), kick_msg.length(), 0);
	}
}
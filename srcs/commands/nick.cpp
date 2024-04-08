/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:44:10 by mboyer            #+#    #+#             */
/*   Updated: 2024/04/08 15:00:43 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"
#include "../../includes/irc.hpp"

int is_non_ascii(const std::string & str)
{
	for (size_t i = 0; i < str.length(); ++i) {
		if (static_cast<unsigned char>(str[i]) > 127)
			return (1);
	}
	return (0);
}

int	is_in_use(Server *server, const std::string nickname)
{
	 for (std::vector<User *>::iterator it = server->_users.begin(); it != server->_users.end(); ++it) {
		if (nickname == (*it)->getNickname())
			return (1);
	 }
	 return (0);
}

void	nick_cmd(Server *server, std::vector<std::string> param, int i)
{
	if (param.empty()) {
		send(server->_fds[i].fd, ": No nickname given\n", 20, 0);
		return ;
	}
	else if (is_non_ascii(param[0]) == 1 || param[0].size() > 9) {
		std::string err = param[0] + " :Erroneus nickname\n";
		send(server->_fds[i].fd, err.c_str(), err.size(), 0);
		return ;
	}
	else if (is_in_use(server, param[0]) == 1)
	{
		std::string err = param[0] + " :Nickname is already in use\n";
		send(server->_fds[i].fd, err.c_str(), err.size(), 0);
		return ;
	}
	server->_users[i - 1]->setNickname(param[0]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:43:37 by mboyer            #+#    #+#             */
/*   Updated: 2024/04/11 12:58:20 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"
#include <map>

int	check_duplicata(std::vector<std::string> names) {
	for (size_t i = 0; i < names.size(); ++i)
		for (size_t j = i + 1; j < names.size(); ++j)
		 	if (names[i] == names[j])
				return (1);
	return (0);
}

void	privmsg_cmd(Server *server, std::vector<std::string> param, int i) {
	if (param.empty())
		send(server->_fds[i].fd, ":No recipient given (PRIVMSG)\n", 30, 0);
	else if (param.size() < 2)
		send(server->_fds[i].fd, ":No text to send\n", 16, 0);
	else if (std::string(param[1]).find(":") != std::string::npos) {
		if (param[0].find(',') != std::string::npos) {
			std::vector<std::string>	names;
			std::istringstream			iss(param[0]);
			std::string					word;
			while (std::getline(iss, word, ','))
				names.push_back(word);
			if (check_duplicata(names) == 1) {
				std::string err = param[0];
				err += " :Duplicate recipients. No message delivered\n";
				send(server->_fds[i].fd, err.c_str(), err.size(), 0);
			}
			else {
				for (size_t j = 0; j < names.size(); ++j) {
					std::vector<std::string> tmp;
					tmp.push_back(names[j]);
					tmp.push_back(param[1]);
					send_all_fd(server, tmp, i);
				}
			}
		}
		else
			send_all_fd(server, param, i);
	}
}

void	send_all_fd(Server *server, std::vector<std::string> split_msg, int i) {
	int			n = 1;
	std::string	join_response = ":" + server->_users[i - 1]->getNickname() + " PRIVMSG " + split_msg[0] + ' ' + split_msg[1] + '\n';
	std::string	target = split_msg[0];

	if (target[0] == '#') {
		std::map<std::string, User *>::iterator it = server->_channels[target]->_users.begin();
		while (it != server->_channels[target]->_users.end()) {
			if (it->second->_id != i)
				send(server->_fds[it->second->_id].fd, join_response.c_str(), join_response.length(), 0);
			it ++;
		}
	}
	else {
		while (n <= server->getNbUsers()) {
			if (n != i && (server->_users[n - 1]->getNickname() == target))
				send(server->_fds[n].fd, join_response.c_str(), join_response.length(), 0);
			n ++;
		}
	}
}

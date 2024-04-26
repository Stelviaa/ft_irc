/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:43:14 by mboyer            #+#    #+#             */
/*   Updated: 2024/04/26 14:28:29 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"
#include "../../includes/irc.hpp"

void	join_rpl(Server *server, int i, std::string name) {
	
	std::string	join_response = ":" + server->_users[i - 1]->getNickname() + " JOIN " + name + "\r\n";
	send(server->_fds[i].fd, join_response.c_str(), join_response.size(), 0);
	if (!server->_channels[name]->_topic.empty()) {
		std::string	topic =  name + " " + server->_channels[name]->_topic; 
		send(server->_fds[i].fd, topic.c_str(), topic.size(), 0);
	}
	else {
		std::string	err = name + " :No topic is set\n";
		send(server->_fds[i].fd, err.c_str(), err.size(), 0);
	}
	std::string	names = name + " :";
	std::map<std::string, User *>::iterator	it = server->_channels[name]->_users.begin();
	while (it != server->_channels[name]->_users.end()) {
		names += it->first + " ";
		it++;
	}
	names += "\n";
	send(server->_fds[i].fd, names.c_str(), names.size(), 0);
}

void	process_join_cmd(Server *server, std::vector<std::string> splitted, int i) {
	if (!(splitted[0][0] == '#'))
		return ; // erreur ici ?

	std::string	name = splitted[0];
	std::string	join_response = ":" + server->_users[i - 1]->getNickname() + " JOIN " + name + "\r\n";
	if (server->_channels.find(name) == server->_channels.end())
		server->_channels[name] = new Channel(name, server->_users[i - 1]);
	else {
		if (server->_channels[name]->_mode & K_PASS) {
			if (splitted.size() <= 1) {
				err_cannot_join_chan(server, splitted[0], i, 'k');
				return ;
			}
			if (splitted[1] != server->_channels[name]->getPassword()) {
				err_cannot_join_chan(server, splitted[0], i, 'k');
				return ;
			}
		}
		if ((server->_channels[name]->_mode & U_LIMITS) && (server->_channels[name]->_userLimit >= server->_channels[name]->_users.size())) {
			err_cannot_join_chan(server, splitted[0], i, 'l');
			return ;
		}
		if (server->_channels[name]->_mode & I_ONLY){
			size_t j = 0;
			while (j < server->_channels[name]->_invitedUsers.size())
			{
				if (server->_channels[name]->_invitedUsers[j] == server->_users[i - 1]->getNickname())
					break ;
				j ++;
			}
			if (j == server->_channels[name]->_invitedUsers.size())
			{
				err_cannot_join_chan(server, splitted[0], i, 'i');
				return ;
			}
		}
		server->_channels[name]->AddUsers(server->_users[i - 1]);
		server->_users[i - 1]->_channels.push_back(name);
	}
	join_rpl(server, i, name);
}

void	join_cmd(Server *server, std::vector<std::string> splitted, int i) {
	if (splitted.empty()) {
		err_need_more_params(server, "JOIN", i);
		return ;
	}
	if (splitted[0].find(',') != std::string::npos) {
		std::istringstream	iss1(splitted[0]);
		std::string			word;
		while (std::getline(iss1, word, ',')) {
			std::vector<std::string>	tmp;
			tmp.push_back(word);
			if (splitted.size() > 1 && !splitted[1].empty()) {
				std::istringstream	iss2(splitted[1]);
				std::getline(iss2, word, ',');
				tmp.push_back(word);
			}
			process_join_cmd(server, tmp, i);
		}
	}
	else
		process_join_cmd(server, splitted, i);
}

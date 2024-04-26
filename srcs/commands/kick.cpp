/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 12:26:14 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/26 16:32:10 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	kick_cmd(Server *server, std::vector<std::string> splitted, int i) {
	if (splitted.size() < 2) {
		err_need_more_params(server, "KICK", i);
		return ;
	}
	if (!(splitted[0][0] == '#'))
		return ; // erreur ici ?
	
	std::string	chan = get_name(splitted[0]);
	std::string	name = get_name(splitted[1]);
	std::string	kick_msg = ":" + server->_users[i - 1]->getNickname() + " KICK " + chan + "\r\n";
	if (server->_channels.find(chan) != server->_channels.end()) {
		if (server->_channels[chan]->is_op(server->_users[i - 1]) != -1) {
			if (server->_channels[chan]->_users.find(name) != server->_channels[chan]->_users.end()) {
				send(server->_fds[i].fd, "This user has been kicked\n", 27, 0);
				if (splitted.size() == 3) {
					std::string msg = "You have been kicked " + splitted[2] + "\n";
					send(server->_fds[server->_channels[chan]->_users[name]->_id].fd, msg.c_str(), msg.size(), 0);
				}
				else
					send(server->_fds[server->_channels[chan]->_users[name]->_id].fd, "You have been kicked\n", 22, 0);
				server->_channels[chan]->_users.erase(name);
				server->_users[server->is_Users(name) - 1]->removeChannel(chan);
				if (server->_channels[chan]->_users.size() == 0)
				{
					Channel *tmp = server->_channels[chan];
					server->_channels.erase(server->_channels.find(chan));
					delete tmp;
				}
			}
			else
				err_user_not_in_chan(server, splitted[1], splitted[0], i);
		}
		else
			err_not_operator(server, splitted[0], i);
	}
	else
		err_no_such_channel(server, splitted[0], i);
	send(server->_fds[i].fd, kick_msg.c_str(), kick_msg.length(), 0);
}

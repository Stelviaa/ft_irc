/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:08:43 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/11 12:36:40 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	topic_cmd(Server *server, std::vector<std::string> split_msg, int i) {
	if (split_msg.empty()) {
		err_need_more_params(server, "TOPIC", i);
		return ;
	}
	std::string	chan = split_msg[0];
	if (server->_channels.find(chan) == server->_channels.end()) {
		err_no_such_channel(server, split_msg[0], i);
		return ;
	}
	if (split_msg.size() == 1) {
		if (!server->_channels[chan]->_topic.empty()) {
			send(server->_fds[i].fd, server->_channels[chan]->_topic.c_str(), server->_channels[chan]->_topic.size(), 0);
		}
		else {
			std::string	err = split_msg[0] + " :No topic is set\n";
			send(server->_fds[i].fd, err.c_str(), err.size(), 0);
		}
	}
	if (split_msg.size() >= 2) {
		if ((server->_channels[chan]->_mode & T_OP) && server->_channels[chan]->is_op(server->_users[i - 1]) == -1) {
			err_not_operator(server, split_msg[0], i);
			return ;
		}
		server->_channels[chan]->_topic = split_msg[1] + "\n";
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:08:45 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/23 18:32:21 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	invite_cmd(Server *server, std::vector<std::string> split_msg, int i) {
	std::string	err_message = "";
	if (split_msg.size() < 2) {
		send(server->_fds[i].fd, "INVITE :Not enough parameters\n", 31, 0);
		return ;
	}
	if (!server->is_Users(split_msg[0])) {
		err_message += split_msg[0] + " :No such nick\n";
		send(server->_fds[i].fd, err_message.c_str(), err_message.size(), 0);
		return;
	}
	if (server->_channels.find(split_msg[1]) != server->_channels.end()) {
		if (server->_channels[split_msg[1]]->_users.find(server->_users[i - 1]->getNickname()) == server->_channels[split_msg[1]]->_users.end()) {
			err_message += split_msg[1] + " :You're not on that channel\n";
			send(server->_fds[i].fd, err_message.c_str(), err_message.size(), 0);
			return ;
		}
		if (server->_channels[split_msg[1]]->_users.find(split_msg[0]) != server->_channels[split_msg[1]]->_users.end()) {
			err_message += split_msg[1] + " " + split_msg[0] + " :is already on channel\n";
			send(server->_fds[i].fd, err_message.c_str(), err_message.size(), 0);
			return ;
		}
		if (server->_channels[split_msg[1]]->_mode & I_ONLY && server->_channels[split_msg[1]]->is_op(server->_users[i - 1]) == -1) {
			err_message += split_msg[1] + " :You're not channel operator\n";
			send(server->_fds[i].fd, err_message.c_str(), err_message.size(), 0);
			return;
		}
		server->_channels[split_msg[1]]->_invitedUsers.push_back(split_msg[0]);
	}
	std::string	inv_msg = server->_users[i - 1]->getNickname() + " invited you to " + split_msg[1] + "\n";
	send(server->_fds[server->is_Users(split_msg[0])].fd, inv_msg.c_str(), inv_msg.size(), 0);
	err_message += split_msg[1] + " " + split_msg[0] + "\n";
	send(server->_fds[i].fd, err_message.c_str(), err_message.size(), 0);
}

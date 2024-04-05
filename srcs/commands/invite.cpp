/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:08:45 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/05 16:31:51 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	invite_cmd(Server *server, std::vector<std::string> split_msg, int i)
{
	std::string err_message = "";
	
	if (split_msg.size() < 2) {
		send(server->_fds[i].fd, "INVITE :Not enough parameters\n", 31, 0);
		return ;
	}
	if (!server->is_Users(split_msg[0]))
	{
		err_message += split_msg[0];
		err_message += " :No such nick\n";
		send(server->_fds[i].fd, err_message.c_str(), err_message.size(), 0);
		return;
	}
	if (server->_channels.find(split_msg[1]) != server->_channels.end())
	{
		if (server->_channels[split_msg[1]]->_users.find(server->_users[i - 1]->getUsername()) == server->_channels[split_msg[1]]->_users.end())
		{
			err_message += split_msg[1];
			err_message += " :You're not on that channel\n";
			send(server->_fds[i].fd, err_message.c_str(), err_message.size(), 0);
			return ;
		}
		if (server->_channels[split_msg[1]]->_users.find(split_msg[0]) != server->_channels[split_msg[1]]->_users.end())
		{
			err_message += split_msg[1];
			err_message += " ";
			err_message += split_msg[0];
			err_message += " :is already on channel\n";
			send(server->_fds[i].fd, err_message.c_str(), err_message.size(), 0);
			return ;
		}
		if (server->_channels[split_msg[1]]->_mode & I_ONLY && !server->_channels[split_msg[1]]->is_op(server->_users[i - 1]))
		{
			err_message += split_msg[1];
			err_message += " :You're not channel operator\n";
			send(server->_fds[i].fd, err_message.c_str(), err_message.size(), 0);
			return;
		}
		server->_channels[split_msg[1]]->_invitedUsers.push_back(split_msg[0]);
	}

	std::string inv_msg = "";
	inv_msg += server->_users[i - 1]->getUsername();
	inv_msg += " invited you to ";
	inv_msg += split_msg[1];
	inv_msg += "\n";
	send(server->_fds[server->is_Users(split_msg[0])].fd, inv_msg.c_str(), inv_msg.size(), 0);
	err_message += split_msg[1];
	err_message += " ";
	err_message += split_msg[0];
	err_message += "\n";
	send(server->_fds[i].fd, err_message.c_str(), err_message.size(), 0);
}
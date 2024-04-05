/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:08:43 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/05 10:52:21 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	topic_cmd(Server *server, std::vector<std::string> split_msg, int i)
{
	if (split_msg.empty()) {
		send(server->_fds[i].fd, "TOPIC error: missing parameters\n", 32, 0);
		//<canal> [<sujet>]
		return ;
	}
	std::string chan = split_msg[0];
	if (server->_channels.find(chan) == server->_channels.end())
	{
		send(server->_fds[i].fd, "This channel doesn't exist\n", 28, 0);
		return ;
	}
	if (split_msg.size() == 1)
	{
		if (!server->_channels[chan]->_topic.empty())
		{
			send(server->_fds[i].fd, server->_channels[chan]->_topic.c_str(), server->_channels[chan]->_topic.size(), 0);
		}
		else
			send(server->_fds[i].fd, "This channel don't have any topic\n", 35, 0);
	}
	if (split_msg.size() >= 2)
	{
		if ((server->_channels[chan]->_mode & T_OP) && !server->_channels[chan]->is_op(server->_users[i - 1]))
		{
			send(server->_fds[i].fd, "You are not operator on this channel\n", 38, 0);
			return ;
		}
		server->_channels[chan]->_topic = split_msg[1];
	}
}
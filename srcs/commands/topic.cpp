/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:08:43 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/03 01:53:34 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	topic_cmd(Server *server, std::string buffer, int i)
{
	std::vector<std::string> split_msg;

	split_msg = ft_split(buffer, ' ');
	std::string chan = get_name(split_msg[1]);
	if (server->_channels.find(chan) == server->_channels.end())
	{
		send(server->_fds[i].fd, "This channel doesn't exist\n", 28, 0);
		return ;
	}
	if (split_msg.size() == 2)
	{
		if (!server->_channels[chan]->_topic.empty())
		{
			send(server->_fds[i].fd, server->_channels[chan]->_topic.c_str(), server->_channels[chan]->_topic.size(), 0);
		}
		else
			send(server->_fds[i].fd, "This channel don't have any topic\n", 35, 0);
	}
	if (split_msg.size() == 3)
	{
		if ((server->_channels[chan]->_mode & T_OP) && !server->_channels[chan]->is_op(server->_users[i - 1]))
		{
			send(server->_fds[i].fd, "You are not operator on this channel\n", 38, 0);
			return ;
		}
		server->_channels[chan]->_topic = split_msg[2];
	}
}
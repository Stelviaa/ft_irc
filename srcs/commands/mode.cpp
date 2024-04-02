/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:30:05 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/03 01:57:04 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void mode_cmd(Server *server, std::string buffer, int i)
{
	(void)server;
	(void)i;
	
	std::vector<std::string> split_msg;
	std::string	chan;

	split_msg = ft_split(buffer, ' ');
	if (split_msg.size() <= 2)
		return;
	chan = get_name(split_msg[1]);
	if (server->_channels.find(chan) == server->_channels.end())
	{
		send(server->_fds[i].fd, "This channel doesn't exist\n", 28, 0);
		return ;
	}
	if (!server->_channels[chan]->is_op(server->_users[i - 1]))
	{
		send(server->_fds[i].fd, "You are not operator on this channel\n", 38, 0);
		return ;
	}
	if (split_msg[2][0] == '+')
	{
		if (split_msg[2].find("i")  != std::string::npos)
			server->_channels[chan]->_mode |= I_ONLY;
		if (split_msg[2].find("t")  != std::string::npos)
			server->_channels[chan]->_mode |= T_OP;
		if (split_msg[2].find("k")  != std::string::npos)
		{
			server->_channels[chan]->_mode |= K_PASS;
			server->_channels[chan]->setPassword(get_name(split_msg[3]));
		}
		if (split_msg[2].find("l")  != std::string::npos)
		{
			server->_channels[chan]->_mode |= U_LIMITS;
			server->_channels[chan]->_userLimit = std::atoi(split_msg[3].c_str());
		}
		if (split_msg[2].find("o")  != std::string::npos)
		{
			if (server->_channels[chan]->_users.find(get_name(split_msg[3])) == server->_channels[chan]->_users.end())
				send(server->_fds[i].fd, "This user isn't in this channel\n", 33, 0);
			else
				server->_channels[chan]->_op.push_back(server->_channels[chan]->_users[get_name(split_msg[3])]);	
		}
	}
}
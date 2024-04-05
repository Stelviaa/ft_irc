/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:30:05 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/05 17:16:18 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

int	mode_cmd_c(std::vector<std::string> &split_msg) {}

void mode_cmd(Server *server, std::vector<std::string> split_msg, int i)
{
	std::string	chan;

	if (split_msg.size() <= 1)
		return;
	chan = get_name(split_msg[0]);
	if (server->_channels.find(chan) == server->_channels.end())
	{
		err_no_such_channel(server, split_msg[0], i);
		return ;
	}
	if (!server->_channels[chan]->is_op(server->_users[i - 1]))
	{
		err_not_operator(server, split_msg[0], i);
		return ;
	}
	if (split_msg[1][0] == '+')
	{
		if (split_msg[1].find("i")  != std::string::npos)
			server->_channels[chan]->_mode |= I_ONLY;
		if (split_msg[1].find("t")  != std::string::npos)
			server->_channels[chan]->_mode |= T_OP;
		if (split_msg[1].find("k")  != std::string::npos)
		{
			server->_channels[chan]->_mode |= K_PASS;
			server->_channels[chan]->setPassword(get_name(split_msg[2]));
		}
		if (split_msg[1].find("l")  != std::string::npos)
		{
			server->_channels[chan]->_mode |= U_LIMITS;
			server->_channels[chan]->_userLimit = std::atoi(split_msg[2].c_str());
		}
		if (split_msg[1].find("o")  != std::string::npos)
		{
			if (server->_channels[chan]->_users.find(get_name(split_msg[2])) == server->_channels[chan]->_users.end())
				err_user_not_in_chan(server, split_msg[2], split_msg[0], i); //split_msg a changer par user
			else
				server->_channels[chan]->_op.push_back(server->_channels[chan]->_users[get_name(split_msg[2])]);
		}
	}
}

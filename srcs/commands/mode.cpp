/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:30:05 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/08 10:00:50 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void mode_cmd(Server *server, std::string buffer, int i)
{
	(void)server;
	(void)i;
	
	std::vector<std::string> split_msg;
	std::string	chan;

	if (split_msg.empty() || split_msg.size() < 2) {
		err_need_more_params(server, "MODE", i);
		return (param);
	}
	param.chan = split_msg[0];
	param.mods = split_msg[1];
	for (size_t k = 0; k < param.mods.size(); k++) {
		if (param.mods[k] != 'i' && param.mods[k] != 't' && param.mods[k] != 'k' && param.mods[k] != 'l' &&
			param.mods[k] != 'o' && param.mods[k] != '+' && param.mods[k] != '-') {
				std::string	err = param.mods[k] + std::string(" :is unknown mode char to me\n");
				send(server->_fds[i].fd, err.c_str(), err.size(), 0);
		}
	}
	if (param.mods.find("k") != std::string::npos)
		param.pass = split_msg[j++];
	if (param.mods.find("l") != std::string::npos)
		param.limit = split_msg[j++];
	if (param.mods.find("o") != std::string::npos)
		param.user = split_msg[j++];
	if (server->_channels.find(param.chan) == server->_channels.end()) {
		err_no_such_channel(server, param.chan, i);
		param.chan = "";
		return (param);
	}
	if (!server->_channels[param.chan]->is_op(server->_users[i - 1])) {
		err_not_operator(server, param.chan, i);
		param.chan = "";
		return (param);
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
			if (server->_channels[p.chan]->_users.find(p.user) == server->_channels[p.chan]->_users.end())
				err_user_not_in_chan(server, p.user, p.chan, i);
			else
				server->_channels[p.chan]->_op.push_back(server->_channels[p.chan]->_users[p.user]);
		}
	}
	if (split_msg[1][0] == '-')
	{
		if (split_msg[1].find("i")  != std::string::npos && server->_channels[p.chan]->_mode & I_ONLY)
			server->_channels[p.chan]->_mode ^= I_ONLY;
		if (split_msg[1].find("t")  != std::string::npos && server->_channels[p.chan]->_mode & T_OP)
			server->_channels[p.chan]->_mode ^= T_OP;
		if (split_msg[1].find("k")  != std::string::npos && server->_channels[p.chan]->_mode & K_PASS)
			server->_channels[p.chan]->_mode ^= K_PASS;
		if (split_msg[1].find("l")  != std::string::npos && server->_channels[p.chan]->_mode & U_LIMITS)
			server->_channels[p.chan]->_mode ^= U_LIMITS;
		/*if (split_msg[1].find("o")  != std::string::npos)
		{
			if (server->_channels[chan]->_users.find(get_name(split_msg[2])) == server->_channels[chan]->_users.end())
>>>>>>> Stashed changes
				send(server->_fds[i].fd, "This user isn't in this channel\n", 33, 0);
			else
				server->_channels[chan]->_op.push_back(server->_channels[chan]->_users[get_name(split_msg[3])]);	
		}
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:30:05 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/06 19:52:47 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

typedef struct s_param {
	std::string	chan;
	std::string mods;
	std::string	pass;
	std::string	limit;
	std::string	user;
}				t_param;

t_param	mode_cmd_param_check(Server *server, std::vector<std::string> &split_msg, int i) {
	t_param	param;
	int		j = 2;

	if (split_msg.empty() || split_msg.size() < 2) {
		err_need_more_params(server, "MODE", i);
		return (param);
	}
	param.chan = split_msg[0];
	param.mods = split_msg[1];
	for (size_t k = 0; k < param.mods.size(); k++) {
		if (param.mods[k] != 'i' && param.mods[k] != 't' && param.mods[k] != 'k' && param.mods[k] != 'l' &&
			param.mods[k] != 'o' && param.mods[k] != '+' && param.mods[k] != '-') {
				std::string	err = param.mods[k] + " :is unknow mode char to me\n";
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
	if (server->_channels[param.chan]->is_op(server->_users[i - 1]) == -1) {
		err_not_operator(server, param.chan, i);
		param.chan = "";
		return (param);
	}
	return (param);
}

void mode_cmd(Server *server, std::vector<std::string> split_msg, int i)
{
	t_param	p = mode_cmd_param_check(server, split_msg, i);
	if (p.chan.empty())
		return ;

	if (p.mods[0] == '+')
	{
		if (p.mods.find("i")  != std::string::npos)
			server->_channels[p.chan]->_mode |= I_ONLY;
		if (p.mods.find("t")  != std::string::npos)
			server->_channels[p.chan]->_mode |= T_OP;
		if (p.mods.find("k")  != std::string::npos)
		{
			server->_channels[p.chan]->_mode |= K_PASS;
			server->_channels[p.chan]->setPassword(p.pass);
		}
		if (p.mods.find("l")  != std::string::npos)
		{
			server->_channels[p.chan]->_mode |= U_LIMITS;
			server->_channels[p.chan]->_userLimit = std::atoi(p.limit.c_str());
		}
		if (p.mods.find("o")  != std::string::npos)
		{
			if (server->_channels[p.chan]->_users.find(p.user) == server->_channels[p.chan]->_users.end())
				err_user_not_in_chan(server, p.user, p.chan, i);
			else
				server->_channels[p.chan]->_op.push_back(server->_channels[p.chan]->_users[p.user]);
		}
	}
	if (p.mods[0] == '-')
	{
		if (p.mods.find("i")  != std::string::npos && server->_channels[p.chan]->_mode & I_ONLY)
			server->_channels[p.chan]->_mode ^= I_ONLY;
		if (p.mods.find("t")  != std::string::npos && server->_channels[p.chan]->_mode & T_OP)
			server->_channels[p.chan]->_mode ^= T_OP;
		if (p.mods.find("k")  != std::string::npos && server->_channels[p.chan]->_mode & K_PASS)
			server->_channels[p.chan]->_mode ^= K_PASS;
		if (p.mods.find("l")  != std::string::npos && server->_channels[p.chan]->_mode & U_LIMITS)
			server->_channels[p.chan]->_mode ^= U_LIMITS;
		if (p.mods.find("o")  != std::string::npos)
		{
			int index;
			if (server->_channels[p.chan]->_users.find(p.user) == server->_channels[p.chan]->_users.end())
				err_user_not_in_chan(server, p.user, p.chan, i);
			index = server->_channels[p.chan]->is_op(server->_channels[p.chan]->_users[p.user]);
			if (index != -1)
				server->_channels[p.chan]->_op.erase(server->_channels[p.chan]->_op.erase(server->_channels[p.chan]->_op.begin() + index));
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 12:54:49 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/11 12:38:59 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Commands.hpp"

int	is_valid_command(std::string cmd) {
	if (cmd == "NICK" || cmd == "JOIN" || cmd == "QUIT" || cmd == "PRIVMSG" ||
		cmd == "KICK" || cmd == "TOPIC" || cmd == "MODE" || cmd == "INVITE" || 
		cmd == "USER" || cmd == "PASS")
		return (1);
	return (0);
}

std::vector<std::string>	commands_split(std::string raw_cmd) {
	std::vector<std::string>	split_cmd;
	std::istringstream			iss(raw_cmd);
	std::string					tmp;

	while (iss >> tmp) {
		split_cmd.push_back(tmp);
		if (tmp[0] == ':') {
			std::string	line;
			std::getline(iss, line);
			split_cmd.back() += line;
			break ;
		}
	}
	if (!split_cmd.empty())
		split_cmd.back() = get_name(split_cmd.back());
	return (split_cmd);
}

s_command	commands_parsing(std::string raw_cmd) {
	t_command					command;
	std::vector<std::string>	split_cmd = commands_split(raw_cmd);

	if (!split_cmd.empty() && is_valid_command(split_cmd[0]) == 1) {
		command.cmd = split_cmd[0];
		command.args.assign(split_cmd.begin() + 1, split_cmd.end());
	}
	else if (split_cmd.size() > 1 && is_valid_command(split_cmd[1]) == 1) {
		command.prefix = split_cmd[0];
		command.cmd = split_cmd[1];
		command.args.assign(split_cmd.begin() + 2, split_cmd.end());
	}
	return (command);
}

void	commands(Server *server, std::string buffer, int i) {
	t_command	command = commands_parsing(std::string(buffer));

	if (command.cmd.empty())
		send(server->_fds[i].fd, "Error: invalid command\n", 23, 0);
	else if (command.cmd == "QUIT")
		quit_cmd(server, command.args, i);
	else if (command.cmd == "PASS")
		pass_cmd(server, command.args, i);
	else if (server->_users[i - 1]->getStatus() == 0 && !server->_pass.empty()) {
		send(server->_fds[i].fd, "You have to connect using the command : PASS <password>\n", 57, 0);
		return ;
	}
	else if (command.cmd == "NICK")
		nick_cmd(server, command.args, i);
	else if (server->_users[i - 1]->getNickname().empty()) {
		send(server->_fds[i].fd, "You have to identify using the command : NICK <nickname>\n", 58, 0);
		return ;
	}
	else if (command.cmd == "JOIN")
		join_cmd(server, command.args, i);
	else if (command.cmd == "PRIVMSG")
		privmsg_cmd(server, command.args, i);
	else if (command.cmd == "KICK")
		kick_cmd(server, command.args, i);
	else if (command.cmd == "TOPIC")
		topic_cmd(server, command.args, i);
	else if (command.cmd == "INVITE")
		invite_cmd(server, command.args, i);
	else if (command.cmd == "MODE")
		mode_cmd(server, command.args, i);
}

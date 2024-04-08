/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 12:54:49 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/08 11:20:26 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Commands.hpp"

void commands(Server *server, char buffer[1024], int i)
{
	if (cmd == "NICK" || cmd == "JOIN" || cmd == "QUIT" || cmd == "PRIVMSG" ||
		cmd == "KICK" || cmd == "TOPIC" || cmd == "MODE" || cmd == "INVITE" ||
		cmd == "PASS" || cmd == "QUIT" || cmd == "CAP")
		return (1);
	return (0);
}

std::vector<std::string>	commands_split(std::string raw_cmd)
{
	std::vector<std::string>	split_cmd;
	std::istringstream			iss(raw_cmd);
	std::string					tmp;

	while (iss >> tmp)
>>>>>>> Stashed changes
	{
		server->_users[i - 1]->parseName(buffer);
	}
<<<<<<< Updated upstream
	if (std::string(buffer).find("JOIN") != std::string::npos)
		join_cmd(server, buffer, i);
	if (std::string(buffer).find("QUIT") != std::string::npos)
=======
	if (!split_cmd.empty())
		split_cmd.back() = get_name(split_cmd.back());
	return (split_cmd);
}

s_command	commands_parsing(std::string raw_cmd)
{
	t_command					command;
	std::vector<std::string>	split_cmd = commands_split(raw_cmd);

	// std::cout << "vector :" << std::endl;
	// for (std::vector<std::string>::iterator it = split_cmd.begin(); it != split_cmd.end(); ++it)
	// std::cout << *it << std::endl;

	if (!split_cmd.empty() && is_valid_command(split_cmd[0]) == 1)
	{
		//command.prefix = "";
		command.cmd = split_cmd[0];
		command.args.assign(split_cmd.begin() + 1, split_cmd.end());
	}
	else if (split_cmd.size() > 1 && is_valid_command(split_cmd[1]) == 1)
	{
		command.prefix = split_cmd[0];
		command.cmd = split_cmd[1];
		command.args.assign(split_cmd.begin() + 2, split_cmd.end());
	}
	//else
	//	command.cmd = "";
	return (command);
}

void	commands(Server *server, std::string buffer, int i)
{
	t_command	command = commands_parsing(buffer);

	// std::cout << "structure :" << std::endl;
	// std::cout << "prefix:\t" << command.prefix << std::endl;
	// std::cout << "cmd:\t" << command.cmd << std::endl;
	// for (std::vector<std::string>::iterator it = command.args.begin(); it != command.args.end(); ++it)
	// std::cout << *it << std::endl;
	
	if (command.cmd.empty())
	{
		send(server->_fds[i].fd, "Error: invalid command\n", 23, 0);
	}
	else if (command.cmd == "NICK")
		nick_cmd(server, command.args, i);
	else if (command.cmd == "JOIN")
		join_cmd(server, command.args, i);
	else if (command.cmd == "QUIT")
>>>>>>> Stashed changes
	{
		delete server->_users[i - 1];
		if (i != server->getNbUsers())
		{
			server->_users[i -1] = server->_users[server->getNbUsers() - 1];
			server->_users[i - 1]->_id = i - 1;
			server->_users[server->getNbUsers() - 1] = 0;
			server->_fds[i] = server->_fds[server->getNbUsers()];
		}
		server->RemoveUser();
	}
	if (std::string(buffer).find("PRIVMSG") != std::string::npos)
		privmsg_cmd(server, buffer, i);
	if (std::string(buffer).find("KICK") != std::string::npos)
		kick_cmd(server, buffer, i);
	if (std::string(buffer).find("TOPIC") != std::string::npos)
		topic_cmd(server, buffer, i);
	if (std::string(buffer).find("MODE") != std::string::npos)
		mode_cmd(server, buffer, i);
}
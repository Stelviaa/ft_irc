/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:25:21 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/03 14:57:02 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <vector>
# include <string>
# include <sstream>
# include "Server.hpp"
# include <cstdlib>

typedef struct s_command
{
	std::string					prefix;
	std::string					cmd;
	std::vector<std::string>	args;

}				t_command;

void	commands(Server *server, char buffer[1024], int i);
void	join_cmd(Server *server, std::vector<std::string> splitted, int i);
void	kick_cmd(Server *server, std::vector<std::string> splitted, int i);
void	privmsg_cmd(Server *server, std::vector<std::string> param, int i);
void 	send_all_fd(Server *server, std::string msg, int i);
void	topic_cmd(Server *server, std::vector<std::string> split_msg, int i);
void 	mode_cmd(Server *server, std::vector<std::string> split_msg, int i);

#endif
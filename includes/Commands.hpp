/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:25:21 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/08 12:21:48 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <vector>
# include <string>
# include "Server.hpp"
# include <cstdlib>

typedef struct s_command
{
	std::string					prefix;
	std::string					cmd;
	std::vector<std::string>	args;

}				t_command;

void	commands(Server *server, std::string buffer, int i);
void	nick_cmd(Server *server, std::vector<std::string> param, int i);
void	join_cmd(Server *server, std::vector<std::string> splitted, int i);
void	kick_cmd(Server *server, std::vector<std::string> splitted, int i);
void	privmsg_cmd(Server *server, std::vector<std::string> param, int i);
void 	send_all_fd(Server *server, std::vector<std::string> split_msg, int i);
void	topic_cmd(Server *server, std::vector<std::string> split_msg, int i);
void	invite_cmd(Server *server, std::vector<std::string> split_msg, int i);
void 	mode_cmd(Server *server, std::vector<std::string> split_msg, int i);

void	err_need_more_params(Server *server, std::string cmd, int i);
void	err_cannot_join_chan(Server *server, std::string chan, int i, char c);
void	err_not_operator(Server *server, std::string chan, int i);
void	err_no_such_channel(Server *server, std::string chan, int i);
void	err_user_not_in_chan(Server *server, std::string user, std::string chan, int i);


#endif
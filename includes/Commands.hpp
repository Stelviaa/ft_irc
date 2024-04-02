/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:25:21 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/02 00:26:12 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <vector>
# include <string>
# include "Server.hpp"
# include <cstdlib>

void	commands(Server *server, char buffer[1024], int i);
void	join_cmd(Server *server, std::string buffer, int i);
void	kick_cmd(Server *server, std::string buffer, int i);
void	privmsg_cmd(Server *server, std::string buffer, int i);
void 	send_all_fd(Server *server, std::string msg, int i);
void	topic_cmd(Server *server, std::string buffer, int i);
void 	mode_cmd(Server *server, std::string buffer, int i);

#endif
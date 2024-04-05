/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:03:50 by mpelazza          #+#    #+#             */
/*   Updated: 2024/04/05 18:22:51 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Commands.hpp"

void	err_need_more_params(Server *server, std::string cmd, int i) {
	std::string	err = cmd + " :Not enough parameters\n";
	send(server->_fds[i].fd, err.c_str(), err.size(), 0);
}

void	err_cannot_join_chan(Server *server, std::string chan, int i, char c) {
	std::string	err = chan + " :Cannot join channel (+" + c + ")\n";
	send(server->_fds[i].fd, err.c_str(), err.size(), 0);
}

void	err_no_such_channel(Server *server, std::string chan, int i) {
	std::string	err = chan + " :No such channel\n";
	send(server->_fds[i].fd, err.c_str(), err.size(), 0);
}

void	err_not_operator(Server *server, std::string chan, int i) { // ERR_CHANOPRIVSNEEDED
	std::string	err = chan + " :You're not channel operator\n";
	send(server->_fds[i].fd, err.c_str(), err.size(), 0);
}

void	err_user_not_in_chan(Server *server, std::string user, std::string chan, int i) {
	std::string	err = user + " " + chan + " :Users aren't on channel\n";
	send(server->_fds[i].fd, err.c_str(), err.size(), 0);
}

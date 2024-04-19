/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:57:28 by sforesti          #+#    #+#             */
/*   Updated: 2024/04/19 12:03:10 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <netinet/in.h>
# include "Channel.hpp"
# include "User.hpp"
# include "irc.hpp"
# include "poll.h"
# include <vector>
# include <map>

extern bool	close_server;

class Server {
	private:
		int					_fd;
		struct sockaddr_in	_address;
		int					_lenAddress;
		int					_nbUsers;

	public:
		Server(int port, std::string pass);
		~Server();

		std::string							_pass;
		struct pollfd						_fds[4096];
		std::vector<User *>					_users;
		std::map<std::string , Channel *>	_channels;
		

		void				RemoveUser();
		void				AddUsers();
		void				CheckSocket();
		void				CheckConnection();
		void				log_in(std::string buffer, int i);
		void				kickUser(int id);
		void				close_serv();
		int					getFd() const;
		int					is_Users(std::string _nick);
		int					getNbUsers();
		int					*getLenAddress();
		struct sockaddr_in	*getAddress();
};

#endif

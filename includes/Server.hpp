/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:32:47 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/29 16:05:29 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include <netinet/in.h>
# include "User.hpp"
# include "irc.hpp"
# include "poll.h"
# include <vector>

extern bool close_server;

class Server{

    private:
        int                 _fd;
        struct sockaddr_in  _address;
        int                 _lenAddress;
        int                 _nbUsers;
        struct pollfd       _fds[4096];
    
    public:
        Server(int port);
        ~Server();
        std::vector<User *>   _users;
        int getFd() const;
        struct sockaddr_in *getAddress();
        void    send_all_fd(std::string msg, int i);
        void    close_serv();
        int getNbUsers();
        int *getLenAddress();
        void RemoveUser();
        void AddUsers();
        void CheckSocket();
        void CheckConnection();
};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:32:47 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/29 10:36:34 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include <netinet/in.h>
# include "User.hpp"
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
        std::string	prv_format(std::string buffer);
        void    close_serv();
        int getNbUsers();
        int *getLenAddress();
        void RemoveUser();
        void AddUsers();
        void CheckSocket();
        void CheckConnection();
};

#endif
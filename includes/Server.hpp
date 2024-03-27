/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:32:47 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/27 16:28:20 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <netinet/in.h>
#include "User.hpp"
#include "poll.h"
#include <vector>

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
        int getNbUsers();
        int *getLenAddress();
        void RemoveUser();
        void AddUsers();
        void CheckSocket();
        void CheckConnection();
};
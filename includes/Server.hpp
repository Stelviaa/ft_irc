/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:32:47 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/25 16:13:55 by luxojr           ###   ########.fr       */
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
    
    public:
        Server(int port);
        ~Server();
        std::vector<User *>   _users;
        int getFd() const;
        struct sockaddr_in *getAddress();
        int getNbUsers();
        int *getLenAddress();
        void AddUsers();
        void CheckSocket();
        void CheckConnection();
};
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:32:47 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/31 22:17:43 by luxojr           ###   ########.fr       */
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

extern bool close_server;

class Server
{

    private:
        int                 _fd;
        struct sockaddr_in  _address;
        int                 _lenAddress;
        int                 _nbUsers;
        std::string         _pass;
    
    public:
        struct pollfd       _fds[4096];
        Server(int port, std::string pass);
        ~Server();
        std::vector<User *>   _users;
        std::map<std::string , Channel *>   _channels;
        int getFd() const;
        struct sockaddr_in *getAddress();
        void    close_serv();
        void    log_in(std::string buffer, int i);
        int getNbUsers();
        int *getLenAddress();
        void RemoveUser();
        void AddUsers();
        void CheckSocket();
        void CheckConnection();
};

#endif
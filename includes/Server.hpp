/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:32:47 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/30 18:19:12 by luxojr           ###   ########.fr       */
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

extern bool close_server;

class Server
{

    private:
        int                 _fd;
        struct sockaddr_in  _address;
        int                 _lenAddress;
        int                 _nbUsers;
        std::string         _pass;
        struct pollfd       _fds[4096];
        std::vector<Channel *>   _channels;
    
    public:
        Server(int port, std::string pass);
        ~Server();
        std::vector<User *>   _users;
        int getFd() const;
        struct sockaddr_in *getAddress();
        void    send_all_fd(std::string msg, int i);
        void    close_serv();
        void    commands(char buffer[1024], int i);
        void    log_in(std::string buffer, int i);
        int getNbUsers();
        int *getLenAddress();
        void RemoveUser();
        void AddUsers();
        void CheckSocket();
        void CheckConnection();
};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:32:47 by sforesti          #+#    #+#             */
/*   Updated: 2024/04/10 17:47:54 by luxojr           ###   ########.fr       */
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
    
    public:
        std::string         _pass;
        struct pollfd       _fds[4096];
        Server(int port, std::string pass);
        ~Server();
        std::vector<User *>   _users;
        std::map<std::string , Channel *>   _channels;
        int getFd() const;
        void kickUser(int id);
        struct sockaddr_in *getAddress();
        void    close_serv();
        void    log_in(std::string buffer, int i);
        int     is_Users(std::string _nick);
        int getNbUsers();
        int *getLenAddress();
        void RemoveUser();
        void AddUsers();
        void CheckSocket();
        void CheckConnection();
};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:32:47 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/21 14:33:59 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <netinet/in.h>

class Server{

    private:
        int                 _fd;
        struct sockaddr_in  _address;
        int                 _lenAddress;
    public:
        Server(int port);
        ~Server();

        int getFd() const;
        struct sockaddr_in *getAddress() const;
        int *getLenAddress() const;
};
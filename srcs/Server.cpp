/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:11:22 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/22 13:10:39 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <unistd.h>

Server::Server(int port){

    _lenAddress = sizeof(_address);
    if ((_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = htons(INADDR_ANY);
    _address.sin_port = htons(port);
    
    if (bind(_fd, (struct sockaddr *)&_address, sizeof(_address)) < 0) {
        perror("Erreur lors de l'attachement du socket à l'adresse et au port spécifiés");
        exit(EXIT_FAILURE);
    }
    if (listen(_fd, 3) < 0) {
        perror("Erreur lors de l'écoute des connexions entrantes");
        exit(EXIT_FAILURE);
    }
    std::cout << "Serveur IRC en attente de connexions..." << std::endl;
}

int Server::getFd() const{
    return (_fd);
}

struct sockaddr_in *Server::getAddress(){
    return (&_address);
}

int *Server::getLenAddress(){
    return (&_lenAddress);
}

Server::~Server(){
    close(_fd);
}
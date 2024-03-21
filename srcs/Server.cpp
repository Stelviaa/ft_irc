/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:11:22 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/21 14:38:57 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include <iostream>
#include <stdlib.h>

Server::Server(int port){

    this->_lenAddress = sizeof(this->_address);
    if ((this->_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }
    this->_address.sin_family = AF_INET;
    this->_address.sin_addr.s_addr = htons(INADDR_ANY);
    this->_address.sin_port = htons(port);
    
    if (bind(this->_fd, (struct sockaddr *)&this->_address, sizeof(this->_address)) < 0) {
        perror("Erreur lors de l'attachement du socket à l'adresse et au port spécifiés");
        exit(EXIT_FAILURE);
    }
    if (listen(this->_fd, 1) < 0) {
        perror("Erreur lors de l'écoute des connexions entrantes");
        exit(EXIT_FAILURE);
    }
    std::cout << "Serveur IRC en attente de connexions..." << std::endl;
}

int Server::getFd() const{
    return (_fd);
}

struct sockaddr_in *Server::getAddress() const{
    return (&_address);
}

int *Server::getLenAddress() const{
    return (&_lenAddress);
}

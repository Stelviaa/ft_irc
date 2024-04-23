/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:34:15 by sforesti          #+#    #+#             */
/*   Updated: 2024/04/23 19:45:14 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

Bot::Bot(int port, std::string pass){

    if (port <= 0 || port >= 65536)
	{
		perror("Port invalide");
		exit(EXIT_FAILURE);
	}
    int status;
    struct sockaddr_in serv_addr;
    if ((this->_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        exit(EXIT_FAILURE);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
    if ((status = connect(this->_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        exit(EXIT_FAILURE);
    }
    this->connection(pass);
    this->read_fd();
    
}

void Bot::read_fd()
{   
    int valread = -2;
    while (valread != -1 && valread != 0)
    {
        char buffer[1024] = {0};
        valread = read(this->_fd, buffer, 1024 - 1);
        if (valread != -1 && valread != 0)
        {
            std::string tmp = buffer;
            inviteCommand(tmp, this);
            sendPokemon(tmp, this);   
        }
    }
}

void Bot::connection(std::string pass)
{
    if (!pass.empty())
    {
        std::string con_msg = "PASS " + pass + "\n";
        send(this->_fd, con_msg.c_str(), con_msg.size(), 0);
    }
    std::string id_msg = "NICK bot\nUSER bot\n";
    send(this->_fd, id_msg.c_str(), id_msg.size(), 0);
}

void Bot::openfile()
{
    std::ifstream file("./bot/Pokemon.csv");
    std::string tmp;
    if (!file.is_open())
    {
        std::cerr << "File not open" << std::endl;
        exit(EXIT_FAILURE);
    }
    while (getline(file, tmp, '\n'))
        this->_pokemon.push_back(tmp);
    file.close();
}


std::string Bot::randomPokemon()
{
    std::srand(std::time(0));

    size_t index = std::rand() % 151;
    if (this->_pokemon.size() > index)
        return (this->_pokemon[index]);
    else
        return (std::string("error"));
}

Bot::~Bot(){
    send(this->_fd, "QUIT :Pokebot has left\n", 6, 0);
    close(this->_fd);
}
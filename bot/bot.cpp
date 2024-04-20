/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:34:15 by sforesti          #+#    #+#             */
/*   Updated: 2024/04/20 16:17:05 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

Bot::Bot(int port, std::string pass){

    int status, valread;
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


    char* con_msg = "NICK bot\nUSER bot\n";
    char buffer[1024] = { 0 };
    send(this->_fd, con_msg, strlen(con_msg), 0);
    valread = read(this->_fd, buffer, 1024 - 1);
    printf("%s\n", buffer);
    std::cout << this->_fd << std::endl;
    int i = 0;
    /*while ((i = recv(this->_fd, buffer, 1024, 0)) != -1)
    {
        if ()
    }*/
}

void Bot::connection(std::string pass)
{
    if (pass.empty())
    {
        
    }
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

    int index = std::rand() % 151;
    if (this->_pokemon.size() > index)
        return (this->_pokemon[index]);
    else
        return (std::string("error"));
}

Bot::~Bot(){
    send(this->_fd, "QUIT :Pokebot has left\n", 6, 0);
    close(this->_fd);
}
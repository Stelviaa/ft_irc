/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:41:38 by sforesti          #+#    #+#             */
/*   Updated: 2024/04/23 19:46:17 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

void inviteCommand(std::string line, Bot *bot){
    size_t i = line.find(" invited you to ");
    if (i != std::string::npos){
        std::string channel = line.substr(i + 16);
        line = "JOIN " + channel;
        send (bot->_fd, line.c_str(), line.size(), 0);
    }
}

void sendPokemon(std::string line, Bot *bot){
    if (bot->_pokemon.size() == 0)
        bot->openfile();
    std::vector<std::string> tmp;
    std::string temp;   
    for (size_t i = 1; i < line.size(); i ++){
        if (line[i] != ' ' && line[i] != '\n' && line[i] != '\r')
            temp += line[i];
        else{
            if (temp.size() > 0){
                tmp.push_back(temp);
                temp.erase();
            }
        }
    }
    if (tmp[1] == "PRIVMSG" && (tmp[3] == ":!poke" || tmp[4] == "!poke")){
        if (tmp[2].find('#') != std::string::npos){
            std::string request = "PRIVMSG " + tmp[2] + " :" + bot->randomPokemon() + "\n";
            send(bot->_fd, request.c_str(), request.size(), 0);
        }
        else{
            std::string request = "PRIVMSG " + tmp[0] + " :" + bot->randomPokemon() + "\n";
            send(bot->_fd, request.c_str(), request.size(), 0);
        }
    }
}
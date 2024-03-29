/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:00:10 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/29 16:09:20 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"
#include <unistd.h>

User::User(){
    
}

void    User::parseName(std::string buf)
{
    size_t start;

    start = buf.find("NICK") + 5;
    std::string name;
    name = buf.substr(start, buf.size() - start);
    this->_username = name.substr(0, name.find('\n'));
}

int User::setFd(int value){
    if (value < 0)
        return (value);
    _fd = value;
    return (value);
}

void    User::setChannel(std::string chan)
{
    this->_channel = chan;
}

std::string    User::getChannel()
{
    return (this->_channel);
}

std::string User::getUsername()
{
    return (this->_username);
}

int User::getFd() const{
    return (_fd);
}

User::~User(){
    close(_fd);
}
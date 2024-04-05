/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:00:10 by sforesti          #+#    #+#             */
/*   Updated: 2024/04/04 11:24:23 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"
#include "../includes/irc.hpp"
#include <unistd.h>

User::User(){
    this->_status = 0;
    this->buffer = "";
}

void    User::parseName(std::string buf)
{
    size_t start;

    start = buf.find("NICK") + 5;
    std::string name;
    name = buf.substr(start, buf.size() - start);
    if (name.find('\r') != std::string::npos)
        this->_username = name.substr(0, name.find('\r'));
    else if (name.find('\n') != std::string::npos)
        this->_username = name.substr(0, name.find('\n'));
}

int User::setFd(int value){
    if (value < 0)
        return (value);
    _fd = value;
    return (value);
}

void    User::setUsername(std::string username){
    _username = username;
}

std::string User::getUsername()
{
    return (this->_username);
}

int User::getStatus()
{
    return (this->_status);
}

void User::setStatus(int i)
{
    this->_status = i;
}

int User::getFd() const{
    return (_fd);
}

User::~User(){
    close(_fd);
}
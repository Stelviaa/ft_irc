/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:00:10 by sforesti          #+#    #+#             */
/*   Updated: 2024/04/05 16:57:41 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"
#include "../includes/irc.hpp"
#include <unistd.h>

User::User(){
    this->_status = 0;
    this->buffer = "";
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

std::string User::getNickname()
{
    return (this->_nickname);
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
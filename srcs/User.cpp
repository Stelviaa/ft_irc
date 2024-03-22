/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:00:10 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/22 19:09:24 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"
#include <unistd.h>

User::User(){
    
}

std::string User::getUsername()
{
    return (this->_username);
}

void    User::parseName(std::string buf)
{
    size_t start;

    start = buf.find("USER") + 5;
    std::string name;
    name = buf.substr(start, buf.size() - start);
    this->_username = name.substr(0, name.find(' '));
}

int User::setFd(int value){
    if (value < 0)
        return (value);
    _fd = value;
    return (value);
}
int User::getFd() const{
    return (_fd);
}

User::~User(){
    close(_fd);
}
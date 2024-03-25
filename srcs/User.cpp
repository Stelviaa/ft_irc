/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:00:10 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/25 12:44:02 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"
#include <unistd.h>

User::User(){
    
}

void    User::parseName(std::string buf)
{
    size_t start;

    std::cout << buf << std::endl;
    start = buf.find("NICK") + 5;
    std::string name;
    name = buf.substr(start, buf.size() - start);
    this->_username = name.substr(0, name.find('\n'));
    std::cout << "name : " << this->_username << std::endl;
}

int User::setFd(int value){
    if (value < 0)
        return (value);
    _fd = value;
    return (value);
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
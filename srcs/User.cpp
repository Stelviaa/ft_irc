/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:00:10 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/22 12:23:42 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"
#include <unistd.h>

User::User(){
    
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
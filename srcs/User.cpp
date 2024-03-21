/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:00:10 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/21 14:39:03 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"

User::User(){
    
}

int User::setFd(int value){
    if (value < 0)
        return (value);
    _fd = value;
}
int User::getFd() const{
    return (_fd);
}
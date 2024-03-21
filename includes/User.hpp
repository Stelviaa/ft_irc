/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:57:16 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/21 14:05:07 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class User{
    private:
        int _fd;
        std::string nickname;
    public:
        User();
        ~User();

        int setFd(int value);
        int getFd() const;
};
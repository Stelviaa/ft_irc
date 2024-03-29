/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:57:16 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/28 19:15:25 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class User{
    private:
        int _fd;
        std::string _nickname;
        std::string _username;
        std::string _channel;

    public:
        User();
        ~User();

        int setFd(int value);
        int getFd() const;
        std::string getUsername();
        void parseName(std::string buf);
};
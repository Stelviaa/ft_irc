/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:57:16 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/29 16:07:53 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP
# include <iostream>
# include <vector>
# include <string>
# include "irc.hpp"

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
        void    setChannel(std::string chan);
        std::string    getChannel();
        std::string getUsername();
        void parseName(std::string buf);
};

#endif
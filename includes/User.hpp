/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:57:16 by sforesti          #+#    #+#             */
/*   Updated: 2024/03/30 18:24:16 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP
# include <iostream>
# include <vector>
# include <string>

class User{
    private:
        int _fd;
        int _status;
        std::string _nickname;
        std::string _username;
        std::string _channel;

    public:
        User();
        ~User();

        int setFd(int value);
        int getFd() const;
        int getStatus();
        void setStatus(int i);
        void    setChannel(std::string chan);
        std::string    getChannel();
        std::string getUsername();
        void parseName(std::string buf);
};

#endif
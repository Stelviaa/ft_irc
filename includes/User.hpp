/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:57:16 by sforesti          #+#    #+#             */
/*   Updated: 2024/04/04 11:23:34 by mpelazza         ###   ########.fr       */
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

    public:
        User();
        ~User();

        int _id;
        std::string buffer;
        int setFd(int value);
        void setUsername(std::string username);
        int getFd() const;
        int getStatus();
        void setStatus(int i);
        std::string getUsername();
        void parseName(std::string buf);
};

#endif
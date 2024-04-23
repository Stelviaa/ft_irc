/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:58:12 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/21 11:52:50 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP
# include <sys/socket.h>
# include "../includes/User.hpp"
# include <fstream>
# include <cstdlib>
# include <ctime>
# include <arpa/inet.h>
# include <stdio.h>
# include <string.h>
# include <sys/socket.h>
# include <unistd.h>
# include <iostream>

class Bot
{
    public:
        Bot(int port, std::string pass);
        ~Bot();

		void openfile();
		void connection(std::string pass);
        int set_fd(int i);
        int _fd;
        void parsePokemon();
        std::string randomPokemon();  
        void read_fd();

    private:
        std::vector<std::string> _pokemon;

    
};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:58:12 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/20 11:30:34 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP
# include <sys/socket.h>
# include "../includes/User.hpp"

class Bot
{
	public:
		Bot();
		~Bot();

		int set_fd(int i);
		int fd;

	private:

	
};

#endif
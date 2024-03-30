/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:02:26 by luxojr            #+#    #+#             */
/*   Updated: 2024/03/30 18:14:59 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include "User.hpp"
# include <vector>


class Channel
{
	public:
		Channel(std::string name, User *op);
		~Channel();
		std::string	getName();
		void	AddUsers(User *usr);

	private:
		std::vector<User *> _op;
		std::vector<User *> _users;
		std::string	_name;


};

#endif
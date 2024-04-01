/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:02:26 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/01 08:32:56 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include "User.hpp"
# include <vector>
# include <map>


class Channel
{
	public:
		Channel(std::string name, User *op);
		~Channel();
		std::string	getName();
		int		is_op(User *usr);
		void	AddUsers(User *usr);
		std::map<std::string, User *> _users;


	private:
		std::vector<User *> _op;
		std::string	_name;


};

#endif
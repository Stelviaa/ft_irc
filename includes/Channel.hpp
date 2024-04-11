/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:02:26 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/11 11:58:53 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "User.hpp"
# include <vector>
# include <map>

# define I_ONLY 1
# define T_OP 2
# define K_PASS 4
# define U_LIMITS 8

class Channel {
	public:
		Channel(std::string name, User *op);
		~Channel();

		std::map<std::string, User *>	_users;
		std::vector<User *>				_op;
		std::vector<std::string>		_invitedUsers;
		std::string						_topic;
		size_t							_userLimit;
		int								_mode;

		void		AddUsers(User *usr);
		void		setPassword(std::string pass);
		int			is_op(User *usr);
		std::string	getName();
		std::string getPassword();

	private:
		std::string	_password;
		std::string	_name;
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:02:26 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/05 16:02:06 by luxojr           ###   ########.fr       */
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


class Channel
{
	public:
		Channel(std::string name, User *op);
		~Channel();
		std::string	getName();
		int		is_op(User *usr);
		void	AddUsers(User *usr);
		std::map<std::string, User *> _users;
		void	setPassword(std::string pass);
		std::string getPassword();
		std::string	_topic;
		size_t			_userLimit;
		int _mode;
		std::vector<User *> _op;
		std::vector<std::string> _invitedUsers;


	private:
		
		
		std::string	_password;
		std::string	_name;
		


};

#endif
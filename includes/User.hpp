/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:59:55 by sforesti          #+#    #+#             */
/*   Updated: 2024/04/11 12:02:32 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <vector>
# include <string>

class User{
	private:
		int			_fd;
		int			_status;
		std::string	_nickname;
		std::string	_username;

	public:
		User();
		~User();

		int 						_id;
		std::string 				buffer;
		std::vector<std::string>	_channels;

		void		removeChannel(std::string chan);
		void		setUsername(std::string username);
		void		setNickname(std::string nickname);
		void		setStatus(int i);
		int			setFd(int value);
		int			getFd() const;
		int			getStatus();
		std::string	getUsername();
		std::string	getNickname();
};

#endif

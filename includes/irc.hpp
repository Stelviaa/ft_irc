/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:39:21 by mboyer            #+#    #+#             */
/*   Updated: 2024/04/19 12:41:28 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# include <string.h>
# include <iostream>
# include <vector>
# include "Channel.hpp"

int							find_index(std::vector<std::string> vec, std::string str);
int							find_channel(std::vector<Channel *> vec, std::string str);
std::string					get_name(std::string name);
std::vector<std::string>	ft_split(std::string string, char sep);

#endif

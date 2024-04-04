/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:39:21 by mboyer            #+#    #+#             */
/*   Updated: 2024/03/30 18:01:27 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP
# include <string.h>
# include <iostream>
# include <vector>
# include "Channel.hpp"

std::vector<std::string> ft_split(std::string string, char sep);
int find_index(std::vector<std::string> vec, std::string str);
int find_channel(std::vector<Channel *> vec, std::string str);
std::string get_name(std::string name);
void    show_vec(std::vector<std::string> vec);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:39:21 by mboyer            #+#    #+#             */
/*   Updated: 2024/03/29 15:00:23 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP
# include <string.h>
# include <iostream>
# include <vector>

std::vector<std::string> ft_split(std::string string, char sep);
void    show_vec(std::vector<std::string> vec);

#endif
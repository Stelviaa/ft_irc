/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:37:44 by mboyer            #+#    #+#             */
/*   Updated: 2024/03/29 15:57:32 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

std::vector<std::string> ft_split(std::string string, char sep)
{
    size_t index;
    std::vector<std::string> ret;

    index = string.find(sep);
    ret.push_back(string.substr(0, index));
    while (string.size() > 1 && index != std::string::npos)
    {
        string.erase(0, index + 1);
        index = string.find_first_not_of(sep);
        string.erase(0, index);
        index = string.find(sep);
        if (string[0] == ':')
            index = std::string::npos;
        ret.push_back(string.substr(0, index));
    }
    return (ret);
}

void    show_vec(std::vector<std::string> vec)
{
    size_t i = 0;

    while (i < vec.size())
    {
        std::cout << vec[i] << std::endl;
        i ++;
    }
}
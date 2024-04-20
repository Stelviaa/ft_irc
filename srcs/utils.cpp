/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:55:00 by mboyer            #+#    #+#             */
/*   Updated: 2024/04/20 11:18:01 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

std::vector<std::string> ft_split(std::string string, char sep) {
	size_t						index;
	std::vector<std::string>	ret;

	index = string.find(sep);
	ret.push_back(string.substr(0, index));
	while (string.size() > 1 && index != std::string::npos) {
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

int find_index(std::vector<std::string> vec, std::string str) {
	size_t	i = 0;

	while (i < vec.size()) {
		if (vec[i].find(str) != std::string::npos)
			return (i);
		i ++;
	}
	return (-1);
}

int find_channel(std::vector<Channel *> vec, std::string str) {
	size_t	i = 0;

	while (i < vec.size()) {
		if (vec[i]->getName().find(str) != std::string::npos)
			return (i);
		i ++;
	}
	return (-1);
}

std::string get_name(std::string name) {
	std::string	ret;
	
	if (name.find("\r") != std::string::npos)
		ret = name.substr(0, name.find("\r"));
	else if (name.find("\n") != std::string::npos)
		ret = name.substr(0, name.find("\n"));
	else
		ret = name;
	return (ret);
}

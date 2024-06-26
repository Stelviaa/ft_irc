/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:58:21 by luxojr            #+#    #+#             */
/*   Updated: 2024/04/23 17:53:30 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include <cstdlib>

int main(int argc, char const* argv[])
{
	if (argc >= 3)
		Bot bot(std::atoi(argv[1]), argv[2]);
	else if (argc == 2)
		Bot bot(std::atoi(argv[1]), "");
	(void) argc;
    return 0;
}
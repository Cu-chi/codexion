/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:06:59 by equentin          #+#    #+#             */
/*   Updated: 2026/04/06 13:26:23 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/parsing.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_parsed	parsed;

	if (parse(&parsed, ac, av))
		return (1);
	printf("number_of_coders = %d\n"
			"time_to_burnout = %d\n"
			"time_to_compile = %d\n"
			"time_to_debug = %d\n"
			"time_to_refactor = %d\n"
			"number_of_compiles_required = %d\n"
			"dongle_cooldown = %d\n"
			"scheduler = %s\n", parsed.number_of_coders,
        parsed.time_to_burnout, parsed.time_to_compile, parsed.time_to_debug, parsed.time_to_refactor,
    parsed.number_of_compiles_required, parsed.dongle_cooldown, parsed.scheduler);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:06:59 by equentin          #+#    #+#             */
/*   Updated: 2026/04/08 12:53:15 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"
#include "coders/codexion.h"
#include "coders/dongles.h"
#include "coders/parsing.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	int			i;
	t_parsed	parsed;
	t_data		data;
	t_coder		coder;

	if (parse(&parsed, ac, av))
		return (1);
	data.parsed = &parsed;
	init_dongles(&data);
	init_coders(&data);
	i = 0;
	while (i < data.parsed->number_of_coders)
	{
		coder = data.coders[i];
		printf("Coder %d has %p at left and %p at right\n", coder.id,
			coder.dongle_left, coder.dongle_right);
		i++;
	}
	destroy_dongles(&data, data.parsed->number_of_dongles);
	free(data.coders);
	return (0);
}

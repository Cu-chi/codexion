/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:06:59 by equentin          #+#    #+#             */
/*   Updated: 2026/04/07 16:39:33 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"
#include "coders/dongles.h"
#include "coders/codexion.h"
#include "coders/parsing.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_parsed	parsed;
	t_data		data;

	if (parse(&parsed, ac, av))
		return (1);
	data.parsed = &parsed;
	init_dongles(&data);

	destroy_dongles(&data, data.parsed->number_of_coders);
	free(data.coders);
	return (0);
}

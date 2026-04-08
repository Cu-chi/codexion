/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:22:18 by equentin          #+#    #+#             */
/*   Updated: 2026/04/08 14:56:22 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"
#include "coders/codexion.h"
#include "coders/dongles.h"

void	destroy_dongles(t_data *data, int destroy_lim)
{
	int	i;

	i = 0;
	while (i < destroy_lim)
		pthread_mutex_destroy(&data->dongles[i++].mutex);
	i = 0;
	free(data->dongles);
}

void	*init_dongles(t_data *data)
{
	int	i;

	i = 0;
	data->dongles = malloc(sizeof(t_dongle) * data->parsed->number_of_dongles);
	if (data->dongles == NULL)
		return (NULL);
	while (i < (data->parsed->number_of_dongles))
	{
		if (pthread_mutex_init(&data->dongles[i].mutex, NULL) != 0)
		{
			destroy_dongles(data, i);
			return (NULL);
		}
		i++;
	}
	return (data->dongles);
}

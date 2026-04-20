/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:49:14 by equentin          #+#    #+#             */
/*   Updated: 2026/04/20 11:31:08 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/codexion.h"
#include <pthread.h>

int	destroy_mutex_cond(t_data *data, int destroy_lim, int cond)
{
	int	i;

	i = 0;
	while (i < destroy_lim)
		pthread_mutex_destroy(data->mutexes[i++]);
	if (cond)
		pthread_cond_destroy(&data->table_cond);
	return (1);
}

int	init_mutexes_cond(t_data *data)
{
	int	i;

	data->mutexes[0] = &data->print_mutex;
	data->mutexes[1] = &data->table_mutex;
	data->mutexes[2] = &data->finished_mutex;
	data->mutexes[3] = &data->exit_mutex;
	data->mutexes[4] = NULL;
	i = 0;
	while (data->mutexes[i])
	{
		if (pthread_mutex_init(data->mutexes[i], NULL) != 0)
			return (destroy_mutex_cond(data, i, 0));
		i++;
	}
	if (pthread_cond_init(&data->table_cond, NULL) != 0)
		return (destroy_mutex_cond(data, i, 0));
	return (0);
}

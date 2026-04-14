/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:47:38 by equentin          #+#    #+#             */
/*   Updated: 2026/04/14 16:03:42 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"
#include "coders/codexion.h"
#include "coders/dongles.h"
#include "coders/utils.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	*coder_routine(void *coder_ptr)
{
	t_coder		*coder;
	t_parsed	*parsed;

	coder = (t_coder *)coder_ptr;
	parsed = coder->data->parsed;
	pthread_mutex_lock(&coder->mutex);
	coder->last_compile = get_time();
	pthread_mutex_unlock(&coder->mutex);
	while (coder->number_of_compilation < parsed->number_of_compiles_required
		&& !check_exit(coder->data))
	{
		coder_compile(coder);
		coder_debug(coder);
		coder_refactor(coder);
	}
	if (!check_exit(coder->data))
	{
		pthread_mutex_lock(&coder->data->finished_mutex);
		coder->data->coder_finished += 1;
		pthread_mutex_unlock(&coder->data->finished_mutex);
	}
	return (NULL);
}

void	*destroy_coders(t_data *data, int destroy_lim)
{
	int	i;

	i = 0;
	while (i < destroy_lim)
		pthread_mutex_destroy(&data->coders[i++].mutex);
	free(data->coders);
	return (NULL);
}

void	*init_coders(t_data *data)
{
	int	i;
	int	left_dongle_index;
	int	right_dongle_index;

	i = 0;
	left_dongle_index = data->parsed->number_of_dongles - 1;
	right_dongle_index = 0;
	data->coders = malloc(sizeof(t_coder) * data->parsed->number_of_coders);
	if (data->coders == NULL)
		return (NULL);
	memset(data->coders, 0, sizeof(t_coder) * data->parsed->number_of_coders);
	while (i < data->parsed->number_of_coders)
	{
		data->coders[i].id = i + 1;
		data->coders[i].dongle_left = &data->dongles[left_dongle_index];
		data->coders[i].dongle_right = &data->dongles[right_dongle_index];
		data->coders[i].data = data;
		left_dongle_index = (left_dongle_index + 1)
			% data->parsed->number_of_coders;
		right_dongle_index++;
		if (pthread_mutex_init(&data->coders[i].mutex, NULL) != 0)
			return (destroy_coders(data, i));
		i++;
	}
	return (data->coders);
}

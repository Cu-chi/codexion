/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:47:38 by equentin          #+#    #+#             */
/*   Updated: 2026/04/10 10:31:59 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"
#include "coders/codexion.h"
#include "coders/dongles.h"
#include "coders/utils.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	coder_compile(t_coder *coder)
{
	t_data	*data;

	data = coder->data;
	request_dongles(coder);
	print_lock(coder->data, "%ld %d has taken a dongle\n", coder->id);
	print_lock(coder->data, "%ld %d has taken a dongle\n", coder->id);
	print_lock(coder->data, "%ld %d is compiling\n", coder->id);
	codexion_sleep(data->parsed->time_to_compile, data);
	coder->number_of_compilation += 1;
	coder->last_compile = get_time();
	release_dongles(coder);
}

void	coder_debug(t_coder *coder)
{
	t_data	*data;

	data = coder->data;
	print_lock(data, "%ld %d is debugging\n", coder->id);
	codexion_sleep(data->parsed->time_to_debug, data);
}

void	coder_refactor(t_coder *coder)
{
	t_data	*data;

	data = coder->data;
	print_lock(data, "%ld %d is refactoring\n", coder->id);
	codexion_sleep(data->parsed->time_to_refactor, data);
}

void	*coder_routine(void *coder_ptr)
{
	t_coder		*coder;
	t_parsed	*parsed;

	coder = (t_coder *)coder_ptr;
	parsed = coder->data->parsed;
	coder->last_compile = get_time();
	while (coder->number_of_compilation < parsed->number_of_compiles_required
		&& !coder->data->exit)
	{
		coder_compile(coder);
		coder_refactor(coder);
		coder_debug(coder);
	}
	if (!coder->data->exit)
		coder->data->coder_finished += 1;
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
		left_dongle_index++;
		right_dongle_index++;
		if (left_dongle_index >= data->parsed->number_of_coders)
			left_dongle_index = 0;
		i++;
	}
	return (data->coders);
}

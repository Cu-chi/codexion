/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:13:53 by equentin          #+#    #+#             */
/*   Updated: 2026/04/14 13:44:17 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"
#include "coders/codexion.h"
#include "coders/utils.h"

void	coder_compile(t_coder *coder)
{
	t_data	*data;

	data = coder->data;
	request_dongles(coder);
	pthread_mutex_lock(&coder->mutex);
	coder->last_compile = get_time();
	pthread_mutex_unlock(&coder->mutex);
	print_lock(coder->data, "%ld %d has taken a dongle\n", coder->id);
	print_lock(coder->data, "%ld %d has taken a dongle\n", coder->id);
	print_lock(coder->data, "%ld %d is compiling\n", coder->id);
	codexion_sleep(data->parsed->time_to_compile, data);
	pthread_mutex_lock(&coder->mutex);
	coder->number_of_compilation += 1;
	pthread_mutex_unlock(&coder->mutex);
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

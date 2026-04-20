/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_schedulers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 18:59:46 by equentin          #+#    #+#             */
/*   Updated: 2026/04/17 19:03:34 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/codexion.h"
#include "coders/queue.h"

void	insert_fifo(t_data *data, t_queue *enqueued)
{
	t_queue	*queue;

	queue = data->queue;
	while (queue && queue->next != NULL)
		queue = queue->next;
	queue->next = enqueued;
}

void	insert_edf(t_data *data, t_queue *enqueued)
{
	t_queue	*queue;
	t_queue	*prev;

	queue = data->queue;
	prev = NULL;
	while (queue && queue->coder->last_compile <= enqueued->coder->last_compile)
	{
		prev = queue;
		queue = queue->next;
	}
	if (prev)
		prev->next = enqueued;
	else
		data->queue = enqueued;
	enqueued->next = queue;
}

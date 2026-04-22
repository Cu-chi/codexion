/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:54:21 by equentin          #+#    #+#             */
/*   Updated: 2026/04/22 10:50:57 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H
# include "typedef.h"

struct s_queue
{
	void				*next;
	t_coder				*coder;
};

int						enqueue(t_data *data, t_coder *coder);
void					dequeue(t_data *data, t_coder *coder);
int						is_priority_holder(t_data *data, t_coder *coder);
void					insert_fifo(t_data *data, t_queue *enqueued);
void					insert_edf(t_data *data, t_queue *enqueued);
void					free_queue(t_queue *queue);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:35:35 by equentin          #+#    #+#             */
/*   Updated: 2026/04/22 10:50:46 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODERS_H
# define CODERS_H
# include "codexion.h"
# include "dongles.h"
# include <pthread.h>
# include "typedef.h"

struct s_coder
{
	int					id;
	long				last_compile;
	int					number_of_compilation;
	t_dongle			*dongle_left;
	t_dongle			*dongle_right;
	pthread_t			thread;
	t_data				*data;
	pthread_mutex_t		mutex;
};

int						init_coders(t_data *data);
int						destroy_coders(t_data *data, int destroy_lim);
void					coder_compile(t_coder *coder);
void					coder_debug(t_coder *coder);
void					coder_refactor(t_coder *coder);
void					*coder_routine(void *coder_data_ptr);
#endif

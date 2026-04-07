/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:22:35 by equentin          #+#    #+#             */
/*   Updated: 2026/04/07 16:50:42 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLES_H
# define DONGLES_H
# include "codexion.h"
# include <pthread.h>
# include <stdlib.h>

typedef struct s_dongle
{
    size_t			last_use;
    pthread_mutex_t	mutex;
}					t_dongle;

void				destroy_dongles(t_data *data, int destroy_lim);
void				*init_dongles(t_data *data);
#endif

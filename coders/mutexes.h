/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:07:37 by equentin          #+#    #+#             */
/*   Updated: 2026/04/20 11:21:48 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEXES_H
# define MUTEXES_H
# include "codexion.h"

int		init_mutexes_cond(t_data *data);
void	destroy_mutex_cond(t_data *data, int destroy_lim, int cond);
#endif

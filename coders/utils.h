/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:45:53 by equentin          #+#    #+#             */
/*   Updated: 2026/04/15 16:40:21 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <sys/time.h>
# include <unistd.h>

long			get_time_diff(long start_time);
void			print_lock(t_data *data, char *fmt, int coder_id, int force);
long			get_time(void);
void			codexion_sleep(int ms, t_data *data);
int				check_exit(t_data *data);
int				check_finished(t_data *data);
int				has_burned_out(t_coder *coder, t_parsed *parsed);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:45:53 by equentin          #+#    #+#             */
/*   Updated: 2026/04/13 13:48:01 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <sys/time.h>
# include <unistd.h>

ssize_t			get_time_diff(ssize_t start_time);
void			print_lock(t_data *data, char *fmt, int coder_id);
ssize_t			get_time(void);
struct timespec	get_target_timespec(int ms);
void			codexion_sleep(int ms, t_data *data);
void			lock_ordered(t_coder *coder);
int				check_exit(t_data *data);
int				check_finished(t_data *data);
#endif

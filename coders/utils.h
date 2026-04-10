/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equentin <equentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:45:53 by equentin          #+#    #+#             */
/*   Updated: 2026/04/10 10:32:06 by equentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <sys/time.h>
# include <unistd.h>

ssize_t	get_time_diff(ssize_t start_time);
void	print_lock(t_data *data, char *fmt, int coder_id);
ssize_t	get_time(void);
void	codexion_sleep(int ms, t_data *data);
#endif

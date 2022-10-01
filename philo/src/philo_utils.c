/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:44:13 by arouzen           #+#    #+#             */
/*   Updated: 2022/10/01 15:46:08 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

double	get_time_ms(void)
{
	struct timeval	t;
	double			ret_time;

	gettimeofday(&t, NULL);
	ret_time = (t.tv_sec * 1000) + (double)t.tv_usec / 1000;
	return (ret_time);
}

void	my_sleep(time_t slp)
{
	double	end;

	end = get_time_ms() + slp;
	while (1)
	{
		usleep(100);
		if (get_time_ms() >= end)
			return ;
	}
}

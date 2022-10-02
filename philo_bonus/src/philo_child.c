/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:37:09 by arouzen           #+#    #+#             */
/*   Updated: 2022/10/02 13:14:14 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_children(t_id phl, int exit_code, pid_t sender_child)
{
	int	i;

	i = 0;
	while (i < phl.gdata->nb_philo)
	{
		if (phl.ch_pid[i] != sender_child)
			kill(phl.ch_pid[i], SIGQUIT);
		i++;
	}
	exit_routine(phl, exit_code);
}

void	child_rt(t_id *phl, int id)
{
	pthread_t	tid;

	phl->t_spawn = get_time_ms();
	phl->ph_id = id;
	if (pthread_create(&tid, NULL, &lock_print_state, phl))
		exit(ERR);
	check_state(phl);
}

void	my_sleep(time_t slp)
{
	double	end;

	end = get_time_ms() + slp;
	usleep(slp * 0.95 * 1000);
	while (1)
	{
		usleep(1);
		if (get_time_ms() >= end)
			return ;
	}
}

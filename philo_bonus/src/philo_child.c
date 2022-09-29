/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:37:09 by arouzen           #+#    #+#             */
/*   Updated: 2022/09/29 16:37:36 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_children(t_id phl, int exit_code, pid_t sender_child)
{
	int i;

	i = 0;
	while (i < phl.gdata->nb_philo)
	{
		if (phl.ch_pid[i] != sender_child)
			kill(phl.ch_pid[i], SIGQUIT);
		i++;
	}
	exit(exit_code);
}

void	child_rt(t_id *phl, int id)
{
	pthread_t	tid;

	phl->t_spawn = get_time_ms();
	//sleep(2);
	phl->ph_id = id;
	//printf("been here %d -- timestamp: %ld\n", phl->ph_id,get_time_ms());
	if (pthread_create(&tid, NULL, &lock_print_state, phl))
		exit(ERR);
	check_state(phl);
	//pthread_join(tid[1], th_ret);
}

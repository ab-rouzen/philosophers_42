/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 19:07:46 by arouzen           #+#    #+#             */
/*   Updated: 2022/09/30 17:59:49 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	exit_routine(t_id phl,int exit_code)
{
	sem_close(phl.sem_fork);	
	sem_close(phl.sem_print);	
	sem_close(phl.sem_lock_fork);
	exit(exit_code);
}

int	main(int ac, char *av[])
{
	t_id	phl;
	t_data	gdata;
	int		i = 0;


	if (ac != 5 && ac != 6)
		return (ERR);
	if (load_args(&gdata, av) || phl.gdata->nb_philo > SEM_VALUE_MAX)
		return (ERR);
	printf("LINE is %d\n", __LINE__);
	if (init_philo(&phl, &gdata) || create_sem(&phl))
		return (ERR);
	while (i < gdata.nb_philo)
	{
		phl.ch_pid[i] = fork();
		if (phl.ch_pid[i] == 0)
			child_rt(&phl, i + 1);
		i++;
	}
	parent_watch(phl);
	return (0);
}

int	create_sem(t_id *phl)
{
	sem_unlink(SMP_PRINT);
	sem_unlink(SMP_FORK);
	sem_unlink(SMP_LOCK);
	phl->sem_fork = sem_open(SMP_PRINT, O_CREAT, S_IRWXU, phl->gdata->nb_philo);
	if (phl->sem_fork == SEM_FAILED)
		return (ERR);
	phl->sem_print = sem_open(SMP_FORK, O_CREAT, S_IRWXU, 1);
	if (phl->sem_print == SEM_FAILED)
		return (ERR);
	phl->sem_lock_fork = sem_open(SMP_LOCK, O_CREAT, S_IRWXU, 1);
	if (phl->sem_lock_fork == SEM_FAILED)
		return (ERR);
	return (0);
}

// int	get_philo_id(t_id *phl, pid_t ch_pid)
// {
// 	int	i;

// 	i = 0;
// 	while (i < phl->gdata->nb_philo && phl->ch_pid[i++] != ch_pid);
// 	return (i + 1);
// }

// void	*philo(void *datum)
// {
// 	t_id	*gp;
// 	int		s_fork;
// 	int		id;

// 	gp = (t_id*)datum;
// 	gp->eat_count = 0;
// 	gp->t_spawn = get_time_ms();
// 	if (!gp->t_spawn)
// 		return (NULL);
// 	check_state(gp);
// 	return (NULL);
// }
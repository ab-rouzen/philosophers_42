/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 19:07:46 by arouzen           #+#    #+#             */
/*   Updated: 2022/10/01 15:41:24 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_id	*phl;
	t_data	gdata;
	int		retval;

	if (ac != 5 && ac != 6)
		return (ERR);
	if (init_args(&gdata, av))
		return (ERR);
	phl = malloc(sizeof(t_id) * gdata.nb_philo);
	gdata.mtx = malloc(sizeof(pthread_mutex_t) * gdata.nb_philo);
	if (!phl || !gdata.mtx)
		return (ERR);
	if (init_philo(phl, &gdata) || spawn_philo(phl))
		return (ERR);
	detach_threads(phl);
	retval = check_state(phl);
	exit_threads(phl);
	return (retval);
}

void	detach_threads(t_id *phl)
{
	int	i;

	i = 0;
	while (i < phl->gdata->nb_philo)
	{
		pthread_detach(phl[i].t_id);
		i++;
	}
}

void	exit_threads(t_id *phl)
{
	int	i;

	i = 0;
	while (i < phl->gdata->nb_philo)
	{
		pthread_join(phl[i].t_id, NULL);
		i++;
	}
	i = 0;
	while (i < phl->gdata->nb_philo)
	{
		pthread_mutex_destroy(&phl->gdata->mtx[i]);
		i++;
	}
	pthread_mutex_destroy(&phl->gdata->print_mtx);
}

void	*philo(void *datum)
{
	t_id	*gp;
	int		s_fork;
	int		id;

	gp = (t_id *)datum;
	id = gp->ph_id;
	gp->eat_count = 0;
	gp->lt_eat = 0;
	if (id != 1)
		s_fork = id - 1;
	else
		s_fork = gp->gdata->nb_philo;
	gp->t_spawn = get_time_ms();
	if (!gp->t_spawn)
		return (NULL);
	lock_print_state(gp, id, s_fork);
	return (NULL);
}

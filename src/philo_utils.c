/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:44:13 by arouzen           #+#    #+#             */
/*   Updated: 2022/09/25 21:05:28 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time_ms(void)
{
	struct timeval t;

	if (gettimeofday(&t, NULL))
		return (0);
	return((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	lock_print_state(t_id* gp, int id, int s_fork)
{
	print_state(gp, MSG_THINK);
	pthread_mutex_lock(&gp->gdata->mtx[id - 1]);
	print_state(gp, MSG_FORK);
	pthread_mutex_lock(&gp->gdata->mtx[s_fork - 1]);
	print_state(gp, MSG_FORK);
	gp->lt_eat = print_state(gp, MSG_EAT);
	gp->eat_count++;
	if (gp->eat_count == gp->gdata->n_eat)
		gp->gdata->n_full_eat++;
	usleep(gp->gdata->tm_eat * 1000);
	pthread_mutex_unlock(&gp->gdata->mtx[s_fork - 1]);
	pthread_mutex_unlock(&gp->gdata->mtx[id - 1]);
	print_state(gp, MSG_SLEEP);
	usleep(gp->gdata->tm_sleep * 1000);
}

time_t	print_state(t_id *gp, char* msg)
{
	time_t	stamp;

	stamp = get_time_ms() - gp->t_spawn;
	pthread_mutex_lock(&gp->gdata->print_mtx);
	printf("%ld %d %s\n", stamp, gp->ph_id, msg);
	pthread_mutex_unlock(&gp->gdata->print_mtx);
	return (stamp);
}

int	spawn_philo(t_id *phl)
{
	int i;

	i = 0;
	pthread_mutex_init(&phl->gdata->print_mtx, NULL);
	while (i < phl->gdata->nb_philo)
	{
		if (!(i % 2))
		{
			if (pthread_create(&phl[i].t_id, NULL, &philo, &phl[i]))
				return (1);
		}
		i++;
	}
	usleep(250);
	while (--i >= 0)
	{
		if (i % 2)
			if (pthread_create(&phl[i].t_id, NULL, &philo, &phl[i]))
				return (1);	
	}
	return (0);
}

int	check_state(t_id *phl)
{
	time_t	time_to_die;
	int		i;

	time_to_die = phl->gdata->tm_die;
	i = 0;
	while (i < phl->gdata->nb_philo)
	{
		if (get_time_ms() - phl->t_spawn > phl[i].lt_eat + phl->gdata->tm_die)
		{
			print_state(&phl[i], MSG_DIED);
			return (1);
		}
		if (phl->gdata->n_full_eat == phl->gdata->nb_philo)
			return (0);
		if (i == phl->gdata->nb_philo - 1)
			i = 0;
		else 
			i++;
		usleep(100);
	}
	return (0);
}
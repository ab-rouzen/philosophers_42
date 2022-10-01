/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:44:13 by arouzen           #+#    #+#             */
/*   Updated: 2022/09/30 12:28:50 by arouzen          ###   ########.fr       */
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

void	lock_print_state(t_id *gp, int id, int s_fork)
{
	print_state(gp, MSG_THINK);
	pthread_mutex_lock(&gp->gdata->mtx[id - 1]);
	print_state(gp, MSG_FORK);
	pthread_mutex_lock(&gp->gdata->mtx[s_fork - 1]);
	print_state(gp, MSG_FORK);
	gp->lt_eat = get_time_ms() - gp->t_spawn;
	print_state(gp, MSG_EAT);
	gp->eat_count++;
	if (gp->eat_count == gp->gdata->n_eat)
		gp->gdata->n_full_eat++;
	usleep(gp->gdata->tm_eat * 1000);
	pthread_mutex_unlock(&gp->gdata->mtx[s_fork - 1]);
	pthread_mutex_unlock(&gp->gdata->mtx[id - 1]);
	print_state(gp, MSG_SLEEP);
	usleep(gp->gdata->tm_sleep * 1000);
}

double	print_state(t_id *gp, char *msg)
{
	double	stamp;

	stamp = get_time_ms() - gp->t_spawn;
	pthread_mutex_lock(&gp->gdata->print_mtx);
	if (gp->gdata->finish)
		printf("%ld %d %s\n", (long)stamp, gp->ph_id, msg);
	else if (!ft_strncmp(msg, MSG_DIED, 20))
		printf("%ld %d %s\n", (long)stamp, gp->ph_id, msg);
	pthread_mutex_unlock(&gp->gdata->print_mtx);
	return (stamp);
}

int	spawn_philo(t_id *phl)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&phl->gdata->print_mtx, NULL))
		return (ERR);
	while (i < phl->gdata->nb_philo)
	{
		if (!(i % 2))
			if (pthread_create(&phl[i].t_id, NULL, &philo, &phl[i]))
				return (ERR);
		i++;
	}
	usleep(100);
	while (--i >= 0)
	{
		if (i % 2)
			if (pthread_create(&phl[i].t_id, NULL, &philo, &phl[i]))
				return (ERR);
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
		usleep(100);
		if (get_time_ms() - phl->t_spawn > phl[i].lt_eat + phl->gdata->tm_die)
		{
			phl->gdata->finish = 0;
			print_state(&phl[i], MSG_DIED);
			return (DEATH);
		}
		if (phl->gdata->n_full_eat >= phl->gdata->nb_philo)
			return (ALL_EATEN);
		if (i == phl->gdata->nb_philo - 1)
			i = 0;
		else
			i++;
	}
	return (0);
}

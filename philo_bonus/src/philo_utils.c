/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:44:13 by arouzen           #+#    #+#             */
/*   Updated: 2022/10/01 16:22:28 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time_ms(void)
{
	struct timeval	t;
	long			ret_time;

	if (gettimeofday(&t, NULL))
		return (0);
	if (t.tv_usec % 1000 > 500)
		ret_time = (t.tv_sec * 1000) + (t.tv_usec / 1000) + 1;
	else
		ret_time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (ret_time);
}

void	*lock_print_state(void *datum)
{
	t_id	*gp;

	gp = (t_id *)datum;
	while (1)
	{
		print_state(gp, MSG_THINK);
		sem_wait(gp->sem_lock_fork);
		sem_wait(gp->sem_fork);
		print_state(gp, MSG_FORK);
		sem_wait(gp->sem_fork);
		print_state(gp, MSG_FORK);
		sem_post(gp->sem_lock_fork);
		gp->lt_eat = print_state(gp, MSG_EAT);
		gp->eat_count++;
		my_sleep(gp->gdata->tm_eat);
		sem_post(gp->sem_fork);
		sem_post(gp->sem_fork);
		if (gp->eat_count == gp->gdata->n_eat)
			exit(ALL_EATEN);
		print_state(gp, MSG_SLEEP);
		my_sleep(gp->gdata->tm_sleep);
	}
	return (0);
}

time_t	print_state(t_id *gp, char *msg)
{
	time_t	stamp;

	stamp = get_time_ms() - gp->t_spawn;
	sem_wait(gp->sem_print);
	printf("%ld %d %s\n", stamp, gp->ph_id, msg);
	if (!ft_strncmp(msg, MSG_DIED, 20))
		exit(DEATH);
	sem_post(gp->sem_print);
	return (stamp);
}

void	check_state(t_id *phl)
{
	time_t	time_to_die;

	time_to_die = phl->gdata->tm_die;
	while (1)
	{
		usleep(250);
		if (get_time_ms() - phl->t_spawn > phl->lt_eat + time_to_die)
			print_state(phl, MSG_DIED);
	}
}

int	parent_watch(t_id phl)
{
	int		stat_loc;
	int		wait_ret;
	int		n_eaten;

	n_eaten = 0;
	while (1)
	{
		wait_ret = waitpid(0, &stat_loc, WUNTRACED);
		if (wait_ret == -1)
			return (ERR);
		if (WIFSIGNALED(stat_loc))
			kill_children(phl, ERR, wait_ret);
		if (WEXITSTATUS(stat_loc) == ALL_EATEN)
			n_eaten++;
		if (WEXITSTATUS(stat_loc) == DEATH)
			kill_children(phl, DEATH, wait_ret);
		if (n_eaten == phl.gdata->nb_philo)
			kill_children(phl, ALL_EATEN, -1);
	}
}

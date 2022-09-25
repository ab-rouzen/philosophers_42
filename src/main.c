/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 19:07:46 by arouzen           #+#    #+#             */
/*   Updated: 2022/09/25 21:49:58 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_number(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (check_arg(args[i]))
			return (1);
		i++;
	}
	return (0);
}

int	init_args(t_data *data, char **args)
{
	if (check_number(args))
		return (1);
	data->nb_philo = ft_atoi(args[1]);
	data->tm_die = ft_atoi(args[2]);
	data->tm_eat = ft_atoi(args[3]);
	data->tm_sleep = ft_atoi(args[4]);
	data->n_full_eat = 0;
	if (args[5])
		data->n_eat = ft_atoi(args[5]);
	return (0);
}

int	init_philo(t_id *phl, t_data *gdata)
{
	int		i;

	i = 0;
	while (i < gdata->nb_philo)
	{
		phl[i].ph_id = i + 1;
		phl[i].gdata = gdata;
		phl[i].lt_eat = 0;
		if (pthread_mutex_init(&phl->gdata->mtx[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_id	*phl;
	t_data	gdata;

	if (ac != 5 && ac != 6)
		return (1);
	if (init_args(&gdata, av))
		return (1);
	phl = malloc(sizeof(t_id) * gdata.nb_philo);
	gdata.mtx = malloc(sizeof(pthread_mutex_t) * gdata.nb_philo);
	if (!phl || !gdata.mtx)
		return (1);
	if (init_philo(phl, &gdata))
		return (1);
	spawn_philo(phl);
	check_state(phl);
	return (0);
}

void	*philo(void *datum)
{
	t_id	*gp;
	int		s_fork;
	int		id;

	gp = (t_id*)datum;
	id = gp->ph_id;
	gp->eat_count = 0;
	if (id != 1)
		s_fork = id - 1;
	else
		s_fork = gp->gdata->nb_philo; 
	gp->t_spawn = get_time_ms();
	if (!gp->t_spawn)
		return (NULL);
	while (1)
		lock_print_state(gp, id, s_fork);
	return (NULL);
}
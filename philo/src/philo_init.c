/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:15:22 by arouzen           #+#    #+#             */
/*   Updated: 2022/09/30 12:04:49 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_arg(char *arg)
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

static int	check_number(char **args)
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
	data->finish = 1;
	if (args[5])
		data->n_eat = ft_atoi(args[5]);
	else
		data->n_eat = 0;
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

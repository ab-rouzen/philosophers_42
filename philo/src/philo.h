/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 15:51:52 by arouzen           #+#    #+#             */
/*   Updated: 2022/09/27 11:30:27 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO_H_
#define _PHILO_H_

#include <stdio.h> 
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include "../../lib/libft/libft.h"
#define MSG_EAT "is eating"
#define MSG_THINK "is thinking"
#define MSG_SLEEP "is sleeping"
#define MSG_DIED "died"
#define MSG_FORK "has taken a fork"
#define ALL_EATEN 2
#define ERR 1
#define DEATH 0

typedef struct s_data
{
	int				nb_philo;
	int				tm_sleep;
	int				tm_eat;
	int				tm_die;
	int				n_eat;
	pthread_mutex_t	*mtx;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	lock_mtx;
	int				n_full_eat;
	int				finish;

}				t_data;

typedef struct		 s_id
{
	t_data			*gdata;
	int				ph_id;
	pthread_t		t_id;
	time_t			t_spawn;
	time_t			lt_eat;
	int				eat_count;
}					t_id;

void	*philo(void *datum);
time_t	get_time_ms(void);
void	lock_print_state(t_id *gp, int id, int s_fork);
time_t	print_state(t_id *gp, char* msg);
int		spawn_philo(t_id *phl);
int		check_state(t_id *phl);
int		init_philo(t_id *phl, t_data *gdata);
int		init_args(t_data *data, char **args);


#endif
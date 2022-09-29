/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arouzen <arouzen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 15:51:52 by arouzen           #+#    #+#             */
/*   Updated: 2022/09/29 19:36:23 by arouzen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO_H_
#define _PHILO_H_

#include <stdio.h> 
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <signal.h>
#include "../../lib/libft/libft.h"
#define MSG_EAT "is eating"
#define MSG_THINK "is thinking"
#define MSG_SLEEP "is sleeping"
#define MSG_DIED "died"
#define MSG_FORK "has taken a fork"
#define SMP_PRINT "sem_print"
#define SMP_FORK "sem_fork"
#define SMP_LOCK "sem_lock_fork"
#define ALL_EATEN 2
#define ERR 1
#define DEATH 0
#define FALSE 0
#define TRUE 1

typedef int bool;
typedef struct s_data
{
	int				nb_philo;
	int				tm_sleep;
	int				tm_eat;
	int				tm_die;
	int				n_eat;
	pid_t			*whoami;

}				t_data;

typedef struct		 s_id
{
	t_data			*gdata;
	int				ph_id;
	pid_t			*ch_pid;
	sem_t			*sem_fork;
	sem_t			*sem_print;
	sem_t			*sem_lock_fork;
	time_t			t_spawn;
	time_t			lt_eat;
	bool			died;
	int				eat_count;
}					t_id;

void	*philo(void *datum);
time_t	get_time_ms(void);
void	*lock_print_state(void *datum);
time_t	print_state(t_id *gp, char* msg);
int		spawn_philo(t_id *phl);
int		init_philo(t_id *phl, t_data *gdata);
int		load_args(t_data *data, char **args);
void	kill_children(t_id phl, int exit_code, pid_t sender_child);
void	child_rt(t_id *phl, int id);
int		parent_watch(t_id phl);
int		create_sem(t_id *phl);
void	check_state(t_id *phl);
void	kill_children(t_id phl, int exit_code, pid_t sender_child);
void	child_rt(t_id *phl, int id);


#endif
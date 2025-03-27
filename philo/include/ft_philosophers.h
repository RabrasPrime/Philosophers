/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:06:45 by tjooris           #+#    #+#             */
/*   Updated: 2025/03/27 15:53:59 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILOSOPHERS_H
# define FT_PHILOSOPHERS_H

#include "libft.h"
#include <pthread.h>
#include "ft_printf.h"
#include <stdlib.h>
#include <sys/time.h>

enum	t_state
{
	SLEEP,
	EAT,
	THINK,
};

typedef struct s_table t_table;

typedef struct s_philosopher {
    int id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    int status;
    long last_meal_time;
    int meals_eaten;
    t_table *table;
    pthread_t thread;
} t_philosopher;

struct s_table {
    int num_philosophers;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int must_eat_count;
    int stop_simulation;
    long start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    pthread_mutex_t status_simulation;
    t_philosopher *philosophers;
};

void *philosopher_routine(void *arg);
void take_forks_and_eat(t_philosopher *philo);
void print_status(t_philosopher *philo, char *message);
long get_time_in_ms();
void start_simulation(t_table *table);
void	take_forks(t_philosopher *philo);
void clear_table(t_table *table, int nb_philo);
t_table *init_table(int nb_philo, int time_to_die, int time_to_eat, int time_to_sleep, int eat_count);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:06:45 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/23 17:31:25 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILOSOPHERS_H
# define FT_PHILOSOPHERS_H


# include <pthread.h>

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

enum	t_state
{
	SLEEP,
	EAT,
	THINK,
	DEAD,
};

enum    t_status_fork
{
    FREE,
    TAKEN,
};

typedef struct s_fork
{
    pthread_mutex_t fork;
    int status;
}   t_fork;

typedef struct s_table t_table;

typedef struct s_philosopher {
    int id;
    t_fork *left_fork;
    t_fork *right_fork;
    int status;
    long long last_meal_time;
    long long  time_to_die;
    int meals_eaten;
    t_table *table;
    pthread_t thread;
} t_philosopher;

struct s_table {
    int num_philosophers;
    long long time_to_die;
    long long time_to_eat;
    long long time_to_sleep;
    int must_eat_count;
    int stop_simulation;
    long long start_time;
    t_fork *forks;
    pthread_mutex_t print_lock;
    pthread_mutex_t status_simulation;
    pthread_mutex_t init;
    t_philosopher *philosophers;
};

void *philosopher_routine(void *arg);
void take_forks_and_eat(t_philosopher *philo);
int print_status(t_philosopher *philo, char *message);
long long get_current_time_ms(void);
void clear_table(t_table *table, int nb_philo);
t_table *init_table(int nb_philo, int time_to_die, int time_to_eat, int time_to_sleep, int eat_count);
int	my_usleep(t_philosopher *philo, long long time);
void	let_fork(t_philosopher *philo);
int	is_fork_taken(t_fork *fork);
int	take_fork(t_fork *fork);
int	check_philo_status(t_philosopher *philo);
int	check_philo_died(t_philosopher	*philo);
int check_simulation_stop(t_philosopher *philo);
int	take_forks(t_fork *left_fork, t_fork *right_fork);
int	is_eating(t_philosopher *philo);
int	is_sleeping(t_philosopher *philo);
int	is_thinking(t_philosopher *philo);
int	check_arguments(int size, char **tab);
int	is_number(char *str);
int	ft_atoi_philo(char *number);

#endif
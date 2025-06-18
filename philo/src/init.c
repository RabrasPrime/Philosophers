/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:23:05 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/18 15:29:35 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

// int init_philosopher(t_table *table, int id, t_philosopher **philosopher)
// {
//     *philosopher = malloc(sizeof(t_philosopher));
//     if (!*philosopher)
//         return (id);
//     (*philosopher)->id = id;
//     (*philosopher)->table = table;
//     (*philosopher)->meals_eaten = 0;
//     (*philosopher)->last_meal_time = table->start_time;
//     (*philosopher)->time_to_die = table->time_to_die;
// 	if (id % 2 == 0)
//     	(*philosopher)->status = EAT;
// 	else
// 		(*philosopher)->status = THINK;
// 	(*philosopher)->status = 0;
//     (*philosopher)->left_fork = &table->forks[id];
//     (*philosopher)->right_fork = &table->forks[(id + 1) % table->num_philosophers];
//     return (0);
// }

void init_philosopher(t_table *table, int id, t_philosopher *philo)
{
    philo->id = id;
    philo->table = table;
    philo->meals_eaten = 0;
    philo->last_meal_time = table->start_time;
    philo->time_to_die = table->time_to_die;
    philo->left_fork = &table->forks[id];
    philo->right_fork = &table->forks[(id + 1) % table->num_philosophers];
    if (id % 2 == 0)
        philo->status = EAT;
    else
        philo->status = THINK;
}

void init_philosophers(t_table *table)
{
    int i = 0;
    while (i < table->num_philosophers)
    {
        init_philosopher(table, i, &table->philosophers[i]);
        i++;
    }
}

static int init_forks(t_fork **forks, int nb_philo)
{
    int i;

    *forks = malloc(sizeof(t_fork) * nb_philo);
    if (!*forks)
        return (0);
    i = 0;
    while (i < nb_philo)
    {
        (*forks)[i].status = FREE;
        if (pthread_mutex_init(&(*forks)[i].fork, NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&(*forks)[i].fork);
            free(*forks);
            return (0);
        }
        i++;
    }
    return (1);
}


static int init_mutexes(t_table *table)
{
    if (pthread_mutex_init(&table->print_lock, NULL) != 0)
        return (0);
    if (pthread_mutex_init(&table->status_simulation, NULL) != 0)
    {
        pthread_mutex_destroy(&table->print_lock);
        return (0);
    }
    return (1);
}

t_table *init_table(int nb_philo, int time_to_die, int time_to_eat, int time_to_sleep, int eat_count)
{
    t_table *table;

	if (nb_philo < 0 || time_to_die < 0 || time_to_eat < 0 || time_to_sleep < 0 || eat_count == -1)
		return (NULL);
    table = malloc(sizeof(t_table));
    if (!table)
        return (NULL);
    table->num_philosophers = nb_philo;
    table->time_to_die = time_to_die;
    table->time_to_eat = time_to_eat;
    table->time_to_sleep = time_to_sleep;
    table->must_eat_count = eat_count;
    table->stop_simulation = 0;
    table->start_time = get_current_time_ms();
    if (!init_forks(&table->forks, nb_philo) || !init_mutexes(table))
        return (free(table), NULL);
    table->philosophers = malloc(sizeof(t_philosopher) * nb_philo);
    if (!table->philosophers)
    {
        pthread_mutex_destroy(&table->status_simulation);
        pthread_mutex_destroy(&table->print_lock);
        free(table->forks);
		free(table);
        return (NULL);
    }
    init_philosophers(table);
    return (table);
}

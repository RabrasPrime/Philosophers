/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:23:05 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/27 14:15:45 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void	init_philosopher(t_table *table, int id, t_philosopher *philo)
{
	philo->id = id;
	philo->table = table;
	philo->meals_eaten = 0;
	philo->last_meal_time = table->start_time;
	philo->left_fork = &table->forks[id];
	philo->right_fork = &table->forks[(id + 1) % table->num_philosophers];
	philo->status = THINK;
}

void	init_philosophers(t_table *table, int time_to_die,
			int time_to_eat, int time_to_sleep)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
	{
		init_philosopher(table, i, &table->philosophers[i]);
		table->philosophers[i].time_to_die = time_to_die;
		table->philosophers[i].time_to_eat = time_to_eat;
		table->philosophers[i].time_to_sleep = time_to_sleep;
		i++;
	}
}

static int	init_forks(t_fork **forks, int nb_philo)
{
	int	i;

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

static int	init_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->status_simulation, NULL) != 0)
	{
		pthread_mutex_destroy(&table->print_lock);
		return (0);
	}
	if (pthread_mutex_init(&table->init, NULL) != 0)
	{
		pthread_mutex_destroy(&table->print_lock);
		pthread_mutex_destroy(&table->status_simulation);
		return (0);
	}
	return (1);
}

t_table	*init_table(int nb_philo, int eat_count)
{
	t_table	*table;

	if (nb_philo < 0 || eat_count == -1)
		return (NULL);
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	init_value(table, nb_philo, eat_count);
	if (!init_forks(&table->forks, nb_philo) || !init_mutexes(table))
	{
		free(table);
		return (NULL);
	}
	table->philosophers = malloc(sizeof(t_philosopher) * nb_philo);
	if (!table->philosophers)
	{
		pthread_mutex_destroy(&table->status_simulation);
		pthread_mutex_destroy(&table->print_lock);
		free(table->forks);
		free(table);
		return (NULL);
	}
	return (table);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:07:41 by tjooris           #+#    #+#             */
/*   Updated: 2025/03/26 14:52:01 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

/* ************************************************************************** */
/*                          FONCTIONS UTILITAIRES                             */
/* ************************************************************************** */

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

/* ************************************************************************** */
/*                        FONCTIONS DE SIMULATION                             */
/* ************************************************************************** */

void	take_forks_and_eat(t_philosopher *philo)
{
	t_table	*table = philo->table;

	take_forks(philo);
	print_status(philo, "is eating 🍝");
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	usleep(table->time_to_eat * 1000);
	pthread_mutex_unlock(&table->forks[philo->right_fork]);
	pthread_mutex_unlock(&table->forks[philo->left_fork]);
	print_status(philo, "is sleeping 😴");
	usleep(table->time_to_sleep * 1000);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo = (t_philosopher *)arg;

	// Si le philosophe est pair, il commence par penser pour laisser le temps à un impair de manger.
	if (philo->id % 2 == 0)
	{
		print_status(philo, "is thinking 💭");
		usleep(philo->table->time_to_eat * 1000);
	}
	// Sinon, l'impair commence directement par manger.
	else
		take_forks_and_eat(philo);
	while (!philo->table->stop_simulation)
	{
		print_status(philo, "is thinking 💭");
		take_forks_and_eat(philo);
	}
	return (NULL);
}

void	monitor_simulation(t_table *table)
{
	int	i;
	int	all_full;

	while (1)
	{
		all_full = 1;
		for (i = 0; i < table->num_philosophers; i++)
		{
			if ((get_time_in_ms() - table->philosophers[i].last_meal_time) > table->time_to_die)
			{
				print_status(&table->philosophers[i], "died 💀");
				table->stop_simulation = 1;
				return ;
			}
			if (table->must_eat_count != -1 && table->philosophers[i].meals_eaten < table->must_eat_count)
				all_full = 0;
		}
		if (table->must_eat_count != -1 && all_full)
		{
			table->stop_simulation = 1;
			return ;
		}
		usleep(1000);
	}
}

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;
	int		i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (NULL);
	}
}

void	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_create(&table->philosophers[i].thread, NULL, philosopher_routine, &table->philosophers[i]);
		i++;
	}
	monitor_simulation(table);
	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table	*table;
	int		i;

	table = init_table(argc, argv);
	if (!table)
		return (1);
	start_simulation(table);
	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	free(table->forks);
	free(table->philosophers);
	free(table);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:07:41 by tjooris           #+#    #+#             */
/*   Updated: 2025/07/04 13:11:44 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"
#include <limits.h>

int	everyone_ate(t_philosopher *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->status_simulation);
	if (table->must_eat_count == -2)
	{
		pthread_mutex_unlock(&table->status_simulation);
		return (0);
	}
	if (table->have_eaten == table->num_philosophers)
	{
		table->stop_simulation = 1;
		pthread_mutex_unlock(&table->status_simulation);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&table->status_simulation);
		return (0);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->table->must_eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&philo->table->init);
	pthread_mutex_unlock(&philo->table->init);
	philo->status = THINK;
	if (philo->id % 2 == 1)
		usleep((philo->time_to_eat / 2) * 1000);
	while (!everyone_ate(philo))
	{
		if (check_philo_died(philo))
			break ;
		if (philo->status == THINK)
			is_thinking(philo);
		else if (philo->status == EAT)
			is_eating(philo);
		else if (philo->status == SLEEP)
			is_sleeping(philo);
	}
	return (NULL);
}

static void	wait_simulation_end(t_table *table)
{
	while (1)
	{
		pthread_mutex_lock(&table->status_simulation);
		if (table->stop_simulation == 1)
		{
			pthread_mutex_unlock(&table->status_simulation);
			break ;
		}
		pthread_mutex_unlock(&table->status_simulation);
		usleep(1000);
	}
}

static int	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->init);
	while (i < table->num_philosophers)
	{
		table->philosophers[i].last_meal_time = table->start_time;
		if (pthread_create(&table->philosophers[i].thread,
				NULL, philosopher_routine, &table->philosophers[i]))
		{
			table->stop_simulation = 1;
			break ;
		}
		i++;
	}
	table->start_time = get_current_time_ms();
	pthread_mutex_unlock(&table->init);
	wait_simulation_end(table);
	join_philo(table, i);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	int		error_philo;

	if (argc < 5 || argc > 6)
	{
		printf("error: wrong number of argument\n");
		return (EXIT_FAILURE);
	}
	if (!check_arguments(argc, argv))
	{
		printf("error: wrong type of arguments\n");
		return (EXIT_FAILURE);
	}
	if (argc == 6)
		table = init_table(ft_atoi_philo(argv[1]), ft_atoi_philo(argv[5]));
	else
		table = init_table(ft_atoi_philo(argv[1]), -2);
	if (!table)
		return (-1);
	error_philo = init_philosophers(table, ft_atoi_philo(argv[2]),
			ft_atoi_philo(argv[3]), ft_atoi_philo(argv[4]));
	if (error_philo)
		start_simulation(table);
	clear_table(table);
}

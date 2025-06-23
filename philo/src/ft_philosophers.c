/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:07:41 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/23 17:35:47 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"
#include <limits.h>

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo = (t_philosopher *)arg;
	
	if (philo->table->must_eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&philo->table->init);
	pthread_mutex_unlock(&philo->table->init);
	if (philo->id % 2 == 1)
		usleep(philo->table->time_to_sleep * 1000);
	while (!check_simulation_stop(philo))
	{
		if (is_thinking(philo))
			continue;
		if (is_eating(philo))
			return (NULL);
		if (is_sleeping(philo))
			continue;
		//usleep(1000);
	}
	return (NULL);
}

static int	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->init);
	while (i < table->num_philosophers)
	{
		table->philosophers[i].last_meal_time = table->start_time;
		if (pthread_create(&table->philosophers[i].thread, NULL, philosopher_routine, &table->philosophers[i]))
			return(0);
		i++;
	}
	table->start_time = get_current_time_ms();
	pthread_mutex_unlock(&table->init);
	while(1)
	{
		pthread_mutex_lock(&table->status_simulation);
		if (table->stop_simulation == 1)
		{
			pthread_mutex_unlock(&table->status_simulation);
			break;
		}
		pthread_mutex_unlock(&table->status_simulation);
	}
	i = 0;
	while (i < table->num_philosophers)
	{
		if (pthread_join(table->philosophers[i].thread, NULL))
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc < 5 || argc > 6)
	{
		printf("error: wrong number of argument\n");
		exit(EXIT_FAILURE);
	}
	if (!check_arguments(argc, argv))
	{
		printf("error: wrong type of arguments\n");
		exit(EXIT_FAILURE);
	}
	if (argc == 6)
		table = init_table(ft_atoi_philo(argv[1]), ft_atoi_philo(argv[2]), ft_atoi_philo(argv[3]), ft_atoi_philo(argv[4]), ft_atoi_philo(argv[5]));
	else
		table = init_table(ft_atoi_philo(argv[1]), ft_atoi_philo(argv[2]), ft_atoi_philo(argv[3]), ft_atoi_philo(argv[4]), -2);
	if (!table)
		return (-1);
	start_simulation(table);
}

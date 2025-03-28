/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:07:41 by tjooris           #+#    #+#             */
/*   Updated: 2025/03/28 13:59:39 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

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
	if (philo->id % 2 == 0)
	{
		print_status(philo, "is thinking");
		my_usleep(philo->table->time_to_eat * 1000);
	}
	else
		take_forks_and_eat(philo);
	while (!philo->table->stop_simulation)
	{
		print_status(philo, "is thinking");
		take_forks_and_eat(philo);
	}
	return (NULL);
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

	table = init_table(argv[1], argv[2], argv[3], argv[4], argv[5]);
	if (!table)
		return (-1);
}

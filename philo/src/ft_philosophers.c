/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:07:41 by tjooris           #+#    #+#             */
/*   Updated: 2025/03/31 14:36:21 by tjooris          ###   ########.fr       */
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
	print_status(philo, "is eating");
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	usleep(table->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	print_status(philo, "is sleeping");
	usleep(table->time_to_sleep * 1000);
}

int check_philo_died(t_philosopher *philo)
{
	if(philo->status == DEAD)
	{
		print_status(philo, "died");
		pthread_mutex_lock(&philo->table->status_simulation);
		philo->table->stop_simulation = 1;
		pthread_mutex_unlock(&philo->table->status_simulation);
		return (1);
	}
	return (0);	
}

int check_simulation_died(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->table->status_simulation);
	if (philo->table->stop_simulation == 1)
	{
		pthread_mutex_unlock(&philo->table->status_simulation);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->status_simulation);
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo = (t_philosopher *)arg;
	
	if (philo->table->must_eat_count == 0)
		return (NULL);
	if (philo->id % 2 == 0)
	{
		print_status(philo, "is thinking");
		my_usleep(philo->table ,philo->table->time_to_eat * 1000);
	}
	else
		take_forks_and_eat(philo);
	while (!philo->table->stop_simulation)
	{
		if (!check_philo_died(philo))
			return (NULL);
		if (philo->status == THINK || philo->status == SLEEP)
			print_status(philo, "is thinking");
		if (check_philo_died(philo) || check_simulation_died(philo))
			return (NULL);
		take_forks_and_eat(philo);
	}
	return (NULL);
}

static int	start_simulation(t_table *table)
{
	int	i;

	table->start_time = get_time_in_ms() + (table->num_philosophers * 2 * 10);
	i = 0;
	while (i < table->num_philosophers)
	{
		if (pthread_create(&table->philosophers[i].thread, NULL, philosopher_routine, &table->philosophers[i]))
			return(0);
		i++;
	}
	i = 0;
	while (i < table->num_philosophers)
	{
		if (pthread_join(table->philosophers[i].thread, NULL))
			return (0);
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

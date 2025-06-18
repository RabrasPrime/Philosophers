/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:07:41 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/18 16:32:00 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"
#include <limits.h>

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_arguments(int size, char **tab)
{
	int	i;

	i = 1;
	while (i < size)
	{

		if (!is_number(tab[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi_philo(char *number)
{
	long long	nb;
	int			i;

	i = 0;
	nb = 0;
	while (number[i])
	{
		
		nb = (nb * 10) + (number[i] - '0'); 
		i++;
		if (nb < 0)
			return (-1);
	}
	return (nb);
}

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

int	is_eating(t_philosopher *philo)
{
	t_table	*table = philo->table;

	if (check_simulation_stop(philo))
		return (1);
	print_status(philo, "is eating");
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	if (my_usleep(philo, table->time_to_eat * 1000))
		return (1);
	let_fork(philo);
	return (0);
}

int	is_sleeping(t_philosopher *philo)
{
	t_table	*table = philo->table;

	if (check_simulation_stop(philo))
		return (1);
	print_status(philo, "is sleeping");
	if (my_usleep(philo, table->time_to_sleep * 1000))
		return (1);
	return (0);
}

int	check_philo_status(t_philosopher *philo)
{
	time_t	now;

	now = get_current_time_ms();
	if (now - philo->last_meal_time >= philo->table->time_to_die)
		return (0);
	return (1);
}

void	report_death(t_philosopher	*philo)
{
	t_table	*table;

	table = philo->table;
	if (check_simulation_stop(philo))
		print_status(philo, "died");
	pthread_mutex_lock(&table->status_simulation);
	table->stop_simulation = 1;
	pthread_mutex_unlock(&table->status_simulation);
}

int	is_thinking(t_philosopher	*philo)
{
	t_table	*table;

	if (check_simulation_stop(philo))
		return (1);
	print_status(philo, "is thinking");
	table = philo->table;
	while(take_fork(philo->left_fork))
	{
		if (check_philo_died(philo))
			return (1);
	}
	print_status(philo, "has taken a fork");
	while(take_fork(philo->right_fork))
	{
		if (check_philo_died(philo))
			return (1);
	}
	print_status(philo, "has taken a fork");
	return (0);
}

int	check_philo_died(t_philosopher	*philo)
{
	if (check_simulation_stop(philo))
		return (1);
	if (!check_philo_status(philo))
	{
		report_death(philo);
		return (1);
	}
	return (0);
}

int check_simulation_stop(t_philosopher *philo)
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
	while (!check_simulation_stop(philo))
	{
		if (is_thinking(philo))
			return (NULL);
		if (is_eating(philo))
			return (NULL);
		if (is_sleeping(philo))
			return (NULL);
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
	//clear_table(table, table->num_philosophers);
}

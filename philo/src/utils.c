/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:22:26 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/18 16:13:31 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void	print_status(t_philosopher *philo, char *message)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("[%ld] Philosopher %d %s\n", get_current_time_ms() - philo->table->start_time, philo->id, message);
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	let_fork(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		philo->left_fork->status = FREE;
		pthread_mutex_unlock(&philo->left_fork->fork);
		pthread_mutex_lock(&philo->right_fork->fork);
		philo->right_fork->status = FREE;
		pthread_mutex_unlock(&philo->right_fork->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		philo->right_fork->status = FREE;
		pthread_mutex_unlock(&philo->right_fork->fork);
		pthread_mutex_lock(&philo->left_fork->fork);
		philo->left_fork->status = FREE;
		pthread_mutex_unlock(&philo->left_fork->fork);
	}	
}

int	take_fork(t_fork *fork)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&fork->fork);
	if (fork->status == TAKEN)
		i = 1;
	else
		fork->status = TAKEN;
	pthread_mutex_unlock(&fork->fork);
	return (i);
}

time_t get_current_time_ms(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) != 0)
        return (-1);
    return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

int	my_usleep(t_philosopher *philo, time_t time)
{
	time_t	end;
	t_table	*table;

	table = philo->table;
	end = get_current_time_ms() + time;
	while (get_current_time_ms() < end)
	{
		if (check_simulation_stop(philo) || check_philo_died(philo))
			return (0);
		usleep(1000);
	}
	return (1);
}

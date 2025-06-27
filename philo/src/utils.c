/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:22:26 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/27 13:57:28 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

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

int	print(t_philosopher *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->table->status_simulation);
	i = print_status(philo);
	pthread_mutex_unlock(&philo->table->status_simulation);
	return (i);
}

int	print_status(t_philosopher *philo)
{
	if (philo->table->stop_simulation == 1)
		return (0);
	pthread_mutex_lock(&philo->table->print_lock);
	if (philo->status == DEAD)
		printf("\033[31m%lld %d died\033[0m\n",
			get_current_time_ms() - philo->table->start_time, philo->id);
	else if (philo->status == EAT)
		printf("\033[33m%lld %d is eating\033[0m\n",
			get_current_time_ms() - philo->table->start_time, philo->id);
	else if (philo->status == THINK)
		printf("\033[36m%lld %d is thinking\033[0m\n",
			get_current_time_ms() - philo->table->start_time, philo->id);
	else if (philo->status == SLEEP)
		printf("\033[35m%lld %d is sleeping\033[0m\n",
			get_current_time_ms() - philo->table->start_time, philo->id);
	else
	{
		printf("\033[34m%lld %d has taken a fork\033[0m\n",
			get_current_time_ms() - philo->table->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->table->print_lock);
	return (1);
}

long long	get_current_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((long long)tv.tv_sec * 1000LL + (long long)(tv.tv_usec / 1000));
}

int	my_usleep(t_philosopher *philo, long long time)
{
	long long	end;

	end = get_current_time_ms() + time;
	while (get_current_time_ms() < end)
	{
		if (check_philo_died(philo))
			return (0);
		usleep(200);
	}
	return (1);
}

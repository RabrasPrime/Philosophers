/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:22:26 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/23 16:45:16 by tjooris          ###   ########.fr       */
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

int	print_status(t_philosopher *philo, char *message)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%lld %d %s\n", get_current_time_ms() - philo->table->start_time, philo->id, message);
	pthread_mutex_unlock(&philo->table->print_lock);
	return (1);
}

long long get_current_time_ms(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) != 0)
        return (-1);
    return ((long long)tv.tv_sec * 1000LL + (long long)(tv.tv_usec / 1000));
}

int	my_usleep(t_philosopher *philo, long long time)
{
	long long	i;
	t_table	*table;

	i = 0;
	table = philo->table;
	while (i < time)
	{
		if (check_philo_died(philo))
			return (0);
		usleep(1000);
		i++;
	}
	return (1);
}

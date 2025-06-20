/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:22:26 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/20 14:52:05 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void	print_status(t_philosopher *philo, char *message)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("[%lld] Philosopher %d %s\n", get_current_time_ms() - philo->table->start_time, philo->id, message);
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	let_fork(t_philosopher *philo)
{
	if (check_simulation_stop(philo) || check_philo_died(philo))
			return ;
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

int take_forks(t_fork *left_fork, t_fork *right_fork)
{
	t_fork *first;
	t_fork *second;

	if (left_fork < right_fork)
	{
		first = left_fork;
		second = right_fork;
	}
	else
	{
		first = right_fork;
		second = left_fork;
	}
	pthread_mutex_lock(&first->fork);
	pthread_mutex_lock(&second->fork);

	if (left_fork->status == TAKEN || right_fork->status == TAKEN)
	{
		pthread_mutex_unlock(&second->fork);
		pthread_mutex_unlock(&first->fork);
		return (1);
	}
	left_fork->status = TAKEN;
	right_fork->status = TAKEN;
	pthread_mutex_unlock(&second->fork);
	pthread_mutex_unlock(&first->fork);
	return (0);
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

long long get_current_time_ms(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) != 0)
        return (-1);
    return ((long long)tv.tv_sec * 1000LL + (long long)(tv.tv_usec / 1000));
}

int	my_usleep(t_philosopher *philo, long long time)
{
	//long long	end;
	long long	i;
	t_table	*table;

	i = 0;
	table = philo->table;
	//printf("res = %lld\n", time);
	//end = get_current_time_ms() + time;
	while (i < time)
	{
		//  if (philo->id == 0)
		//  	print_status(philo, "lslslslsls");
		if (check_simulation_stop(philo) || check_philo_died(philo))
			return (0);
		usleep(1000);
		i++;
	}
	return (1);
}

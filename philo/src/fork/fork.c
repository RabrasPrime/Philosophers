/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:33:41 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/23 14:22:29 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

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
	pthread_mutex_lock(&left_fork->fork);
	pthread_mutex_lock(&right_fork->fork);
	if (left_fork->status == TAKEN || right_fork->status == TAKEN)
	{
		pthread_mutex_unlock(&right_fork->fork);
		pthread_mutex_unlock(&left_fork->fork);
		return (1);
	}
	left_fork->status = TAKEN;
	right_fork->status = TAKEN;
	pthread_mutex_unlock(&right_fork->fork);
	pthread_mutex_unlock(&left_fork->fork);
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

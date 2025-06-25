/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:33:41 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/25 16:42:51 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void	let_fork(t_philosopher *philo)
{
	t_fork	*first;
	t_fork	*second;

	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(&first->fork);
	pthread_mutex_lock(&second->fork);
	first->status = FREE;
	second->status = FREE;
	pthread_mutex_unlock(&second->fork);
	pthread_mutex_unlock(&first->fork);
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

int	fork_lock(t_philosopher *philo)
{
	t_fork	*first;
	t_fork	*second;

	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	while (take_fork(first))
	{
		if (check_philo_died(philo))
			return (1);
	}
	while (take_fork(second))
	{
		if (check_philo_died(philo))
			return (1);
	}
	return (0);
}

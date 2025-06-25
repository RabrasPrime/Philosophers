/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:33:41 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/25 14:07:05 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void let_fork(t_philosopher *philo)
{
    t_fork *first;
    t_fork *second;

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

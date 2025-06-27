/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:33:40 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/27 14:06:47 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   fork.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tjooris <tjooris@student.42lyon.fr>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/23 13:33:41 by tjooris		   #+#	#+#			 */
/*   Updated: 2025/06/27 14:03:01 by tjooris		  ###   ########.fr	   */
/*																			*/
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
	pthread_mutex_unlock(&first->fork);
	pthread_mutex_unlock(&second->fork);
}

int	taking_only_fork(t_philosopher *philo, t_fork *first)
{
	if (first->status == TAKEN)
	{
		pthread_mutex_unlock(&first->fork);
		return (1);
	}
	first->status = TAKEN;
	print(philo);
	pthread_mutex_unlock(&first->fork);
	return (1);
}

int	take_forks(t_philosopher *philo, t_fork *first, t_fork *second)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&first->fork);
	if (check_nb_philo(philo) == 1)
	{
		i = taking_only_fork(philo, first);
		return (i);
	}
	pthread_mutex_lock(&second->fork);
	if (first->status == TAKEN || second->status == TAKEN)
		i = 1;
	else
	{
		first->status = TAKEN;
		first->status = TAKEN;
		print(philo);
		print(philo);
	}
	pthread_mutex_unlock(&first->fork);
	pthread_mutex_unlock(&second->fork);
	return (i);
}

int	taking_forks(t_philosopher *philo, t_fork *first, t_fork *second)
{
	while (take_forks(philo, first, second))
	{
		if (check_philo_died(philo))
			return (1);
		usleep(200);
	}
	return (0);
}

int	fork_lock(t_philosopher *philo)
{
	t_fork	*first;
	t_fork	*second;
	int		i;

	i = 0;
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
	i = taking_forks(philo, first, second);
	return (i);
}

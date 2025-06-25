/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_thinking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:30:18 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/25 14:35:17 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

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
		//usleep(200);
	}
	while (take_fork(second))
	{
		if (check_philo_died(philo))
			return (1);
		//usleep(200);
	}
	return (0);
}

int	is_thinking(t_philosopher *philo)
{
	if (check_simulation_stop(philo))
		return (1);
	print_status(philo);
	usleep(300);
	fork_lock(philo);
    if (check_philo_died(philo))
      return (1);
    philo->status = TAKEN_FORKS;
	print_status(philo);
    philo->status = EAT;
	return (0);
}

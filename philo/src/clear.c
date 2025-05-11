/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:50:38 by tjooris           #+#    #+#             */
/*   Updated: 2025/05/11 22:24:30 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void clear_table(t_table *table, int nb_philo)
{
	int i;

	i = 0;
        while (i < nb_philo)
        {
            pthread_mutex_destroy(&table->forks[i].fork);
            i++;
        }
        free(table->forks);
        free(table);
}

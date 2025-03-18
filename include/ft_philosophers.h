/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:06:45 by tjooris           #+#    #+#             */
/*   Updated: 2025/03/18 09:54:46 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILOSOPHERS_H
# define FT_PHILOSOPHERS_H

#include "libft.h"
#include <pthread.h>
#include <stdlib.h>

enum	t_state
{
	SLEEP,
	EAT,
	THINK,
};

typedef	struct s_phylosopher
{
	int	number;
	int state;
}	t_phylosopher;

typedef struct s_table
{
	
}	t_table;

#endif
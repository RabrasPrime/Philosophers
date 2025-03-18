/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:07:41 by tjooris           #+#    #+#             */
/*   Updated: 2025/03/13 15:17:17 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void init_phylosophers(t_phylosopher **phylo, int argc)
{
	phylo = malloc (sizeof(t_phylosopher) * argc);
	if (!phylo)
		ft_error("erreur d'allocation");
}

int main(int argc, char **argv)
{
	int i;
	t_phylosopher	*phylosophers;

	init_phylosophers(phylosophers, argc);
	
}
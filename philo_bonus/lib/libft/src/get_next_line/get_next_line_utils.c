/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:20:37 by tjooris           #+#    #+#             */
/*   Updated: 2025/03/03 09:08:58 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "get_next_line.h"
#include "libft.h"

char	*ft_strndup(char *ptr, size_t n)
{
	char	*line;

	line = malloc(n + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, ptr, n);
	line[n] = '\0';
	return (line);
}

char	*handle_buffer_cleanup(t_buffer *buffer, char *line, ssize_t bytes_read)
{
	if (bytes_read <= 0 || line == NULL)
	{
		free(buffer->data);
		buffer->data = NULL;
		buffer->length = 0;
		buffer->capacity = 0;
		if (bytes_read == -1 || line == NULL)
		{
			free(line);
			line = NULL;
			return (NULL);
		}
	}
	return (line);
}

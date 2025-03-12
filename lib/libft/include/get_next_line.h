/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:20:19 by tjooris           #+#    #+#             */
/*   Updated: 2025/03/07 14:47:52 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_buffer
{
	char	*data;
	size_t	length;
	size_t	capacity;
}				t_buffer;

char	*get_next_line(int fd, int status);
char	*ft_strndup(char *ptr, size_t n);
char	*handle_buffer_cleanup(t_buffer *buffer,
			char *line, ssize_t bytes_read);

#endif

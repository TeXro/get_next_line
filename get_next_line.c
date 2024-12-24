/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzin <zzin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:12:58 by zzin              #+#    #+#             */
/*   Updated: 2024/12/24 17:29:05 by zzin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gen_line(char **saved, char *buffer)
{
	char	*new_saved;
	char	*line;
	char	*nline_pos;

	if (buffer)
		free(buffer);
	if (ft_strchr(*saved, '\n'))
	{
		nline_pos = ft_strchr(*saved, '\n');
		line = malloc(ft_strch(*saved, '\n') + 2);
		ft_memcpy(line, *saved, ft_strch(*saved, '\n') + 1);
		new_saved = ft_strjoin(NULL, nline_pos + 1);
		free(*saved);
		*saved = new_saved;
	}
	else
	{
		line = ft_strjoin(*saved, NULL);
		*saved = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*buffer;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		saved = ft_strjoin(saved, buffer);
		if (ft_strchr(saved, '\n'))
			return (gen_line(&saved, buffer));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (saved && *saved && bytes_read == 0)
		return (gen_line(&saved, buffer));
	free(saved);
	saved = NULL;
	return (free(buffer), NULL);
}

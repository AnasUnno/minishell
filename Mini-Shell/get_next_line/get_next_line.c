/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 02:33:24 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/08 17:53:13 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_join_free(char *buffer, char *buff)
{
	char	*tmp;

	tmp = ft_strjoins(buffer, buff);
	free(buffer);
	return (tmp);
}

char	*next_line(char *buffer)
{
	char	*buff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!*buffer)
		return (free(buffer), NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	buff = (char *)malloc(sizeof(char) * (ft_strlength(buffer) - i) + 1);
	if (!buff)
		return (free(buffer), NULL);
	if (buffer[i] == '\n')
		i++;
	while (buffer[i])
		buff[j++] = buffer[i++];
	return (free(buffer), buff[j] = 0, buff);
}

char	*get_my_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!*buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = (char *)malloc(sizeof(char) * (i + 2));
	else
		line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	return (line[i] = '\0', line);
}

char	*read_file(int fd, char *buffer)
{
	char	*buff;
	int		n_bytes;

	if (!buffer)
		buffer = ft_strd("");
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (free(buffer), NULL);
	n_bytes = 1;
	while (!(ft_strc(buffer, '\n')) && n_bytes != 0)
	{
		n_bytes = read(fd, buff, BUFFER_SIZE);
		if (n_bytes == -1)
			return (free(buff), free(buffer), NULL);
		buff[n_bytes] = '\0';
		buffer = ft_join_free(buffer, buff);
	}
	return (free(buff), buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (free(buffer), buffer = NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_my_line(buffer);
	buffer = next_line(buffer);
	return (line);
}

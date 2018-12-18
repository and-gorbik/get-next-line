/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:41:20 by sjacelyn          #+#    #+#             */
/*   Updated: 2018/12/18 17:28:18 by sjacelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** return:
** 1 - string is complete,
** -1 - error,
** 0 - next filling the buf from file
*/

static int	read_line(char **buf, char **line, char delim)
{
	char	*prev;
	char	*chunk;
	char	*sub;
	int		status;

	if ((sub = ft_strchr(*buf, delim)))
		status = 1;
	else
	{
		status = 0;
		sub = *buf + ft_strlen(*buf);
	}
	if (!(chunk = ft_strnew(sub - *buf)))
		return (-1);
	prev = *line;
	if (!(*line = ft_strjoin(prev, ft_strncpy(chunk, *buf, sub - *buf))))
		status = -1;
	else
		ft_strcpy(*buf, sub + status);
	free(chunk);
	free(prev);
	return (status);
}

int			get_next_line(const int fd, char **line)
{
	static char	buf[BUFF_SIZE + 1];
	char		*pbuf;
	int			status;

	if (fd < 0 || !line || read(fd, buf, 0) < 0)
		return (-1);
	if (!(*line = ft_strnew(0)))
		return (-1);
	pbuf = buf;
	if (!buf[0])
		buf[read(fd, buf, BUFF_SIZE)] = '\0';
	while (buf[0])
	{
		status = read_line(&pbuf, line, '\n');
		if (status)
			return (status);
		buf[read(fd, buf, BUFF_SIZE)] = '\0';
	}
	free(*line);
	*line = NULL;
	return (0);
}

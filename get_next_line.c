/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:41:20 by sjacelyn          #+#    #+#             */
/*   Updated: 2018/12/23 21:35:58 by sjacelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** returns:
** 1  - string is complete,
** -1 - error,
** 0  - next reading data from file to buffer
*/

static int	read_line_from_buffer(char **buf, char **line, char delim)
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
	CHECK_ERROR((chunk = ft_strnew(sub - *buf)));
	prev = *line;
	if (!(*line = ft_strjoin(prev, ft_strncpy(chunk, *buf, sub - *buf))))
		status = -1;
	else
		ft_strcpy(*buf, status ? sub + 1 : sub);
	ft_memdel((void **)&chunk);
	ft_memdel((void **)&prev);
	return (status);
}

/*
** This function returns a buffer by fd
*/

static char	*get_buffer(char **bufs, int fd)
{
	char	b[1];

	if (fd < 0 || fd == 1 || fd == 2 || fd >= FD_SIZE
		|| read(fd, b, 0) < 0 || !bufs)
		return (NULL);
	if (!bufs[fd])
		bufs[fd] = ft_strnew(BUFF_SIZE);
	return (bufs[fd]);
}

/*
** This function reads a line from file, excluding '\n'
** until '\0' is found.
** returns:
** 1  - string is complete,
** -1 - error,
** 0  - end of file
*/

int			get_next_line(const int fd, char **line)
{
	static char		*bufs[FD_SIZE];
	char			*buf;
	int				status;

	CHECK_ERROR(line && BUFF_SIZE > 0 && FD_SIZE > 0);
	CHECK_ERROR((buf = get_buffer(bufs, fd)));
	CHECK_ERROR((*line = ft_strnew(0)));
	if (!buf[0])
		buf[read(fd, buf, BUFF_SIZE)] = '\0';
	if (!buf[0])
	{
		ft_memdel((void **)&bufs[fd]);
		return (0);
	}
	while (buf[0])
	{
		status = read_line_from_buffer(&buf, line, '\n');
		if (status)
			return (status);
		buf[read(fd, buf, BUFF_SIZE)] = '\0';
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:41:20 by sjacelyn          #+#    #+#             */
/*   Updated: 2018/12/21 15:49:25 by sjacelyn         ###   ########.fr       */
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
	CHECK_ERROR((chunk = ft_strnew(sub - *buf)))
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
** this function create a new list item and returns a buffer.
** lst and fd are always valid.
*/

static char	*create_buffer(t_list **lst, int fd)
{
	t_buf	cur;
	t_list	*item;

	cur.fd = fd;
	if (!(cur.buf = ft_strnew(BUFF_SIZE)))
		return (NULL);
	if (!(item = ft_lstnew(&cur, sizeof(t_buf))))
	{
		ft_memdel((void **)&cur.buf);
		return (NULL);
	}
	ft_lstadd(lst, item);
	return (cur.buf);
}

/*
** if list item doesn't exist with such fd,
** this function create a new list item and returns a buffer,
** otherwise it returns an existing buffer.
*/

static char	*get_buffer(t_list **lst, int fd)
{
	char	b[1];
	t_buf	*cur;
	t_list	*item;

	if (!lst || fd < 0 || fd == 1 || fd == 2 || read(fd, b, 0) < 0)
		return (NULL);
	item = *lst;
	while (item)
	{
		cur = item->content;
		if (cur->fd == fd)
			return (cur->buf);
		item = item->next;
	}
	return (create_buffer(lst, fd));
}

/*
** this function removes an item with fd from the lst,
** freeing the item's buffer
*/

static void	remove_buffer(t_list **lst, int fd)
{
	t_list	*prev;
	t_list	*cur;
	t_buf	*data;

	cur = *lst;
	prev = NULL;
	while (cur)
	{
		data = cur->content;
		if (data->fd == fd)
			break ;
		cur = cur->next;
		prev = cur;
	}
	if (prev)
		prev->next = (cur ? cur->next : NULL);
	if (cur == *lst)
		*lst = NULL;
	ft_memdel((void **)&(data->buf));
	ft_memdel((void **)&(cur));
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
	static t_list	*bufs;
	char			*buf;
	int				status;

	CHECK_ERROR(line && BUFF_SIZE > 0)
	CHECK_ERROR((buf = get_buffer(&bufs, fd)))
	CHECK_ERROR((*line = ft_strnew(0)))
	if (!buf[0])
		buf[read(fd, buf, BUFF_SIZE)] = '\0';
	if (!buf[0])
	{
		remove_buffer(&bufs, fd);
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

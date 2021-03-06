/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacelyn <sjacelyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 17:13:28 by sjacelyn          #+#    #+#             */
/*   Updated: 2018/12/23 21:23:01 by sjacelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 21
# define FD_SIZE 2048
# define CHECK_ERROR(x) if (!x) return (-1);

# include "libft/libft.h"

int				get_next_line(const int fd, char **line);

#endif

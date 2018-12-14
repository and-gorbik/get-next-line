/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacelyn <sjacelyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 17:13:28 by sjacelyn          #+#    #+#             */
/*   Updated: 2018/12/10 22:40:25 by sjacelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# include "libft.h"

# define BUFF_SIZE (1 << 1)

int     get_next_line(const int fd, char **line);

#endif

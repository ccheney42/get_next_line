/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 16:51:48 by ccheney           #+#    #+#             */
/*   Updated: 2018/04/26 14:16:24 by ccheney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(const int fd, char *buff, int *x)
{
	char	tmp1[BUFF_SIZE + 1];
	char	*tmp2;

	*x = read(fd, tmp1, BUFF_SIZE);
	tmp1[*x] = '\0';
	tmp2 = buff;
	if (!(buff = ft_strjoin(buff, tmp1)))
		return (NULL);
	ft_strdel(&tmp2);
	return (buff);
}

int			copy_end(char **line, char **buff)
{
	if (!(*line = ft_strdup(*buff)))
		return (-1);
	ft_bzero(*buff, ft_strlen(*buff));
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	int			x;
	static char	*buff = "";
	char		*str;

	x = 1;
	if (!line || fd < 0 || (buff[0] == '\0' && (!(buff = ft_strnew(0)))))
		return (-1);
	while (x > 0)
	{
		if ((str = ft_strchr(buff, '\n')) != NULL)
		{
			*str = '\0';
			if (!(*line = ft_strdup(buff)))
				return (-1);
			ft_memmove(buff, str + 1, ft_strlen(str + 1) + 1);
			return (1);
		}
		if (!(buff = read_line(fd, buff, &x)))
			return (-1);
	}
	ft_strdel(&str);
	if (x == 0 && ft_strlen(buff))
		x = copy_end(&(*line), &buff);
	return (x);
}

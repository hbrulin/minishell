/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 10:26:33 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/12 13:51:05 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_fill_line(char **s, char **line, int len)
{
	char	*tmp;

	if ((*s)[len] == '\n')
	{
		*line = ft_substr(*s, 0, len);
		tmp = ft_strdup((*s) + len + 1);
		free((*s));
		(*s) = tmp;
		if ((*s)[0] == '\0')
		{
			free(*s);
			*s = NULL;
		}
	}
	else if ((*s)[len] == '\0')
	{
		*line = ft_strdup(*s);
		free(*s);
		*s = NULL;
		return (0);
	}
	return (1);
}

int		ft_return(char **line, char **s, int ret)
{
	int len;

	len = 0;
	if (ret < 0)
	{
		return (-1);
	}
	else if (ret == 0 && (*s == NULL || (*s)[0] == '\0'))
	{
		*line = ft_strdup("");
		return (0);
	}
	while ((*s)[len] != '\n' && (*s)[len])
		len++;
	return (ft_fill_line(s, line, len));
}

int		get_next_line(int fd, char **line)
{
	static char		*s;
	char			buf[BUFFER_SIZE + 1];
	char			*tmp;
	int				ret;

	if (fd < 0 || line == NULL || BUFFER_SIZE == 0)
	{
		return (-1);
	}
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (s == NULL)
			s = ft_strnew(1);
		tmp = ft_strjoin(s, buf);
		free(s);
		s = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (ft_return(line, &s, ret));
}

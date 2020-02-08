/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:48:12 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 11:54:38 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "printf.h"

int		ft_get_data(t_data *data, const char *str, va_list ap)
{
	static int	(*f_conversion[8])(va_list, t_data *) = {
		&ft_id, &ft_c, &ft_s, &ft_p, &ft_u, &ft_x, &ft_x_upper, &ft_pourc };

	if (ft_assign_data(data) == MALLOC_FAIL)
		return (data->error);
	data->format = get_format(str, data->i + 1);
	get_flags(str, data->i + 1, data);
	if (!data->format)
	{
		ft_free(data);
		return (EXIT);
	}
	if ((*f_conversion[ft_index(data)])(ap, data) == MALLOC_FAIL)
		return (data->error);
	return (0);
}

void	ft_launch_output(t_data *data, int fd)
{
	ft_output(data, fd);
	if (data->flags != NULL)
		data->i += ft_strlen(data->flags);
	data->i++;
	ft_free(data);
}

void	data_init(t_data *data)
{
	data->value = 0;
	data->i = 0;
}

int		ft_printf_fd(int fd, const char *str, ...)
{
	va_list		ap;
	t_data		data;

	data_init(&data);
	va_start(ap, str);
	while (str[data.i] != '\0')
	{
		if (str[data.i] == '%' && ft_strlen(str) != 1)
		{
			if (ft_get_data(&data, str, ap) != 0)
				return (data.error);
			ft_launch_output(&data, fd);
		}
		else
		{
			ft_putchar_fd(str[data.i], fd);
			data.value++;
		}
		data.i++;
	}
	va_end(ap);
	return (data.value);
}

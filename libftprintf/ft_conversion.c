/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:49:15 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 11:54:04 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "printf.h"

char	get_format(const char *str, int i)
{
	while (str[i] != '\0')
	{
		if (str[i] == 'i' || str[i] == 'c' || str[i] == 's' || str[i] == 'p' ||
			str[i] == 'd' || str[i] == 'u' || str[i] == 'x' || str[i] == 'X' ||
			str[i] == '%')
			return (str[i]);
		i++;
	}
	return (0);
}

int		ft_index(t_data *data)
{
	if (data->format == 'i' || data->format == 'd')
		return (0);
	if (data->format == 'c')
		return (1);
	if (data->format == 's')
		return (2);
	if (data->format == 'p')
		return (3);
	if (data->format == 'u')
		return (4);
	if (data->format == 'x')
		return (5);
	if (data->format == 'X')
		return (6);
	if (data->format == '%')
		return (7);
	return (-1);
}

int		ft_id(va_list ap, t_data *data)
{
	int n;

	if (data->star_fwidth == 1)
		data->star_arg = va_arg(ap, int);
	if (data->star_fprec == 1)
		data->star_arg2 = va_arg(ap, int);
	n = va_arg(ap, int);
	if (n < 0)
		data->neg_i++;
	if (!(data->output = ft_itoa(n)))
		return (set_error(data));
	if (data->flags != NULL)
		ft_launch_flags(data);
	return (0);
}

int		ft_c(va_list ap, t_data *data)
{
	char c;

	if (data->star_fwidth == 1)
		data->star_arg = va_arg(ap, int);
	if (data->star_fprec == 1)
		data->star_arg2 = va_arg(ap, int);
	c = va_arg(ap, int);
	data->c = c;
	if (data->flags != NULL)
		ft_launch_flags(data);
	return (0);
}

int		ft_s(va_list ap, t_data *data)
{
	char *output;

	if (data->star_fwidth == 1)
		data->star_arg = va_arg(ap, int);
	if (data->star_fprec == 1)
		data->star_arg2 = va_arg(ap, int);
	output = va_arg(ap, char *);
	if (output == NULL)
	{
		if (!(data->output = ft_strdup("(null)")))
			return (set_error(data));
	}
	else
	{
		if (!(data->output = ft_strdup(output)))
			return (set_error(data));
	}
	if (data->flags != NULL)
		ft_launch_flags(data);
	return (0);
}

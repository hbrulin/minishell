/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion_pt2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 11:08:22 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 11:53:42 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "printf.h"

int		ft_p(va_list ap, t_data *data)
{
	unsigned long	adress;
	char			*output;

	if (data->star_fwidth == 1)
		data->star_arg = va_arg(ap, int);
	if (data->star_fprec == 1)
		data->star_arg2 = va_arg(ap, int);
	adress = va_arg(ap, unsigned long);
	if (adress == 0 && (data->flag_bit & PRECISION))
	{
		if (!(data->output = ft_strdup("0x")))
			return (set_error(data));
	}
	else
	{
		if (!(output = aff_hex(adress)))
			return (set_error(data));
		if (!(data->output = ft_strjoin("0x", output)))
			return (set_error(data));
		free(output);
	}
	if (data->flags != NULL)
		ft_launch_flags(data);
	return (0);
}

int		ft_u(va_list ap, t_data *data)
{
	unsigned int u;

	if (data->star_fwidth == 1)
		data->star_arg = va_arg(ap, int);
	if (data->star_fprec == 1)
		data->star_arg2 = va_arg(ap, int);
	u = va_arg(ap, unsigned int);
	if (!(data->output = ft_uitoa(u)))
		return (set_error(data));
	if (data->flags != NULL)
		ft_launch_flags(data);
	return (0);
}

int		ft_x(va_list ap, t_data *data)
{
	unsigned int x;

	if (data->star_fwidth == 1)
		data->star_arg = va_arg(ap, int);
	if (data->star_fprec == 1)
		data->star_arg2 = va_arg(ap, int);
	x = va_arg(ap, unsigned int);
	if (!(data->output = aff_hex(x)))
		return (set_error(data));
	if (data->flags != NULL)
		ft_launch_flags(data);
	return (0);
}

int		ft_x_upper(va_list ap, t_data *data)
{
	unsigned int	x;
	int				j;

	if (data->star_fwidth == 1)
		data->star_arg = va_arg(ap, int);
	if (data->star_fprec == 1)
		data->star_arg2 = va_arg(ap, int);
	j = 0;
	x = va_arg(ap, unsigned int);
	if (!(data->output = aff_hex(x)))
		return (set_error(data));
	while (data->output[j] != '\0')
	{
		data->output[j] = ft_toupper(data->output[j]);
		j++;
	}
	if (data->flags != NULL)
		ft_launch_flags(data);
	return (0);
}

int		ft_pourc(va_list ap, t_data *data)
{
	if (data->star_fwidth == 1)
		data->star_arg = va_arg(ap, int);
	if (data->star_fprec == 1)
		data->star_arg2 = va_arg(ap, int);
	data->c = '%';
	if (data->flags != NULL)
		ft_launch_flags(data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:48:53 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 11:54:42 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "printf.h"

int		set_error(t_data *data)
{
	ft_putstr("MALLOC_FAIL");
	data->error = MALLOC_FAIL;
	return (data->error);
}

int		ft_assign_data(t_data *data)
{
	if (!(data->flags = ft_strnew(6)))
		return (set_error(data));
	data->flag_bit = 0;
	data->output = NULL;
	data->precision_nbr = 0;
	data->width_nbr = 0;
	data->star_fwidth = 0;
	data->star_fprec = 0;
	data->star_arg = 0;
	data->star_arg2 = 0;
	data->flag_zero = 0;
	data->neg = 0;
	data->neg_i = 0;
	data->nbr_pad = 0;
	data->error = 0;
	return (0);
}

void	ft_free(t_data *data)
{
	if (data->flags)
	{
		free(data->flags);
		data->flags = NULL;
	}
	if (data->output)
	{
		free(data->output);
		data->output = NULL;
	}
}

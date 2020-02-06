/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:57:24 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 11:54:50 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "printf.h"

int		ft_width_output(t_data *data, char *padding, int neg)
{
	char	*output2;

	if (neg == 1 || data->flag_bit & MINUS)
	{
		if (!(output2 = ft_strjoin(data->output, padding)))
			return (set_error(data));
	}
	else
	{
		if (!(output2 = ft_strjoin(padding, data->output)))
			return (set_error(data));
	}
	free(data->output);
	if (!(data->output = ft_strdup(output2)))
		return (set_error(data));
	free(output2);
	return (0);
}

int		ft_width(t_data *data)
{
	int		j;
	char	*padding;
	int		neg;

	if (ft_width_check_format(data) == EXIT)
		return (EXIT);
	neg = 0;
	get_width_nbr(data);
	ft_init_neg(data, &neg);
	if (ft_init_nbr_pad(data) == EXIT)
		return (EXIT);
	if (!(padding = ft_strnew(data->nbr_pad)))
		return (set_error(data));
	j = 0;
	while (data->nbr_pad--)
		padding[j++] = ' ';
	if (ft_width_output(data, padding, neg) == MALLOC_FAIL)
		return (data->error);
	free(padding);
	return (0);
}

int		ft_width_c(t_data *data)
{
	int j;

	get_width_nbr(data);
	if (data->width_nbr < 0)
	{
		data->width_nbr *= -1;
		data->neg = 1;
	}
	if (data->width_nbr == 0)
		return (EXIT);
	if (!(data->output = (char*)malloc(sizeof(char) * data->width_nbr + 1)))
		return (set_error(data));
	j = 0;
	while (data->width_nbr)
	{
		data->output[j] = ' ';
		j++;
		data->width_nbr--;
	}
	data->output[j] = '\0';
	return (0);
}

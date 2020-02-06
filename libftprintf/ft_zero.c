/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zero.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:57:55 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 11:54:54 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "printf.h"

int	ft_zero_neg_i_output(t_data *data, int i, char *zero)
{
	char	*number;
	char	*minus;
	char	*output;

	if (!(minus = ft_strdup("-")))
		return (set_error(data));
	if (!(number = ft_strdup(data->output + i + 1)))
		return (set_error(data));
	free(data->output);
	if (!(output = ft_strjoin(minus, zero)))
		return (set_error(data));
	free(minus);
	if (!(data->output = ft_strjoin(output, number)))
		return (set_error(data));
	free(output);
	free(number);
	return (0);
}

int	ft_zero_neg_i(t_data *data)
{
	char	*zero;
	int		i;

	if (data->output[0] == '-')
		return (EXIT);
	i = 0;
	if (!(zero = ft_strnew(data->width_nbr)))
		return (set_error(data));
	while (data->output[i] == '0')
	{
		zero[i] = '0';
		i++;
	}
	if (ft_zero_neg_i_output(data, i, zero) == MALLOC_FAIL)
		return (data->error);
	free(zero);
	return (0);
}

int	ft_zero(t_data *data)
{
	int i;

	i = 0;
	if (data->format == 's' || data->format == 'c' || data->format == 'p')
		return (EXIT);
	if (!(data->flag_bit & PRECISION) || data->precision_nbr < 0
		|| data->format == '%')
	{
		while (data->output[i] == ' ' && data->output[i] != '\0')
		{
			data->output[i] = '0';
			i++;
		}
	}
	if (data->neg_i == 1 && data->width_nbr != 0
		&& (!(data->flag_bit & PRECISION) || data->precision_nbr < 0))
	{
		if (ft_zero_neg_i(data) == MALLOC_FAIL)
			return (data->error);
		return (EXIT);
	}
	return (0);
}

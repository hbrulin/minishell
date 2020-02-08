/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:53:44 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 11:54:15 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "printf.h"

int		ft_check_output(t_data *data, int fd)
{
	if (!data->output)
	{
		ft_putchar_fd(data->c, fd);
		data->value++;
		return (-1);
	}
	return (0);
}

void	ft_neg_minus_c(t_data *data, int *value, int *j, int fd)
{
	ft_putchar(data->c);
	*value = *value + 1;
	while (data->output[*j])
	{
		ft_putchar_fd(data->output[*j], fd);
		*value = *value + 1;
		*j = *j + 1;
	}
}

void	ft_output_c(t_data *data, int fd)
{
	int j;
	int value;

	j = 1;
	if (ft_check_output(data, fd) == -1)
		return ;
	value = 0;
	if (data->neg == 1 || data->flag_bit & MINUS)
		ft_neg_minus_c(data, &value, &j, fd);
	else
	{
		while (data->output[j])
		{
			ft_putchar_fd(data->output[j], fd);
			value++;
			j++;
		}
		ft_putchar_fd(data->c, fd);
		value++;
	}
	data->value += value;
}

void	ft_output(t_data *data, int fd)
{
	int j;
	int value;

	j = 0;
	value = 0;
	if (data->format == 'c' || data->format == '%')
	{
		ft_output_c(data, fd);
		return ;
	}
	while (data->output[j])
	{
		ft_putchar_fd(data->output[j], fd);
		value++;
		j++;
	}
	if (data->flag_zero == 1 && data->width_nbr == 0)
		value = 0;
	data->value += value;
}

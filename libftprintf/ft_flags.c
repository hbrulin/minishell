/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:54:00 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 11:54:09 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "printf.h"

void	ft_set_null(t_data *data)
{
	int len;

	len = ft_strlen(data->flags);
	if (len <= 0)
	{
		free(data->flags);
		data->flags = NULL;
	}
}

void	get_flags(const char *str, int i, t_data *data)
{
	int j;

	j = 0;
	while (str[i] != data->format && str[i] != '\0')
	{
		if (str[i] == '.' || str[i] == '-' || str[i] == '*' ||
			ft_isdigit(str[i]))
		{
			if (str[i] == '*' && str[i - 1] == '.')
				data->star_fprec++;
			else if (str[i] == '*')
				data->star_fwidth++;
			data->flags[j] = str[i];
			j++;
		}
		else
			break ;
		i++;
	}
	data->flags[j] = '\0';
	get_flag_bit(data);
	ft_set_null(data);
}

void	get_precision_bit(t_data *data)
{
	int i;

	i = 0;
	while (data->flags[i])
	{
		if (data->flags[i] == '.')
			data->flag_bit += PRECISION;
		i++;
	}
}

void	get_flag_bit(t_data *data)
{
	if ((data->flags[0] == '0' && data->flags[1] == '-') ||
		(data->flags[0] == '-' && data->flags[1] == '0'))
	{
		data->flag_bit += MINUS;
		data->flag_bit += WIDTH;
	}
	else if (data->flags[0] == '0')
	{
		data->flag_bit += ZERO;
		data->flag_bit += WIDTH;
	}
	else if (data->flags[0] == '-')
	{
		data->flag_bit += MINUS;
		data->flag_bit += WIDTH;
	}
	else if (ft_isdigit(data->flags[0]))
		data->flag_bit += WIDTH;
	else if (data->star_fwidth == 1)
		data->flag_bit += WIDTH;
	get_precision_bit(data);
}

int		ft_launch_flags(t_data *data)
{
	if (data->flag_bit & PRECISION)
	{
		if (ft_precision(data) == MALLOC_FAIL)
			return (data->error);
	}
	if (data->flag_bit & WIDTH)
		if (ft_width(data) == MALLOC_FAIL)
			return (data->error);
	if (ft_strlen(data->flags) != 1)
	{
		if ((data->flag_bit & ZERO) && (data->flag_bit & WIDTH))
		{
			if (ft_zero(data) == MALLOC_FAIL)
				return (data->error);
		}
	}
	return (0);
}

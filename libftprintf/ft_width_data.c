/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 12:38:07 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 11:54:46 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "printf.h"

void	get_width_nbr(t_data *data)
{
	int		i;
	int		j;
	char	nb[ft_strlen(data->flags) + 1];

	if (data->star_fwidth == 1)
	{
		data->width_nbr = data->star_arg;
		return ;
	}
	i = 0;
	j = 0;
	while (data->flags[i] != '\0' && (data->flags[i] == '0' ||
		data->flags[i] == '-'))
		i++;
	while (data->flags[i] != '\0' && data->flags[i] != '.')
	{
		if (ft_isdigit(data->flags[i]))
		{
			nb[j] = data->flags[i];
			j++;
		}
		i++;
	}
	nb[j] = '\0';
	data->width_nbr = ft_atoi(nb);
}

int		ft_width_check_format(t_data *data)
{
	if (data->format == 'c' || data->format == '%')
	{
		if (ft_width_c(data) == MALLOC_FAIL)
			return (data->error);
		return (EXIT);
	}
	return (0);
}

int		ft_init_nbr_pad(t_data *data)
{
	if (data->width_nbr > (int)ft_strlen(data->output))
	{
		data->nbr_pad = data->width_nbr - ft_strlen(data->output);
		return (0);
	}
	else
		return (EXIT);
}

void	ft_init_neg(t_data *data, int *neg)
{
	if (data->width_nbr < 0)
	{
		data->width_nbr *= -1;
		*neg = 1;
	}
}

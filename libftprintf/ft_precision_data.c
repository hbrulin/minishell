/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 12:08:43 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 11:54:19 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "printf.h"

int		ft_star_precision(t_data *data)
{
	if (data->star_fprec == 1)
	{
		data->precision_nbr = data->star_arg2;
		return (0);
	}
	else
		return (EXIT);
}

void	get_precision_nbr(t_data *data)
{
	int		i;
	int		j;
	char	nb[ft_strlen(data->flags)];

	i = 0;
	j = 0;
	if (ft_star_precision(data) == 0)
		return ;
	while (data->flags[i] != '\0')
	{
		if (data->flags[i] == '.')
			break ;
		i++;
	}
	while (data->flags[i] != '\0')
	{
		if (ft_isdigit(data->flags[i]))
		{
			nb[j] = data->flags[i];
			j++;
		}
		i++;
	}
	nb[j] = '\0';
	data->precision_nbr = ft_atoi(nb);
}

int		ft_precision_check_format(t_data *data)
{
	if (data->format == 'c' || data->format == 'p' || data->format == '%')
		return (-1);
	if (data->format == 's')
	{
		if (ft_precision_s(data) == MALLOC_FAIL)
			return (data->error);
		return (EXIT);
	}
	else
		return (0);
}

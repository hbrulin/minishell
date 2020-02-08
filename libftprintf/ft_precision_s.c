/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision_s.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 19:07:33 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 11:54:23 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "printf.h"

int		precision_s_output(t_data *data)
{
	char	*output2;
	int		j;

	if (!(output2 = ft_strnew(data->precision_nbr)))
		return (set_error(data));
	j = 0;
	while (data->output[j] != '\0' && data->precision_nbr)
	{
		output2[j] = data->output[j];
		j++;
		data->precision_nbr--;
	}
	output2[j] = '\0';
	free(data->output);
	if (!(data->output = ft_strdup(output2)))
		return (set_error(data));
	free(output2);
	return (0);
}

int		ft_precision_s(t_data *data)
{
	get_precision_nbr(data);
	if (data->precision_nbr < 0)
		return (EXIT);
	if (data->precision_nbr == 0 || !(data->precision_nbr))
	{
		free(data->output);
		if (!(data->output = ft_strdup("")))
			return (set_error(data));
		return (EXIT);
	}
	if (precision_s_output(data) == MALLOC_FAIL)
		return (data->error);
	return (0);
}

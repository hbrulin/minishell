/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision_spec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 19:07:05 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 11:54:29 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "printf.h"

int		ft_precision_empty_output(t_data *data)
{
	if (data->precision_nbr < 0)
		return (EXIT);
	if (data->precision_nbr == 0 && ft_strncmp(data->output, "0", 1) == 0)
	{
		free(data->output);
		if (!(data->output = ft_strdup("")))
			return (set_error(data));
		data->flag_zero = 1;
		return (EXIT);
	}
	return (0);
}

int		ft_precision_specific_cases(t_data *data)
{
	if (data->nbr_pad < 0)
		return (EXIT);
	else if (data->neg_i == 1)
	{
		data->nbr_pad++;
		if (ft_precision_neg_i(data) == MALLOC_FAIL)
			return (data->error);
		return (EXIT);
	}
	return (0);
}

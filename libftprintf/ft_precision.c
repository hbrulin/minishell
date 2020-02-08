/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:55:43 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 11:54:33 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "printf.h"

int		ft_precision_neg_i_output(t_data *data, char *padding, char *nbr)
{
	char	*output2;

	if (!(output2 = ft_strjoin(padding, nbr)))
		return (set_error(data));
	if (!(data->output = ft_strdup(output2)))
		return (set_error(data));
	free(output2);
	return (0);
}

int		ft_precision_neg_i(t_data *data)
{
	int		j;
	char	*padding;
	char	*nbr;

	j = 1;
	if (!(padding = ft_strnew(data->nbr_pad + 1)))
		return (set_error(data));
	padding[0] = '-';
	if (!(nbr = ft_substr(data->output, 1, ft_strlen(data->output))))
		return (set_error(data));
	free(data->output);
	while (data->nbr_pad)
	{
		padding[j] = '0';
		j++;
		data->nbr_pad--;
	}
	padding[j] = '\0';
	if (ft_precision_neg_i_output(data, padding, nbr) == MALLOC_FAIL)
		return (data->error);
	free(nbr);
	free(padding);
	return (0);
}

int		ft_precision_output(t_data *data, char *padding)
{
	char	*output2;

	if (!(output2 = ft_strjoin(padding, data->output)))
		return (set_error(data));
	free(data->output);
	if (!(data->output = ft_strdup(output2)))
		return (set_error(data));
	free(output2);
	return (0);
}

int		ft_precision(t_data *data)
{
	int		j;
	char	*padding;

	if (ft_precision_check_format(data) != 0)
		return (data->error);
	get_precision_nbr(data);
	if (ft_precision_empty_output(data) != 0)
		return (data->error);
	data->nbr_pad = data->precision_nbr - ft_strlen(data->output);
	j = 0;
	if (ft_precision_specific_cases(data) != 0)
		return (data->error);
	else
	{
		if (!(padding = ft_strnew(data->nbr_pad)))
			return (set_error(data));
		while (data->nbr_pad--)
			padding[j++] = '0';
	}
	if (ft_precision_output(data, padding) == MALLOC_FAIL)
		return (data->error);
	free(padding);
	return (0);
}

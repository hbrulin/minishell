/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:18:23 by hbrulin           #+#    #+#             */
/*   Updated: 2019/11/11 10:59:06 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_neg(int ctr, const char *str)
{
	if (str[ctr] == '-')
		return (-1);
	else
		return (1);
}

int	ft_atoi(const char *str)
{
	int nbr;
	int ctr;
	int neg;

	ctr = 0;
	nbr = 0;
	neg = 1;
	while (str[ctr] == ' ' || str[ctr] == '\n' || str[ctr] == '\r' ||
			str[ctr] == '\v' || str[ctr] == '\t' || str[ctr] == '\f')
		ctr++;
	if (str[ctr] == '+' || str[ctr] == '-')
	{
		neg = ft_neg(ctr, str);
		ctr++;
	}
	while (str[ctr] >= '0' && str[ctr] <= '9')
	{
		nbr = nbr * 10 + str[ctr] - '0';
		ctr++;
	}
	return (nbr * neg);
}

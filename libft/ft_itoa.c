/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 18:47:15 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/07 08:15:04 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_fill_char(int size, int n, char *ret)
{
	int tmp;

	size--;
	if (n < 0)
	{
		tmp = -n;
		ret[0] = '-';
	}
	else
		tmp = n;
	if (tmp >= 10)
	{
		ft_fill_char(size, tmp / 10, ret);
		ret[size] = tmp % 10 + '0';
	}
	else
		ret[size] = tmp + '0';
	return (ret);
}

int		ft_size(int n)
{
	int tmp;
	int size;

	size = 0;
	if (n < 0)
	{
		size++;
		tmp = -n;
	}
	else
		tmp = n;
	while (tmp > 0)
	{
		tmp = tmp / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		size;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (!n || n == 0)
		return (ft_strdup("0"));
	size = ft_size(n);
	ret = ft_strnew(size);
	return (ft_fill_char(size, n, ret));
}

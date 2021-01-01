/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:40:29 by kcedra            #+#    #+#             */
/*   Updated: 2020/07/31 02:08:13 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa_neg(long long int nb, long long int copy)
{
	int		len;
	char	*s;

	nb = nb * (-1);
	len = 0;
	while (copy / 10 != 0)
	{
		copy = copy / 10;
		len++;
	}
	len += 2;
	if (!(s = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s[len] = '\0';
	while (len != 1)
	{
		len--;
		s[len] = (nb % 10) + 48;
		nb = nb / 10;
	}
	s[0] = '-';
	return (s);
}

char		*ft_itoa(long long int nb)
{
	int					len;
	long long int		copy;
	char				*s;

	copy = nb;
	if (nb < 0)
		return (ft_itoa_neg(nb, copy));
	len = 0;
	while (copy / 10 != 0)
	{
		copy = copy / 10;
		len++;
	}
	len += 1;
	if (!(s = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s[len] = '\0';
	while (len != 0)
	{
		len--;
		s[len] = (nb % 10) + 48;
		nb = nb / 10;
	}
	return (s);
}

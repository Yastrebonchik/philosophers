/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:51:33 by kcedra            #+#    #+#             */
/*   Updated: 2020/05/22 23:51:34 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tolower(int c)
{
	if (c > 64 && c < 91)
	{
		c += 32;
		return (c);
	}
	else
		return (c);
}

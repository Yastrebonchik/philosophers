/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 16:33:06 by alexander         #+#    #+#             */
/*   Updated: 2020/09/16 16:33:09 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double		ft_abs(double a)
{
	if (a < 0)
		a = a * (-1);
	return (a);
}
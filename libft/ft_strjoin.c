/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:47:39 by kcedra            #+#    #+#             */
/*   Updated: 2020/06/05 01:29:27 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		cur_i;
	char	*new_str;
	int		reslen;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	cur_i = 0;
	reslen = ft_strlen(s1) + ft_strlen(s2);
	if (!(new_str = (char*)malloc(reslen * (sizeof(char) + 1))))
		return (NULL);
	cur_i = 0;
	while (s1[i] != '\0')
		new_str[cur_i++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		new_str[cur_i++] = s2[i++];
	new_str[cur_i] = '\0';
	return (new_str);
}

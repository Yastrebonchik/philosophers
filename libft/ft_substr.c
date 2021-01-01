/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:51:18 by kcedra            #+#    #+#             */
/*   Updated: 2020/08/24 19:40:30 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			cur_len;
	char			*substr;
	size_t			slen;

	if (!s)
		return (NULL);
	if (!(substr = ((char*)malloc((len + 1) * (sizeof(char))))))
		return (NULL);
	slen = ft_strlen(s);
	if (slen < start + 1 || len == 0)
	{
		substr[0] = '\0';
		return (substr);
	}
	i = start;
	cur_len = 0;
	while (s[i] != '\0' && cur_len < len)
		substr[cur_len++] = s[i++];
	substr[cur_len] = '\0';
	return (substr);
}

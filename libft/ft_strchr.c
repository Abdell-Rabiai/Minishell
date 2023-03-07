/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:48:23 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/07 14:40:59 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	c1;

	c1 = c;
	if (c1 == '\0')
		return ((char *)(s + ft_strlen(s)));
	while (*s)
	{
		if (*s == c1)
			return ((char *)s);
		s++;
	}
	return (0);
}

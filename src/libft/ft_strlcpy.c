/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:38:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/24 22:57:10 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = ft_strlen(src);
	if (!dstsize)
		return (len);
	while (*src && (dstsize - 1))
	{
		*dst = *src;
		dst++;
		src++;
		dstsize--;
	}
	*dst = '\0';
	return (len);
}

char	*ft_strncpy(char *dst, const char *src, size_t num)
{
	size_t	i;

	i = -1;
	while (src[++i] && i < num)
		dst[i] = src[i];
	while (i < num)
		dst[i++] = '\0';
	return (dst);
}

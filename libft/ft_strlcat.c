/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:38:36 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/11 16:51:36 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	ls;
	size_t	ld;
	size_t	i;
	
	ls = ft_strlen(src);
	if (!dst && !dstsize)
		return (ls);
	ld = ft_strlen(dst);
	if (!dstsize || dstsize <= ld)
		return (ls + dstsize);
	i = 0;
	while (src[i] && (i < (dstsize - ld - 1)))
	{
		dst[ld + i] = src[i];
		i++;
	}
	dst[ld + i] = '\0';
	return (ls + ld);
}

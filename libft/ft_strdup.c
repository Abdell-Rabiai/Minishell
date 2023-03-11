/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:40:49 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/11 16:41:03 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1, int flag)
{
	char	*copy;
	int		len;
	int		i;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, s1, len + 1);
	if (flag == 1)
		free((char *)s1);
	return (copy);
}

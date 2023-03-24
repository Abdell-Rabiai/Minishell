/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:40:49 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/24 22:58:38 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1, bool flag)
{
	char	*copy;
	int		len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, s1, len + 1);
	if (flag == 1)
		free((char *)s1);
	return (copy);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*new_str;
	size_t	i;

	new_str = (char *)malloc(sizeof(char) * (n + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < n && s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

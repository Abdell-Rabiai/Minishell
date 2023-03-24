/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:05:21 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/24 22:57:49 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2, int flag)
{
	char			*to_return;
	unsigned int	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	to_return = (char *)malloc((len + 1)
			* sizeof(char));
	if (!to_return)
		return (NULL);
	ft_strlcpy(to_return, s1, ft_strlen(s1) + 1);
	ft_strlcat(to_return, s2, len + 1);
	if (flag == 1)
		free((char *)s1);
	else if (flag == 2)
		free((char *)s2);
	else if (flag == 3)
	{
		free((char *)s1);
		free((char *)s2);
	}
	return (to_return);
}

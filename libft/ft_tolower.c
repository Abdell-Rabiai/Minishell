/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:36:11 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/23 21:58:01 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void str_to_lower(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
}

int	ft_tolower(int c)
{
	if (65 <= c && c <= 90)
		c += 32;
	return (c);
}

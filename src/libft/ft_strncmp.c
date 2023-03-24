/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:57:57 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/10 18:09:10 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (*a && n)
	{
		if (*a - *b)
			return (*a - *b);
		a++;
		b++;
		n--;
	}
	if (!(*a) && n)
		return (-(*b));
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (*a)
	{
		if (*a - *b)
			return (*a - *b);
		a++;
		b++;
	}
	if (!(*a))
		return (-(*b));
	return (0);
}
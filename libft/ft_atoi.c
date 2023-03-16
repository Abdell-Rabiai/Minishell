/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:32:05 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/15 21:19:09 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
		return (1);
	return (0);
}

long long	ft_atoi(const char *str)
{
	long long	result;
	long long	sign;

	result = 0;
	sign = 1;
	while (is_whitespace(*str))
		str++;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
		sign *= (-1);
	str++;
	}
	while (*str && ft_isdigit((*str)))
	{
		result *= 10;
		result += *str - '0';
		if ( result > 2147483648 && sign == -1)
			return (0);
		else if (result > 2147483647 && sign == 1)
			return (0);
		str++;
	}
	return (result * (sign));
}

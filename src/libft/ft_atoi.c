/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:32:05 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/05/21 23:24:46 by arabiai          ###   ########.fr       */
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

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

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
		str++;
	}
	return (result * (sign));
}

void	handle_atoi_sign(const char **str, int *sign)
{
	if (**str && (**str == '-' || **str == '+'))
	{
		if (**str == '-')
			*sign *= (-1);
		(*str)++;
	}
}

long long	ft_atoi_exit(const char *str, int *i)
{
	long double	result;
	int			sign;

	result = 0;
	sign = 1;
	*i = 0;
	while (is_whitespace(*str))
		str++;
	handle_atoi_sign(&str, &sign);
	if (!ft_isdigit(*str))
		*i = 1;
	while (*str && ft_isdigit((*str)))
	{
		result *= 10;
		result += *str - '0';
		if ((result > __LONG_LONG_MAX__ && sign == 1)
			|| (result - 1 > __LONG_LONG_MAX__ && sign == -1))
			*i = 1;
		str++;
	}
	return (result * (sign));
}

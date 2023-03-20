/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:13:59 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/20 15:27:20 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_for_newline_option(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '-')
		i++;
	else
		return (1);
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (1);
	}
	return (0);
}


void my_echo(char **strs)
{
	int i;
	int new_line;
	int op;

	new_line = 0;
	i = 1;
	op = 0;
	while (strs[i])
	{
		if (!check_for_newline_option(strs[i]) && op == 0)
		{
			i++;
			new_line = 1;
		}
		else
		{
			op = 1;
			if (!strcmp(strs[i], "$?"))
				printf("%d", global_es);
			else
				printf("%s", strs[i]);
			if (strs[i + 1])
				printf(" ");
			i++;
		}
	}
	if (new_line == 0)
		printf("\n");
}

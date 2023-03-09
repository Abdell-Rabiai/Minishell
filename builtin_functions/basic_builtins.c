/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:34:06 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/09 19:15:35 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    echo(char *str, bool option)
{
	if (option)
		printf("%s", str);
	else
		printf("%s\n", str);
}

void    pwd(void)
{
	char    str[256];

	if (!getcwd(str, sizeof(str)))
		ft_printf(2, "Error printing current working directory!\n");
	else
		printf("%s\n", str);
}

void    cd(char *path)
{
	if (chdir(path))
		ft_printf(2, "bash: cd: %s: No such file or directory\n", path);
}

void    exitt(void)
{
    exit(0);
}
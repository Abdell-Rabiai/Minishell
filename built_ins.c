/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:31:12 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/06 20:34:15 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("Error printing current working directory!\n");
	else
		printf("%s\n", str);
}

void    cd(char *path)
{
	if (chdir(path))
		printf("Error changing directory!\n");
}

void export(char **envp)
{
	int i = 0;
	sort_envp(envp);
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

void unset(char *str, char **envp)
{
	(void)str;
	int i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			free(envp[i]);
		i++;
	}
}

void env(char **envp)
{
	int i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]); 
		i++;
	}
}
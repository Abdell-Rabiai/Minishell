/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:31:12 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/06 19:35:51 by arabiai          ###   ########.fr       */
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

void sort_envp(char **envp)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    while (envp[i])
    {
        j = i + 1;
        while (envp[j])
        {
            if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i])) > 0)
            {
                tmp = envp[i];
                envp[i] = envp[j];
                envp[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

void export(char **envp)
{
    sort_envp(envp);
    while (*envp)
    {
        printf("declare -x %s\n", *envp);
        envp++;
    }
}
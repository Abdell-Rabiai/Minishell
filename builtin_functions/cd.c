/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:45:51 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/14 19:27:10 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    cd(char *path)
{
	if (chdir(path))
		ft_printf(2, "bash: cd: %s: No such file or directory\n", path);
}

void set_envp_value(char *old_variable, char *new_value, t_infos *infos)
{
	t_envp *temp;
	temp = infos->my_envp;
	while (temp)
	{
		if (!ft_strcmp(temp->variable_name, old_variable))
		{
			free(temp->variable_value);
			temp->variable_value = ft_strdup(new_value, 0);
			return ;
		}
		temp = temp->next;
	}
}

void update_old_pwd(t_infos *infos)
{
	char *tmp;
	tmp = get_envp_value("PWD", infos);
	set_envp_value("OLDPWD", tmp, infos);
}

void set_current_directory(t_infos *infos)
{
	char *tmp;
	tmp = getcwd(NULL, 0);
	set_envp_value("PWD", tmp, infos);
	free(tmp);
}

int print_old_pwd(t_infos *infos)
{
    char *old_pwd;

    old_pwd = get_envp_value("OLDPWD", infos);
	if (!ft_strcmp(old_pwd, ""))
    {
        ft_printf(2, "minishell: cd: OLDPWD not set\n");
        return (1);
    }
	cd(old_pwd);
	ft_printf(1, "%s\n", old_pwd);
	return (0);
}

void my_cd(char **strs, t_infos *infos)
{
	set_current_directory(infos);
	if (!strs[1])
		cd(get_envp_value("HOME", infos));
	if (!strs[1])
		return ;
	if (!ft_strcmp(strs[1], "-"))
	{
		if (print_old_pwd(infos))
			return ;
	}
	else if (!ft_strcmp(strs[1], "~"))
		cd(get_envp_value("HOME", infos));
	else if (strs[1][0] == '~')
	{
		char *tmp;
		tmp = ft_strjoin(get_envp_value("HOME", infos), strs[1] + 1, 0);
		cd(tmp);
		free(tmp);
	}
	else if (strs[1])
		cd(strs[1]);
	update_old_pwd(infos);
}

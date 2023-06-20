/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:45:51 by arabiai           #+#    #+#             */
/*   Updated: 2023/06/20 20:52:38 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_old_pwd(t_infos *infos)
{
	char	*tmp;

	tmp = get_envp_value("PWD", infos);
	set_envp_value("OLDPWD", tmp, infos);
}

void	set_current_directory(t_infos *infos, char *path)
{
	char	*tmp;
	char	*removed_pwd;
	char	*slash_path;
	char	*old_pwd;

	tmp = getcwd(NULL, 0);
	if (!tmp)
	{	
		slash_path = ft_strjoin("/", path, 0);
		old_pwd = get_envp_value("OLDPWD", infos);
		removed_pwd = ft_strjoin(old_pwd, slash_path, 2);
		set_envp_value("PWD", removed_pwd, infos);
		free(removed_pwd);
		if (!old_pwd)
			free(slash_path);
	}
	else
		set_envp_value("PWD", tmp, infos);
	free(tmp);
}

void	cd(char *path, t_infos *infos)
{
	char	*current_dir;

	update_old_pwd(infos);
	if (!path)
	{
		ft_printf(2, "minishell: cd: HOME not set\n");
		g_g.g_exit_status = EXIT_FAILURE;
		return ;
	}
	if (chdir(path))
	{
		ft_printf(2, "minishell: cd: %s: No such file or directory\n", path);
		g_g.g_exit_status = EXIT_FAILURE;
		return ;
	}
	set_current_directory(infos, path);
	current_dir = getcwd(NULL, 0);
	if (!current_dir)
	{
		ft_printf(2, "minishell: cd: error retrieving current directory:"
			" getcwd: cannot access parent directories:"
			" No such file or directory\n");
		g_g.g_exit_status = EXIT_FAILURE;
		return ;
	}
	free(current_dir);
	g_g.g_exit_status = EXIT_SUCCESS;
}

void	my_cd(char **strs, t_infos *infos)
{
	char	*tmp;

	if (!strs[1])
		cd(get_envp_value("HOME", infos), infos);
	if (!strs[1])
		return ;
	if (!ft_strcmp(strs[1], "-"))
	{
		if (print_old_pwd(infos))
			return ;
	}
	else if (!ft_strcmp(strs[1], "~"))
	{
		tmp = infos->tmp_home;
		if (get_envp_value("HOME", infos))
		{
			free(tmp);
			tmp = get_envp_value("HOME", infos);
		}
		printf("tmp = %s\n", tmp);
		cd(tmp, infos);
	}
	else if (strs[1][0] == '~')
	{
		if (get_envp_value("HOME", infos))
			tmp = ft_strjoin(get_envp_value("HOME", infos), strs[1] + 1, 0);
		tmp = ft_strjoin(infos->tmp_home, strs[1] + 1, 0);
		cd(tmp, infos);
		free(tmp);
	}
	else if (strs[1])
		cd(strs[1], infos);
}

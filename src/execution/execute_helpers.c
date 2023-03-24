/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 21:57:20 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/23 22:08:39 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_envpath(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

int check_paths_if_null(char **paths, char **main_cmd, char *cmd)
{
	if (paths == NULL)
	{
		ft_printf(2, "minishell: %s: No such file or directory\n", main_cmd[0]);
		free_all(main_cmd);
		free(cmd);
		if (paths)
			free_all(paths);
		return (1);
	}
	return (0);
}

int check_command_if_accessible(char *cmd, char **paths)
{
	if (access(cmd, F_OK | X_OK) == 0)
	{
		free(cmd);
		free_all(paths);
		return (1);
	}
	return (0);
}

char *return_command_if_found(char **paths, char **main_cmd, char *cmd)
{
	char	*str;
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		str = ft_strjoin(paths[i], cmd, 0);
		if (access(str, F_OK) == 0)
			break ;
		i++;
		free(str);
	}
	if (paths[i] == NULL)
    {
		if (!str)
			exit(EXIT_FAILURE);
        ft_printf(2, "minishell: %s: command not found\n", main_cmd[0]);
		return (free(cmd), free_all(main_cmd), free_all(paths), NULL);
    }
	else
        return (free(cmd), free_all(paths), str);
}

char	*get_command_path(char **paths, char **main_cmd)
{
	int		i;
	char	*cmd;
	char 	*str;

	i = 0;
	cmd = ft_strjoin("/", main_cmd[0], 0);
	if (check_paths_if_null(paths, main_cmd, cmd) == 1)
		return (NULL);
	if (check_command_if_accessible(main_cmd[0], paths) == 1)
        return (main_cmd[0]);

	str = return_command_if_found(paths, main_cmd, cmd);
	return (str);
}


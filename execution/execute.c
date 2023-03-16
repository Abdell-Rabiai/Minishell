/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:39:26 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/15 19:25:21 by arabiai          ###   ########.fr       */
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

char	*get_command_path(char **paths, char **main_cmd, pid_t pid)
{
	int		i;
	char	*str;
	char	*cmd;

	i = 0;
	cmd = ft_strjoin("/", main_cmd[0], 0);
	if (paths == NULL)
    {
        ft_printf(1, "ERROR : %s command not found : ", cmd);
		ft_printf(1, "All commands not available \n");
        free(cmd);
		free_all(paths);
		free_all(main_cmd);
        return (NULL);
    }
	if (access(main_cmd[0], F_OK | X_OK) == 0)
    {
        free(cmd);
        free_all(paths);
        return (main_cmd[0]);
    }
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
        ft_printf(1, "ERROR : %s command not found \n", cmd);
        free(cmd);
        close(pid);
		free_all(main_cmd);
		free_all(paths);
		return (NULL);
    }
	else
    {
        free(cmd);
        free_all(paths);
        return (str);
    }
}

void	child_process_for_one_cmd(char **strs, char **envp, pid_t pid)
{
	char	*path;
	char	**splited_paths;

	splited_paths = get_envpath(envp);
	path = get_command_path(splited_paths, strs, pid);
	execve(path, strs, envp);
	exit(EXIT_SUCCESS);
}

void execute_one_cmd(char **strs, char **envp)
{
	pid_t	pid;
	// pid_t	pid2;

	pid = fork();
	if (pid == 0)
		child_process_for_one_cmd(strs, envp, pid);
	// if (pid2 == 0)
	// 	child
	while (wait(NULL) != -1);
}
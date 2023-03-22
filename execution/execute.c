/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:39:26 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/22 12:13:57 by arabiai          ###   ########.fr       */
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

char	*get_command_path(char **paths, char **main_cmd)
{
	int		i;
	char	*str;
	char	*cmd;

	i = 0;
	cmd = ft_strjoin("/", main_cmd[0], 0);
	if (paths == NULL)
    {
        ft_printf(2, "minishell: %s: No such file or directory\n", main_cmd[0]);
        free(cmd);
		if (paths)
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
        ft_printf(2, "minishell: %s: command not found\n", main_cmd[0]);
        free(cmd);
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

void	child_process_for_one_cmd(t_list *final_list, char **envp, t_infos *infos)
{
	int 	fd_in;
	int		fd_out;
	char	*path;
	char	**splited_paths;
	char 	**strs;

	fd_in = final_list->in_fd;
	fd_out = final_list->out_fd;
	strs = final_list->commands;
	if (final_list->_errno != 0)
		ft_printf(2, "minishell: %s:\n", strerror(final_list->_errno));
	if (final_list->delims != NULL)
	{
		open_heredoc_file(final_list, infos);
		if (fd_in == -2)
			fd_in = open(get_last_heredoc_filename(final_list), O_RDONLY);
		if (!strs[0])
			exit(EXIT_SUCCESS);
	}
	if (fd_in != -2)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != -2)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (is_builtin(final_list) == 1)
	{
		execute_builtin(strs, infos);
		exit(EXIT_SUCCESS);
	}
    else
    {
	    splited_paths = get_envpath(envp);
	    path = get_command_path(splited_paths, strs);
		if (!path)
			exit(127);
        execve(path, strs, envp);
    }
	exit(EXIT_SUCCESS);
}

int is_builtin(t_list *node)
{
	if (!node->commands || !node->commands[0])
		return (0);
	if (ft_strcmp(node->commands[0], "echo") == 0)
		return (1);
	if (ft_strcmp(node->commands[0], "cd") == 0)
		return (1);
	if (ft_strcmp(node->commands[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(node->commands[0], "export") == 0)
		return (1);
	if (ft_strcmp(node->commands[0], "unset") == 0)
		return (1);
	if (ft_strcmp(node->commands[0], "env") == 0)
		return (1);
	if (ft_strcmp(node->commands[0], "exit") == 0)
		return (1);
	return (0);
}

void execute_builtin(char **strs, t_infos *infos)
{
	int i;
	
	i = 0;
	if (!strs || !strs[0])
	{
		free_all(strs);
		return ;
	}
	if (!ft_strcmp(strs[0], "echo"))
		my_echo(strs);
	else if (!ft_strcmp(strs[0], "cd"))
		my_cd(strs, infos);
	else if (!ft_strcmp(strs[0], "pwd"))
		my_pwd(infos);
	else if (!ft_strcmp(strs[0], "export"))
		my_export(strs, infos);
	else if (!ft_strcmp(strs[0], "unset"))
		my_unset(strs, infos);
	else if (!ft_strcmp(strs[0], "env"))
		my_env(infos);
	else if (!ft_strcmp(strs[0], "exit"))
		my_exit(strs, infos);
}

void execute_one_cmd(t_list *final_list, char **envp, t_infos *infos)
{
	pid_t	pid;
	
	if (is_builtin(final_list) == 1 && !final_list->delims)
		execute_builtin(final_list->commands, infos);
	else
	{
		pid = fork();
		if (pid == 0)
			child_process_for_one_cmd(final_list, envp, infos);
		waitpid(pid, &g_exit_status, 0);
		g_exit_status =  WEXITSTATUS(g_exit_status);
	}
}

void execute(t_list *final_list, t_infos *infos)
{
	char 	**envp;

	if (!final_list)
		return ;
	if (final_list->_errno != 0)
	{
		ft_printf(2, "minishell: %s:\n", strerror(final_list->_errno));
		return ;
	}
	infos->std_in = dup(STDIN_FILENO);
	infos->std_out = dup(STDOUT_FILENO);
	envp = copy_envp_into_array(infos);
	if (ft_lstsize(final_list) == 1)
		execute_one_cmd(final_list, envp, infos);
	else
	{
		handle_multiple_here_docs(final_list, infos);
		execute_multiple_cmds(final_list, envp, infos);
	}
	ft_free_envp_array(envp);
}
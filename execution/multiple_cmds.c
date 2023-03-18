/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:15:35 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/18 21:26:44 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process1(t_list *final_list, int pipe_ends[2], char **envp, pid_t pid, t_infos *infos)
{
	int		fd_in;
	char	*path;
	char	**strs;
	char	**splited_paths;

    fd_in = final_list->in_fd;
	strs = final_list->commands;
    if (final_list->_errno != 0)
	{
		close(pid);
		ft_printf(2, "minishell: %s:\n", strerror(final_list->_errno));
	}
	close(pipe_ends[0]);
	dup2(fd_in, STDIN_FILENO);
	dup2(pipe_ends[1], STDOUT_FILENO);
	close(fd_in);
    if (is_builtin(final_list) == 1)
        {
            printf("builtin\n");
            execute_builtin(strs, infos);
        }
    else
    {
	    splited_paths = get_envpath(envp);
	    path = get_command_path(splited_paths, strs);
        execve(path, strs, envp);
    }
	exit(EXIT_SUCCESS);
}

void	child_process2(t_list *final_list , int pipe_ends[2], char **envp, pid_t pid, t_infos *infos)
{
	char	*path;
	char	**strs;
	int		fd_out;
	char	**splited_paths;
    
    fd_out = final_list->out_fd;
	strs = final_list->commands;
    if (final_list->_errno != 0)
	{
		close(pid);
		ft_printf(2, "minishell: %s:\n", strerror(final_list->_errno));
	}
	close(pipe_ends[1]);
	dup2(fd_out, STDOUT_FILENO);
	dup2(pipe_ends[0], STDIN_FILENO);
	close(fd_out);
    if (is_builtin(final_list) == 1)
        execute_builtin(strs, infos);
    else
    {
	    splited_paths = get_envpath(envp);
	    path = get_command_path(splited_paths, strs);
    	execve(path, strs, envp);
    }
	exit(EXIT_SUCCESS);
}

// void execute_multiple_cmds(t_list *final_list, char **envp, t_infos *infos)
// {
//     pid_t	pid;
// 	pid_t	pid1;
//     t_list  *tmp;
// 	int		pipe_ends[2];

//     tmp = final_list;
// 	if (pipe(pipe_ends) == -1)
// 		perror("minishell : pipe :");
// 	pid = fork();
// 	if (pid == -1)
// 		perror("minishell : fork :");
// 	if (pid == 0)
//         child_process1(tmp, pipe_ends, envp, pid, infos);
//     tmp = tmp->next;
// 	pid1 = fork();
// 	if (pid1 == 0)
// 		child_process2(tmp, pipe_ends, envp, pid, infos);
// 	close(pipe_ends[1]);
// 	close(pipe_ends[0]);
// 	while (wait(NULL) != -1)
// 	{
// 	}  
// }

void	first_child_process(t_list *final_list, int pipe_ends[2], char **envp, pid_t pid, t_infos *infos)
{
	int		fd_in;
	char	*path;
	char	**strs;
	char	**splited_paths;

    fd_in = final_list->in_fd;
	strs = final_list->commands;
    if (final_list->_errno != 0)
	{
		close(pid);
		ft_printf(2, "minishell: %s:\n", strerror(final_list->_errno));
	}
	close(pipe_ends[0]);
	dup2(fd_in, STDIN_FILENO);
	dup2(pipe_ends[1], STDOUT_FILENO);
	close(fd_in);
    if (is_builtin(final_list) == 1)
        execute_builtin(strs, infos);
    else
    {
		printf("execve\n");
	    splited_paths = get_envpath(envp);
	    path = get_command_path(splited_paths, strs);
        execve(path, strs, envp);
    }
	exit(EXIT_SUCCESS);
}

void	last_child_process(t_list *final_list, char **envp, pid_t pid, t_infos *infos)
{
	char	*path;
	char	**strs;
	int		fd_out;
	char	**splited_paths;
    
    fd_out = final_list->out_fd;
	strs = final_list->commands;
    if (final_list->_errno != 0)
	{
		close(pid);
		ft_printf(2, "minishell: %s:\n", strerror(final_list->_errno));
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
    if (is_builtin(final_list) == 1)
        execute_builtin(strs, infos);
    else
    {
	    splited_paths = get_envpath(envp);
	    path = get_command_path(splited_paths, strs);
    	execve(path, strs, envp);
    }
	exit(EXIT_SUCCESS);
}

void	inter_process(t_list *final_list, int pipe_ends[2], char **envp, t_infos *infos)
{
	char	*path;
	char	**strs;
	char	**splited_paths;

	strs = final_list->commands;
	close(pipe_ends[0]);
	dup2(pipe_ends[1], STDOUT_FILENO);
    if (is_builtin(final_list) == 1)
        execute_builtin(strs, infos);
    else
    {
	    splited_paths = get_envpath(envp);
	    path = get_command_path(splited_paths, strs);
        execve(path, strs, envp);
    }
	exit(EXIT_SUCCESS);
}
void	redirect_process(int pipe_ends[2])
{
	close(pipe_ends[1]);
	dup2(pipe_ends[0], STDIN_FILENO);
	close(pipe_ends[0]);
}

void	closepipe_waitall(int pipe_ends[2], pid_t pid)
{
	if (pid != 0)
	{
		close(pipe_ends[1]);
		close(pipe_ends[0]);
		while (wait(NULL) != -1)
		{
		}
	}
}

void execute_multiple_cmds(t_list *final_list, char **envp, t_infos *infos)
{
    pid_t	pid;
    t_list  *tmp;
	int		pipe_ends[2];
    int i = 0;

    tmp = final_list;
    while (i < ft_lstsize(final_list))
	{
		if (pipe(pipe_ends) == -1)
			perror("minishell : pipe :");
		pid = fork();
		if (pid == -1)
			perror("minishell : fork :");
		else if (pid == 0)
		{
			if (i == 0)
				first_child_process(tmp, pipe_ends, envp, pid, infos);
			else if (i == ft_lstsize(final_list) - 1)
				last_child_process(tmp, envp, pid, infos);
			else
				inter_process(tmp, pipe_ends, envp, infos);
		}
		redirect_process(pipe_ends);
		tmp = tmp->next;
        i++;
	}
	while (wait(NULL) != -1)
	{
		
	}
}


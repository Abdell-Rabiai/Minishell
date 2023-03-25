/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:26:09 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/25 22:40:31 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_g	g_g;

char	*repalce_path_with_tilda(char *str)
{
	int		slashes;
	char	*tmp;

	slashes = 0;
	if (!str)
		return (NULL);
	tmp = str;
	while (*str)
	{
		if (*str == '/')
			slashes++;
		if (slashes == 3)
			break ;
		str++;
	}
	if (slashes == 3)
		str = ft_strjoin("~", str, 0);
	else if (slashes == 2)
		str = ft_strjoin("~", "", 0);
	else
		str = tmp;
	if (slashes == 3 || slashes == 2)
		free(tmp);
	return (str);
}

char	*prepare_path(t_infos *infos)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup(get_envp_value("PWD", infos), 0);
	cwd = repalce_path_with_tilda(cwd);
	tmp = ft_strjoin("\x1B[1;36m", cwd, 2);
	cwd = ft_strjoin(tmp, "$ \033[0m", 1);
	cwd = ft_strjoin(cwd, "\033[1;32mbash-9.2$ \033[0m", 1);
	if (!cwd)
		cwd = ft_strdup("\033[1;32mbash-9.2$ \033[0m", 0);
	return (cwd);
}

void	prompt(t_infos *infos)
{
	t_list	*final_list;
	char	*cwd;
	char	*str;

	while (1)
	{
		cwd = prepare_path(infos);
		str = readline(cwd);
		free(cwd);
		if (!str)
		{
			clear_history();
			ft_printf(1, "exit\n");
			exit(1);
		}
		final_list = pars_error(str, infos);
		execute(final_list, infos);
		add_history(str);
		free_final_list(final_list);
		free(str);
	}
}

void	execute_using_minishell(char *executable, t_infos *infos)
{
	char	**strs;
	char	**envp;

	executable = ft_strjoin("bash ", executable, 0);
	strs = ft_split(executable, ' ');
	free(executable);
	envp = copy_envp_into_array(infos);
	execve("/bin/bash", strs, envp);
	free_all(strs);
	exit(127);
}

void lek()
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **envp)
{
	t_infos	infos;

	signal(SIGINT, handle_kill);
	signal(SIGQUIT, SIG_IGN);
	initt(&infos);
	duplicate_envp(envp, &infos);
	update_shlvl_variable(&infos);
	if (ac >= 2)
		execute_using_minishell(av[1], &infos);
	prompt(&infos);
}

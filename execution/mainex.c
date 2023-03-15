/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:26:09 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/14 21:26:22 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void my_export(char **strs, t_infos *infos)
{
	int i;
	
	i = 1;
	if (!strs[i])
		export(infos);
	while (strs[i])
	{
		export_variable(infos, strs[i]);
		i++;
	}
}

void my_unset(char **strs, t_infos *infos)
{
	int i;
	
	i = 1;
	if (!strs[i])
		return ;
	while (strs[i])
	{
		unset_variable(strs[i], infos);
		i++;
	}
}

int get_envp_size(t_envp *envp)
{
	int i;
	t_envp *tmp;

	tmp = envp;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void print_envp_array(char **envp, t_infos *infos)
{
	int i;
	
	i = 0;
	while (i < get_envp_size(infos->my_envp))
	{
		ft_printf(1, "%s\n", envp[i]);
		i++;
	}
}

void my_execution(char **strs, t_infos *infos)
{
	char **envp;
	(void)strs;

	envp = copy_envp_into_array(infos);
	execute_one_cmd(strs, envp);
}

void builtin_handler(char *str, t_infos *infos)
{
	char **strs;
	int i;
	
	i = 0;
	strs = ft_split(str, ' ');
	if (!strs || !strs[0])
	{
		free_all(strs);
		return ;
	}
	if ( strs[0] && !ft_strcmp(strs[0], "echo"))
		my_echo(strs);
	else if (!ft_strcmp(strs[0], "cd"))
		my_cd(strs, infos);
	else if (!ft_strcmp(strs[0], "pwd"))
		my_pwd();
	else if (!ft_strcmp(strs[0], "export"))
		my_export(strs, infos);
	else if (!ft_strcmp(strs[0], "unset"))
		my_unset(strs, infos);
	else if (!ft_strcmp(strs[0], "env"))
		my_env(infos);
	else if (!ft_strcmp(strs[0], "exit"))
		my_exit(strs, infos);
	else
		my_execution(strs, infos);
	free_all(strs);
}

char **copy_envp_into_array(t_infos *infos)
{
	char **envp;
	t_envp *tmp;
	char *string;
	int i;
	int envp_size;
	
	i = 0;
	tmp = infos->my_envp;
	envp_size = get_envp_size(infos->my_envp);
	envp = malloc(sizeof(char *) * (envp_size + 1));
	while (i < envp_size)
	{
		string = ft_strjoin(tmp->variable_name, "=", 0);
		envp[i] = ft_strjoin(string, tmp->variable_value, 0);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

void	prompt(t_infos *infos)
{
	(void)infos;
	char	*str;

	signal(SIGINT, handle_kill);
	signal(SIGQUIT, handle_kill);
	while (1)
	{
		char *cwd;
		cwd = getcwd(NULL, 0);
		ft_printf(1, "\x1B[1;36m%s$\033[0m\n", cwd);
		free(cwd);
		str = readline("\033[1;32mminishell> \033[0m");
		if (!str)
		{
			clear_history();
			exit(1);
		}
		builtin_handler(str, infos);
		add_history(str);
		free(str);
		printf("\n");
	}
}

void koo(void)
{
	system("leaks minishell");
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	// atexit(koo);
	t_infos infos;
	init(&infos);
	duplicate_envp(envp, &infos);
	prompt(&infos);
}


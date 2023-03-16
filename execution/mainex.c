/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:26:09 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/16 22:54:46 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void update_shlvl_variable(t_infos *infos)
{
	t_envp *temp;
	int shlvl_old_variable_value;
	char *shlvl_new_variable_value;
	
	temp = infos->my_envp;
	while (temp)
	{
		if (!ft_strcmp(temp->variable_name, "SHLVL"))
		{
			shlvl_old_variable_value = ft_atoi(temp->variable_value);
			shlvl_old_variable_value++;
			shlvl_new_variable_value = ft_itoa(shlvl_old_variable_value);
			free(temp->variable_value);
			temp->variable_value = shlvl_new_variable_value;
			return ;
		}
		temp = temp->next;
	}
}

void my_execution(char **strs, t_infos *infos)
{
	char **envp;
	
	envp = copy_envp_into_array(infos);
	execute_one_cmd(strs, envp);
	ft_free_envp_array(envp);
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
		my_pwd(infos);
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
		if (!cwd)
			cwd = ft_strdup(get_envp_value("PWD", infos), 0);
		ft_printf(1, "\x1B[1;36m%s$ \033[0m", cwd);
		free(cwd);
		str = readline("\033[1;32mminihell> \033[0m");
		if (!str)
		{
			clear_history();
			exit(1);
		}
		builtin_handler(str, infos);
		add_history(str);
		free(str);
	}
}

void koo(void)
{
	system("leaks minishell");
}

void execute_using_minishell(char *executable, t_infos *infos)
{
	char **strs;
	executable= ft_strjoin("bash ", executable, 0);
	strs = ft_split(executable, ' ');
	my_execution(strs, infos);
	exit(EXIT_SUCCESS);
}

void print_env(char **envp)
{
	int i;
	
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

int main(int ac, char **av, char **envp)
{
	// atexit(koo);
	t_infos infos;
	init(&infos);
	duplicate_envp(envp, &infos);
	update_shlvl_variable(&infos);
	if (ac >= 2)
		execute_using_minishell(av[1], &infos);
	prompt(&infos);
}


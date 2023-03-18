/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:26:09 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/18 21:51:23 by arabiai          ###   ########.fr       */
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

void	prompt(t_infos *infos)
{
	(void)infos;
	t_list	*final_list;
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
		final_list = pars_error(str);
		// print_list(final_list, 1);
		execute(final_list, infos);
		add_history(str);
		free(str);
	}
}

void koo(void)
{
	system("leaks minishell");
}

// void execute_using_minishell(char *executable, t_infos *infos)
// {
// 	char **strs;
// 	executable	= ft_strjoin("bash ", executable, 0);
// 	strs = ft_split(executable, ' ');
// 	my_execution(strs, infos);
// 	exit(EXIT_SUCCESS);
// }

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
	(void)ac;
	(void)av;
	t_infos infos;
	init(&infos);
	duplicate_envp(envp, &infos);
	update_shlvl_variable(&infos);
	// if (ac >= 2)
	// 	execute_using_minishell(av[1], &infos);
	prompt(&infos);
}


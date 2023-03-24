/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:26:09 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/24 02:33:59 by arabiai          ###   ########.fr       */
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

char    *repalce_path_with_tilda(char *str)
{
    int        slashes;
    char    *tmp;

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

void    prompt(t_infos *infos)
{
    (void)infos;
    t_list    *final_list;
    char    *cwd;
    char    *tmp;
    char    *str;

    signal(SIGINT, handle_kill);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        cwd = getcwd(NULL, 0);
        if (!cwd)
            cwd = ft_strdup(get_envp_value("PWD", infos), 0);
        cwd = repalce_path_with_tilda(cwd);
        tmp = ft_strjoin("\x1B[1;36m", cwd, 2);
        cwd = ft_strjoin(tmp, "$ \033[0m", 1);
        cwd = ft_strjoin(cwd, "\033[1;32mbash-9.2$ \033[0m", 1);
		if (!cwd)
			cwd = ft_strdup("\033[1;32mbash-9.2$ \033[0m", 0);
        str = readline(cwd);
        free(cwd);
        if (!str)
        {
            clear_history();
            exit(1);
        }
        final_list = pars_error(str, infos);
        execute(final_list, infos);
        add_history(str);
        free_final_list(final_list);
        free(str);
    }
}

void execute_using_minishell(char *executable, t_infos *infos)
{
	char **strs;
    char **envp;

	executable = ft_strjoin("bash ", executable, 0);
	strs = ft_split(executable, ' ');
    free(executable);
    envp = copy_envp_into_array(infos);
    execve("/bin/bash", strs, envp);
    free_all(strs);
	exit(127);
}

int g_exit_status;

int main(int ac, char **av, char **envp)
{
	t_infos infos;

	initt(&infos);
	duplicate_envp(envp, &infos);
	update_shlvl_variable(&infos);
	if (ac >= 2)
		execute_using_minishell(av[1], &infos);
	prompt(&infos);
}


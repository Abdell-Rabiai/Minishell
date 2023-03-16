/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:34:06 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/16 23:06:11 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    my_pwd(t_infos *infos)
{
	char    str[256];

	if (!getcwd(str, sizeof(str)))
		ft_printf(1, "%s\n", get_envp_value("PWD", infos));
	else
		ft_printf(1, "%s\n", str);
}

void my_exit(char **strs, t_infos *infos)
{
	(void)infos;
	long long exit_status;
	if ((strs[1] && strs[2]))
	{
		ft_printf(1, "minishell: exit: too many arguments\n");
		return ;
	}
	if (strs[1])
	{
		exit_status = llabs(ft_atoi(strs[1]));
		printf("exit_status: %lld\n", exit_status);
		if (exit_status == 0)
			ft_printf(1, "exit\nminishell: exit: %s: numeric argument required\n", strs[1]);
		if (exit_status >= 255)
			exit_status = exit_status % 256;
	}
	else
		exit_status = EXIT_SUCCESS;
	ft_printf(1, "exit with status %d\n", exit_status);
	clear_history();
	exit(exit_status);	
}
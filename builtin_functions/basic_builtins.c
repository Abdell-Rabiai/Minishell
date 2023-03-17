/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:34:06 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/17 15:49:21 by arabiai          ###   ########.fr       */
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
	int i = 0;
	(void)(infos);
	long long exit_status;
	if ((strs[1] && strs[2]))
	{
		ft_printf(1, "minishell: exit: too many arguments\n");
		return ;
	}
	if (strs[1])
	{
		ft_printf(1, "exit\n");
		exit_status = ft_atoi_exit(strs[1], &i);
		if (exit_status == 0 || i == 1)
		{
			ft_printf(1, "minishell: exit: %s: numeric argument required\n", strs[1]);
			exit_status = 255;
		}
		if (exit_status >= 255 || exit_status < 0)
			exit_status = exit_status % 256;
		if (exit_status < 0)
			exit_status += 256;
	}
	else
		exit_status = EXIT_SUCCESS;
	ft_printf(1, "echo $? %d\n", exit_status);
	clear_history();
	exit(exit_status);	
}

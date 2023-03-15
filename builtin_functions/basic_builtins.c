/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:34:06 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/14 18:37:18 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    my_pwd(void)
{
	char    str[256];

	if (!getcwd(str, sizeof(str)))
		ft_printf(2, "Error printing current working directory!\n");
	else
		ft_printf(1, "%s\n", str);
}

void my_exit(char **strs, t_infos *infos)
{
	(void)infos;
	int exit_status;
	if (strs[1])
	{
		exit_status = ft_atoi(strs[1]);
		printf("exit {{ %d }}\n", exit_status);
		if (exit_status == 0)
			ft_printf(1, "exit\nminishell: exit: %s: numeric argument required\n", strs[1]);
		if (exit_status >= 256)
			exit_status = exit_status % 256;
	}
	else
		exit_status = EXIT_SUCCESS;
	ft_printf(1, "exit with status {%d}\n", exit_status);
	clear_history();
	exit(exit_status);	
}
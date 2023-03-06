/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:24:53 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/06 21:36:08 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_infos infos;
	init(&infos);
	duplicate_envp(envp, &infos);
	print_envp(&infos);
	// export(envp);
	// unset("PATH", envp);
	// printf("\n*--------------AFTER UNSET PATH-----------------*\n");
	// export(envp);
	// printf("\n*--------------AFTER ENV-----------------*\n");
	// env(envp);
}
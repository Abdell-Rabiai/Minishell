/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:24:53 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/07 17:29:21 by arabiai          ###   ########.fr       */
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
	// env(&infos);
	printf("\n*--------------EXPORT-----------------*\n");
	export(&infos);
	export_variable(&infos, "Tabi3a=Hello world a tabi3a you're so good at what you do");
	// export_variable(&infos, "Tabi3a=Hello world from 1337");
	export(&infos);
	// unset("PATH", envp);
	// printf("\n*--------------AFTER UNSET PATH-----------------*\n");
	// export(envp);
	// printf("\n*--------------AFTER ENV-----------------*\n");
	// env(envp);
}
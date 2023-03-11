/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:24:53 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/11 22:08:22 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void loo(void)
{
	system("leaks minishell");
}

char *get_envp_value(char *variable_name, t_infos *infos)
{
	t_envp *tmp;

	tmp = infos->my_envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->variable_name, variable_name) == 0)
				return (tmp->variable_value);
		tmp = tmp->next;
	}
	return (NULL);
}

int main(int ac, char **av, char **envp)
{
	// atexit(loo);
	(void)ac;
	(void)av;
	(void)envp;
	t_infos infos;
	init(&infos);
	duplicate_envp(envp, &infos);
	// export(&infos);
	// env(&infos);
	// export_variable(&infos, "=jgkldsngjlbdsjgbdsjgb,dmsbg,===");
	// export_variable(&infos, "l+=AI researcher");
	// export_variable(&infos, "Tabi3a======---##=something great");
	// export(&infos);
	// printf("thiers {%s}\n",getenv("Tabi3a"));
	// printf("mine {%s}\n",get_envp_value("Tabi3a", &infos));
	
	export_variable(&infos, "Aaaaaaa+=111111111");
	unset("Aaaaaaa", &infos);
	// export_variable(&infos, "Tabi3a^========= and now thats what im talkiing about ");
	export(&infos);
	// export_variable(&infos, "CTabi3a=3");
	// export_variable(&infos, "     zTabi3a=4");
	// export_variable(&infos, "Tabi3a=5");
	// export_variable(&infos, "Tabi3a=dfaa3 sdaar haz rass o fuck l3alaam tkoon m9iwaad");
	// export_variable(&infos, "Tabi3a=opps");
	// export_variable(&infos, "Tab");
	// export_variable(&infos, "Tab=12");
	// export_variable(&infos, "Black=1004");
	// export_variable(&infos, "Black+=/Security researcher");
	// export_variable(&infos, "*Black=");
	// export_variable(&infos, "");
	// printf("\n*--------------AFTER UNSET PATH-----------------*\n");
	// unset("Tabi3a", &infos);
	// unset("COLORTERM", &infos);
	// unset("BZaytona", &infos);
	// unset("Black", &infos);
	// unset("PATH", &infos);
	// unset("Apple_PubSub_Socket_Render", &infos);
	// unset("__CF_USER_TEXT_ENCODING", &infos);
	// unset("_P9K_TTY", &infos);
	// unset("ZSH", &infos);
	// printf("\n*--------------EXPORT-----------------*\n");
	// printf("\n*--------------ENV-----------------*\n");
	// export(&infos);
	// printf("\n*--------------AFTER ENV-----------------*\n");
	//env(&infos);
	// echo("ps\n", 0);
	// pwd();
	// cd("*");
	// pwd();
	ft_free_envp(&infos.my_envp);
	// while (1);
}

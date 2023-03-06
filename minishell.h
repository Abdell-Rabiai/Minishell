/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:18:23 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/06 21:45:45 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <ctype.h>
# include <readline/history.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct s_envp
{
	char			*variable_name;
	char 			*variable_value;
	struct s_envp	*next;
} t_envp;

typedef struct s_infos
{
	struct s_envp	*my_envp;
} t_infos;

void    prompt();

/*init*/
void init(t_infos *infos);
/*--------->builtins funtions <--------*/
void    echo(char *str, bool option);
void    pwd(void);
void    cd(char *path);
void    export(char **envp);
void    unset(char *str, char **envp);

/*--------->builtins utils funtions <--------*/
void 	sort_envp(char **envp);
void 	env(char **envp);
void 	duplicate_envp(char **envp, t_infos *infos);
void 	print_envp(t_infos *infos);
char 	*get_variable_name(char *string);
char 	*get_variable_value(char *string);
void	add_back_envp(t_envp **lst, t_envp *new);
t_envp	*new_node_envp(char *v_name, char *v_value);

#endif
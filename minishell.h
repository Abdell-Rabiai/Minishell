/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:18:23 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/21 16:23:58 by arabiai          ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/errno.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

typedef struct s_envp
{
	char			*variable_name;
	char 			*variable_value;
	struct s_envp	*next;
} t_envp;

typedef struct s_infos
{
	struct s_envp	*my_envp;
	int std_in;
	int std_out;
} t_infos;

extern int g_exit_status;

/*---------> initialize_data <--------*/
void initt(t_infos *infos);

/*---------> basic builtins funtions <--------*/
void    echo(char *str, bool option);
void    pwd(void);
void    cd(char *path, t_infos *infos);

/*---------> export <--------*/
void	my_export(char **strs, t_infos *infos);
void    export(t_infos *infos);
void	swap_envp_nodes(t_envp *tmp_envp, t_envp *tmp);
void	sort_envp(t_infos *infos);
void	export_variable(t_infos *infos, char *string);
void	add_variable(t_infos *infos, char *var_name, char *var_value);
int		check_variable_regex(char *str);
char 	*get_variable_value(char *string);
char	*get_variable_name(char *string);
t_envp	*new_node_envp(char *v_name, char *v_value);
void	add_back_envp(t_envp **head, t_envp *new);
void 	duplicate_envp(char **envp, t_infos *infos);
void	ft_free_envp(t_envp **head);

/*---------> unset <--------*/
void	my_unset(char **strs, t_infos *infos);
void	unset_variable(char *str, t_infos *infos);
int		delete_head_envp(t_infos *infos, char *str);
int		delete_node_envp(t_infos *infos, char *str);
int		delete_tail_envp(t_infos *infos, char *str);

/*---------> env <--------*/
void	my_env(t_infos *infos);
char 	*get_envp_value(char *variable_name, t_infos *infos);
void 	set_envp_value(char *old_variable, char *current_variable, t_infos *infos);
void	update_shlvl_variable(t_infos *infos);
void	add_ignored_env(t_infos *infos);

/*--------->builtins util funtions <--------*/
int		check_for_newline_option(char *str);
void	my_echo(char **strs);
void    my_pwd(t_infos *infos);
void	my_cd(char **strs, t_infos *infos);
void    cd(char *path, t_infos *infos);
void	my_exit(char **strs, t_infos *infos);

void	builtin_handler(t_list *final_list, t_infos *infos);

/*---------> execution <--------*/
void	my_execution(t_list *final_list, t_infos *infos);
// void	execute_using_minishell(t_list *final_list, char *executable, t_infos *infos);
char	**copy_envp_into_array(t_infos *infos);
void	print_envp_array(char **envp, t_infos *infos);
int		get_envp_size(t_envp *envp);
void	ft_free_envp_array(char **envp);

/*--------->execution preprocessig */
char	**get_envpath(char **envp);
char	*get_command_path(char **paths, char **main_cmd);
void	execute_one_cmd(t_list *final_list, char **envp, t_infos *infos);
void	child_process1(t_list *final_list, int pipe_ends[2], char **envp, pid_t pid, t_infos *infos);
void	child_process2(t_list *final_list , int pipe_ends[2], char **envp, pid_t pid, t_infos *infos);

void	execute_multiple_cmds(t_list *final_list, char **envp, t_infos *infos);
void	execute(t_list *final_list, t_infos *infos);
int		is_builtin(t_list *node);
void	execute_builtin(char **strs, t_infos *infos);






/**AHMAYMOU*/

typedef enum TYPE
{
	word,/*0*/
	trunc,/*1*/
	here_doc,/*2*/
	in_redir,/*3*/
	delimiter,/*4*/
	in_file,/*5*/
	append,/*6*/
	out_file,/*7*/
	Pipe,/*8*/
	_delimiter/*9*/
}			t_type;

void	free_final_list(t_list *final);
void	prompt(t_infos *infos);
t_list	*pars_error(char *str);
void	print_error(char c);
void	handle_kill(int sig);
bool	count_quotes(char *str);
int		end_word_index(char *str);
bool	is_spec(char str);
int		end_word_index(char *str);
void	add_or_join(t_list **head, char *temp, t_list **temp2, int *redir_c);
void	assign_type(t_list *command);
t_type	what_type(char *cmd);
int		check_pars_errors(t_list *command);
int		check_pars_syntax(char *str);
int		check_pars_erros2(t_list *temp, char *str);
void	expand_variables(t_list *head, int pos);
void	expand_multi_vars(t_list **head);
void	check_and_expand(t_list *tmp);
int		count_tokens(const char *str);
char	**split_string(const char *str, int in_quotes, int num_tokens);
char	*extract_token(const char *start, const char *str);
void	remove_quotes(char *str);
void	remove_quotes_node(t_list **temp);
t_list	*create_final_list(t_list **head);
void	free_node(t_list **node, int to_free);
void	print_list(t_list *list, bool flag);
int		open_fill(t_list **head, t_list **temp, int i);
int		open_out_file(t_list **head, t_list **temp, char *file_name);
int		open_files(t_list **head, t_list **temp);
int		count_delimiter(t_list *temp);
t_type	which_delimiter(char *str);
void	finish_node(t_list **final, t_list *temp, int i);
int		count_commands(t_list *temp);
int		fill_check_final(char *inpstr, t_list **final, t_list **command);

#endif

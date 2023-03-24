/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:18:23 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/24 20:36:35 by arabiai          ###   ########.fr       */
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

typedef struct s_help
{
	int		i;
	pid_t	pid;
	int		size;
	int		pipe_ends[2];
}	t_help;

typedef struct s_envp
{
	char			*variable_name;
	char			*variable_value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_infos
{
	struct s_envp	*my_envp;
	int				std_in;
	int				std_out;
	t_help			help;
	int				*pids;
}	t_infos;

typedef struct s_g
{
	int		g_exit_status;
	int		g_heredoc_cmd;
}	t_g;

t_g g_g;
/*---------> initialize_data <--------*/
void	initt(t_infos *infos);

/*---------> basic builtins funtions <--------*/
void	echo(char *str, bool option);
void	pwd(void);
void	cd(char *path, t_infos *infos);

/*---------> export <--------*/
void	my_export(char **strs, t_infos *infos);
void	export(t_infos *infos);
void	swap_envp_nodes(t_envp *tmp_envp, t_envp *tmp);
void	sort_envp(t_infos *infos);
void	export_variable(t_infos *infos, char *string);
void	add_variable(t_infos *infos, char *var_name, char *var_value,
			bool concatenate);
int		check_variable_regex(char *str);
char	*get_variable_value(char *string);
char	*get_variable_name(char *string);
t_envp	*new_node_envp(char *v_name, char *v_value);
void	add_back_envp(t_envp **head, t_envp *new);
void	duplicate_envp(char **envp, t_infos *infos);
void	ft_free_envp(t_envp **head);

/*---------> unset <--------*/
void	my_unset(char **strs, t_infos *infos);
void	unset_variable(char *str, t_infos *infos);
int		delete_head_envp(t_infos *infos, char *str);
int		delete_node_envp(t_infos *infos, char *str);
int		delete_tail_envp(t_infos *infos, char *str);

/*---------> env <--------*/
void	my_env(t_infos *infos);
char	*get_envp_value(char *variable_name, t_infos *infos);
void	set_envp_value(char *old_variable, char *current_variable,
			t_infos *infos);
void	update_shlvl_variable(t_infos *infos);
void	add_ignored_env(t_infos *infos);
char	*get_envp_value(char *variable_name, t_infos *infos);

/*--------->builtins util funtions <--------*/
int		check_for_newline_option(char *str);
void	my_echo(char **strs);
void	my_pwd(t_infos *infos);
void	my_cd(char **strs, t_infos *infos);
void	cd(char *path, t_infos *infos);
void	set_envp_value(char *old_variable, char *new_value, t_infos *infos);
int		print_old_pwd(t_infos *infos);
void	my_exit(char **strs);

void	builtin_handler(t_list *final_list, t_infos *infos);

/*---------> execution <--------*/
char	**copy_envp_into_array(t_infos *infos);
void	print_envp_array(char **envp, t_infos *infos);
int		get_envp_size(t_envp *envp);
void	ft_free_envp_array(char **envp);

/*--------->execution preprocessig */
char	**get_envpath(char **envp);
char	*get_command_path(char **paths, char **main_cmd);
void	execute_one_cmd(t_list *final_list, char **envp, t_infos *infos);
void	first_errno_and_open_heredocs(t_list *final_list, char **strs);
void	first_check_for_inout_output_files(t_list *final_list,
			int pipe_ends[2]);
void	last_check_for_input_output_files(t_list *final_list, t_infos *infos);
void	inter_check_for_input_output_files(t_list *final_list, t_infos *infos);
void	handle_execve_signal_errors(int status);

/**--------------->pipeline------------->*/
void	execute_multiple_cmds(t_list *final_list, char **envp, t_infos *infos);
void	execute(t_list *final_list, t_infos *infos);
void	check_for_inout_output_files(int fd_in, int fd_out);
char	*get_command_path(char **paths, char **main_cmd);
char	*return_command_if_found(char **paths, char **main_cmd, char *cmd);
int		check_command_if_accessible(char *cmd, char **paths);
int		check_paths_if_null(char **paths, char **main_cmd, char *cmd);
char	**get_envpath(char **envp);
int		is_builtin(t_list *node);
void	execute_builtin(char **strs, t_infos *infos);
void	redirect_process(int pipe_ends[2]);
void	create_pipe(int pipe_ends[2]);
pid_t	my_fork(t_infos *infos, int i);

/*------------> heredoc--------->*/
char	*get_last_heredoc_filename(t_list *final_list);
void	open_heredoc_file(t_list *final_list, t_infos *infos);
void	handle_multiple_here_docs(t_list *final_list, t_infos *infos);
void	open_heredoc_if_found(t_list *final_list, t_infos *infos, char **strs);
char	*check_and_expand_heredoc(char *str, t_infos *infos);
char	*expand_variables_heredoc(char *str, int pos, t_infos *infos);
void	handle_multiple_here_docs(t_list *final_list, t_infos *infos);
void	unlink_heredoc_files(t_list *final_list);
void	handle_signal(int signal);

typedef enum TYPE
{
	word,
	trunc,
	here_doc,
	in_redir,
	delimiter,
	in_file,
	append,
	tr_out_file,
	app_out_file,
	Pipe,
	_delimiter
}			t_type;

void	free_final_list(t_list *final);
void	prompt(t_infos *infos);
t_list	*pars_error(char *str, t_infos *infos);
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
void	expand_variables(t_list *head, int pos, t_infos *infos);
void	expand_multi_vars(t_list **head, t_infos *infos);
void	check_and_expand(t_list *tmp, t_infos *infos);
char	*get_variable(char *str, t_infos *infos);

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
int		fill_check_final(char *inpstr, t_list **final,
			t_list **command, t_infos *infos);

#endif

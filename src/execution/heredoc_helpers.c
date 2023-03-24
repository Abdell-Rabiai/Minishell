/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 22:09:38 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/24 21:13:50 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_multiple_here_docs(t_list *final_list, t_infos *infos)
{
	int		i;
	pid_t	pid;
	t_list	*current;

	g_g.g_heredoc_cmd = -2;
	current = final_list;
	i = -1;
	pid = fork();
	if (pid == 0)
	{
		while (current)
		{
			if (current->delims)
				open_heredoc_file(current, infos);
			current = current->next;
		}
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
}

char	*expand_variables_heredoc(char *str, int pos, t_infos *infos)
{
	char	*value;
	char	*tmp_str;
	int		i;

	i = pos;
	tmp_str = ft_substr((str), 0, i);
	value = get_variable((str) + i, infos);
	free(str);
	str = ft_strjoin(tmp_str, value, 1);
	free(value);
	return (str);
}

char	*check_and_expand_heredoc(char *str, t_infos *infos)
{
	int			i;
	static int	quote;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (quote == 0)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
		}
		if (str[i] == '$' && (!quote || quote == '\"')
			&& str[i + 1] && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?'))
		{
			str = expand_variables_heredoc(str, i, infos);
			i = -1;
			quote = 0;
		}
	}
	return (str);
}

char	*get_last_heredoc_filename(t_list *final_list)
{
	int		i;
	t_list	*current;

	current = final_list;
	if (!current)
		return (NULL);
	i = 0;
	while (current->delims[i].delimiter)
		i++;
	return (current->delims[i - 1].tmp_file);
}

void	unlink_heredoc_files(t_list *final_list)
{
	int		i;
	t_list	*current;

	current = final_list;
	i = 0;
	while (current)
	{
		if (!current->delims)
			return ;
		i = 0;
		while (current->delims[i].delimiter)
		{
			unlink(current->delims[i].tmp_file);
			i++;
		}
		current = current->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:13:54 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/24 23:05:58 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_variable(char *str, t_infos *infos)
{
	int		i;
	char	*var;
	char	*var2;
	char	*value;

	i = 0;
	if (ft_isdigit(str[1]) || str[1] == '?')
		var = ft_substr(str, 1, 1);
	else
	{
		while (str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
			i++;
		var = ft_substr(str, 1, i);
	}
	var2 = ft_substr(str, ft_strlen(var) + 1, ft_strlen(str) - ft_strlen(var));
	if (str[1] != '?')
		value = ft_strdup(get_envp_value(var, infos), 0);
	else
		value = ft_itoa(g_g.g_exit_status);
	if (!value)
		value = ft_strdup("", 0);
	value = ft_strjoin(value, var2, 1);
	return (free(var), free(var2), value);
}

void	expand_variables(t_list *tmp, int pos, t_infos *infos)
{
	char	*value;
	char	*tmp_str;
	int		i;

	i = pos;
	tmp_str = ft_substr((tmp->content), 0, i);
	value = get_variable((tmp->content) + i, infos);
	free(tmp->content);
	tmp->content = ft_strjoin(tmp_str, value, 1);
	free(value);
}

void	remove_spaces(char *str)
{
	int		i;
	int		j;
	char	*tmp;
	bool	quote;

	i = 0;
	j = 0;
	tmp = ft_strdup(str, 0);
	quote = false;
	while (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\t'))
		i++;
	while (tmp[i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
			quote = !quote;
		if ((tmp[i] == ' ' || tmp[i] == '\t') && tmp[i + 1] == ' ' && !quote)
			i++;
		else
			str[j++] = tmp[i++];
	}
	str[j] = '\0';
	free(tmp);
}

void	expand_multi_vars(t_list **head, t_infos *infos)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->prev && tmp->prev->type == here_doc)
			tmp = tmp->next;
		if (tmp)
		{
			check_and_expand(tmp, infos);
			remove_spaces(tmp->content);
			tmp = tmp->next;
		}
	}
}

void	check_and_expand(t_list *tmp, t_infos *infos)
{
	int			i;
	static int	quote;
	char		*str;

	i = -1;
	str = tmp->content;
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
			expand_variables(tmp, i, infos);
			str = tmp->content;
			i = -1;
			quote = 0;
		}
	}
}

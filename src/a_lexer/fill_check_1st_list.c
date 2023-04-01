/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_check_1st_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:33:22 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/04/01 21:38:34 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fill_list(char *inputString, t_list **head)
{
	char		*temp;
	int			end_word;
	int			red_c;
	t_list		*temp2;

	temp2 = NULL;
	red_c = 0;
	while (*inputString)
	{
		while (*inputString == ' ' || *inputString == '\t')
			inputString++;
		end_word = end_word_index(inputString);
		temp = ft_substr(inputString, 0, end_word);
		if (what_type(temp) == in_redir || what_type(temp) == trunc
			|| what_type(temp) == append)
			red_c++;
		add_or_join(head, temp, &temp2, &red_c);
		if (end_word == -1)
			return (free(temp), 0);
		free(temp);
		inputString += end_word;
	}
	return (0);
}

void	free2(t_list **final)
{
	int	i;

	i = -1;
	if ((*final)->delims)
	{
		while ((*final)->delims[++i].delimiter)
		{
			if ((*final)->delims[i].tmp_file)
				free((*final)->delims[i].tmp_file);
			free((*final)->delims[i].delimiter);
		}
		free((*final)->delims);
	}
	if ((*final)->in_file)
		free((*final)->in_file);
	if ((*final)->out_file)
		free((*final)->out_file);
	free((*final));
}

void	free_final_list(t_list *final)
{
	t_list	*temp;
	int		i;

	while (final)
	{
		i = -1;
		temp = final->next;
		free(final->content);
		while (final->commands[++i])
			free(final->commands[i]);
		if (final->commands)
			free(final->commands);
		free2(&final);
		final = temp;
	}
}

int	fill_check_final(char *inpstr, t_list **final,
		t_list **command, t_infos *infos)
{
	fill_list(inpstr, command);
	assign_type(*command);
	if (check_pars_errors(*command))
		return (free(inpstr), ft_lstclear(command), 1);
	expand_multi_vars(command, infos);
	*final = create_final_list(command);
	return (0);
}

t_list	*pars_error(char *str, t_infos *infos)
{
	t_list	*command;
	t_list	*final;
	char	*inpstr;

	command = NULL;
	inpstr = ft_strtrim(str, " ");
	if (!inpstr || !*inpstr)
		return (free(inpstr), NULL);
	if (*inpstr == '|' || *inpstr == ';')
		return (print_error(*inpstr), free(inpstr), NULL);
	else if (*(inpstr + ft_strlen(inpstr) - 1) == '|'
		|| *(inpstr + ft_strlen(inpstr) - 1) == ';'
		|| *(inpstr + ft_strlen(inpstr) - 1) == '>'
		|| *(inpstr + ft_strlen(inpstr) - 1) == '<')
		return (print_error('\n'), free(inpstr), free(str), NULL);
	if (!count_quotes(inpstr))
	{
		printf("minishell: syntax error, unclosed quotes\n");
		return (g_g.g_exit_status = 258, free(inpstr), free(str), NULL);
	}
	if (fill_check_final(inpstr, &final, &command, infos))
		return (NULL);
	return (free(inpstr), final);
}

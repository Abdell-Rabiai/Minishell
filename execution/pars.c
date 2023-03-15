/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:08:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/14 09:56:01 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*temp function */

void	print_list(t_list *list)
{
	t_list	*current;

	current = list;
	printf("After tokenisation: of str\n");
	while (current)
	{
		printf("{%s:%d}", (char *)current->content, current->type);
		if (current->next)
			printf("->");
		current = current->next;
	}
	printf("\n");
}

t_type	what_type(char *cmd)
{
	if (!ft_strncmp(cmd, "|", 1))
		return (Pipe);
	else if (!ft_strncmp(cmd, "<<", 2))
		return (here_doc);
	else if (!ft_strncmp(cmd, "<", 1))
		return (in_redir);
	else if (!ft_strncmp(cmd, ">>", 2))
		return (append);
	else if (!ft_strncmp(cmd, ">", 1))
		return (trunc);
	else
		return (word);
}

void	assign_type(t_list *command)
{
	char	*cmd;
	t_list	*temp;

	temp = command;
	while (temp)
	{
		cmd = (char *)temp->content;
		temp->type = what_type(cmd);
		if (temp->prev && temp->type == word && temp->prev->type == in_redir)
			temp->type = in_file;
		else if (temp->prev && temp->type == word && (temp->prev->type == trunc || temp->prev->type == append))
			temp->type = out_file;
		else if (temp->prev && temp->type == word && temp->prev->type == here_doc)
			temp->type = delimiter;
		temp = temp->next;
	}
}

int	fill_list(char *inputString, t_list **head)
{
    char	*temp;
    int		end_word;
	t_list	*temp2;

	temp2 = NULL;
    while (*inputString)
    {
        if (*inputString == ' ')
            while (*inputString == ' ')
                inputString++;
        else
        {
            end_word = end_word_index(inputString);
            temp = ft_substr(inputString, 0, end_word);
            if (end_word == -1)
                return (add_or_join(head, temp, &temp2), free(temp), 0);
			add_or_join(head, temp, &temp2);
            free(temp);
            inputString += end_word;
        }
    }
	return (0);
}

int	pars_error(char *str)
{
	t_list	*command;
	char	*inpStr;

	command = NULL;
	inpStr = ft_strtrim(str, " ");
	if (*inpStr == '|' || *inpStr == ';')
	{
		printf("minishell: syntax error near unexpected token `%c'\n", *(str));
		return (free(inpStr), 1);
	}
	else if (*(inpStr + ft_strlen(inpStr) - 1) == '|' || *(inpStr + ft_strlen(inpStr) - 1) == ';'
		|| *(inpStr + ft_strlen(inpStr) - 1) == '>' || *(inpStr + ft_strlen(inpStr) - 1) == '<')
	{
		printf("minishell: syntax error near unexpected token `\\n'\n");
		return (free(inpStr), 1);
	}
	if (!count_quotes(str))
	{
		printf("minishell: syntax error, unclosed quotes\n");
		return (free(inpStr), 1);
	}
	fill_list(inpStr, &command);
	assign_type(command);
	print_list(command);
	if (check_pars_errors(command))
		return (free(inpStr), ft_lstclear(&command), 1);
	return (free(inpStr), ft_lstclear(&command), 0);
}


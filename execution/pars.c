/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:08:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/18 22:17:35 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*temp function */

void    print_list(t_list *list, bool flag)
{
    t_list    *current;

    current = list;
    int i = -1;
    printf("After tokenisation: of str\n");
    while (current)
    {
        i = -1;
        printf("*-------------------------------*\n");
        printf("{content:%s}\n", current->content);
        printf("{type:%d}\n", current->type);
        printf("{in_fd:%d}\n", current->in_fd);
        printf("{out_fd:%d}\n", current->out_fd);
        printf("{in_file:%s}\n", current->in_file);
        printf("{out_file:%s}\n", current->out_file);
        printf("{_errno:%d / %s}\n", current->_errno, strerror(current->_errno));
        printf("{delims:%p}\n", current->delims);
        if (flag)
        {
            if (current->delims)
                while (current->delims[++i].delimiter)
                    printf("(delim :%d: %s)\n", i, current->delims[i].delimiter);
            
        }
        //print char **commands in list
        if (current->commands)
        {
            int j = -1;
            while (current->commands[++j])
                printf("commands[%d] = [%s]\n", j, current->commands[j]);
        }
        if (current->next)
            printf("->");
        current = current->next;
    }
}

t_type	what_type(char *cmd)
{
	if (!ft_strncmp(cmd, "|", 1))
		return (Pipe);
	else if (ft_strlen(cmd) > 1 && !ft_strncmp(cmd, "<<", 2))
		return (here_doc);
	else if (ft_strlen(cmd) > 1 && !ft_strncmp(cmd, ">>", 2))
		return (append);
	else if (!ft_strncmp(cmd, "<", 1))
		return (in_redir);
	else if (!ft_strncmp(cmd, ">", 1))
		return (trunc);
	return (word);
}

void	assign_type(t_list *command)
{
	char	*cmd;
	t_list	*temp;

	temp = command;
	while (temp)
	{
		cmd = temp->content;
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

void remove_instant_quotes(char* str)
{
    int		i;
	bool	quote;
	int		j;

	i = 0;
	j = 0;
	quote = false;
    while (str[i])
	{
        if ((str[i] == '"' || str[i] == '\'') && !quote
			&& str[i + 1] && str[i + 1] == str[i])
            i += 2;
		else if ((str[i] == '"' || str[i] == '\'')
			&& str[i + 1] && str[i + 1] != str[i])
			{
				str[j++] = str[i++];
				quote = !quote;
			}
		else
        	str[j++] = str[i++];
    }
    str[j] = '\0';
}

int	fill_list(char *inputString, t_list **head)
{
    char		*temp;
    int			end_word;
	int			red_c;
	t_list		*temp2;

	temp2 = NULL;
	red_c = 0;
	remove_instant_quotes(inputString);
    while (*inputString)
    {
        if (*inputString == ' ')
            while (*inputString == ' ')
                inputString++;
        else
        {
            end_word = end_word_index(inputString);
            temp = ft_substr(inputString, 0, end_word);
			if (what_type(temp) == in_redir || what_type(temp) == trunc
				|| what_type(temp) == append)
				red_c++;
			add_or_join(head, temp, &temp2, &red_c);
            if (end_word == -1)
                return (free(temp), expand_multi_vars(head), 0);
            free(temp);
            inputString += end_word;
        }
    }
	return (expand_multi_vars(head), 0);
}

// int	check_string(char *inpStr)
// {
// 	while (*inpStr)
// 	{
// 		if (*inpStr == '>' && *(inpStr + 1) == '|')
// 			return (print_error(*(inpStr + 1)), 1);
// 		inpStr++;
// 	}
// 	return (0);
// }

// int	pars_error(char *str)
// {
// 	t_list	*command;
// 	char	*inpStr;

// 	command = NULL;
// 	inpStr = ft_strtrim(str, " ");
// 	if (!inpStr || !*inpStr)
// 		return (free(inpStr), 0);
// 	if (*inpStr == '|' || *inpStr == ';')
// 	{
// 		printf("minishell: syntax error near unexpected token `%c'\n", *(inpStr));
// 		return (free(inpStr), 1);
// 	}
// 	else if (*(inpStr + ft_strlen(inpStr) - 1) == '|' || *(inpStr + ft_strlen(inpStr) - 1) == ';'
// 		|| *(inpStr + ft_strlen(inpStr) - 1) == '>' || *(inpStr + ft_strlen(inpStr) - 1) == '<')
// 	{
// 		printf("minishell: syntax error near unexpected token `\\n'\n");
// 		return (free(inpStr), 1);
// 	}
// 	// else if (check_string(inpStr))
// 	// 	return (free(inpStr), 1);
// 	if (!count_quotes(inpStr))
// 	{
// 		printf("minishell: syntax error, unclosed quotes\n");
// 		return (free(inpStr), 1);
// 	}
// 	printf("str: %s\n", inpStr);
// 	fill_list(inpStr, &command);
// 	assign_type(command);
// 	print_list(command, 0);
// 	if (check_pars_errors(command))
// 		return (free(inpStr), ft_lstclear(&command), 1);
// 	t_list	*final;
// 	final = create_final_list(&command);
// 	print_list(final, 1);
// 	return (free(inpStr), ft_lstclear(&command),ft_lstclear(&final), 0);
// }

t_list	*pars_error(char *str)
{
	t_list	*command;
	char	*inpStr;

	command = NULL;
	inpStr = ft_strtrim(str, " ");
	if (!inpStr || !*inpStr)
		return (free(inpStr), NULL);
	if (*inpStr == '|' || *inpStr == ';')
	{
		printf("minishell: syntax error near unexpected token `%c'\n", *(inpStr));
		return (free(inpStr), NULL);
	}
	else if (*(inpStr + ft_strlen(inpStr) - 1) == '|' || *(inpStr + ft_strlen(inpStr) - 1) == ';'
		|| *(inpStr + ft_strlen(inpStr) - 1) == '>' || *(inpStr + ft_strlen(inpStr) - 1) == '<')
	{
		printf("minishell: syntax error near unexpected token `\\n'\n");
		return (free(inpStr), NULL);
	}
	if (!count_quotes(inpStr))
	{
		printf("minishell: syntax error, unclosed quotes\n");
		return (free(inpStr), NULL);
	}
	fill_list(inpStr, &command);
	assign_type(command);
	
	if (check_pars_errors(command))
		return (free(inpStr), ft_lstclear(&command), NULL);
	t_list	*final;
	final = create_final_list(&command);
	
	return (free(inpStr), ft_lstclear(&command),final);
}


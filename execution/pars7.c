/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:35:01 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/21 16:16:54 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_delimiter(t_list *temp)
{
	int	count;

	count = 0;
	while (temp && temp->type != Pipe)
	{
		if (temp->type == delimiter)
			count++;
		temp = temp->next;
	}
	return (count + 1);
}

int	random_num_gen(void)
{
	int	fd;
	int	num;

	fd = open("/dev/random", O_RDONLY);
	read(fd, &num, sizeof(int));
	close(fd);
	return (num);
}

char	*tmp_here_doc_file_gen(void)
{
	char		*tmp;
	char		*tmp2;
	char		*tmp3;

	tmp = ft_itoa(random_num_gen());
	tmp2 = ft_strjoin("/tmp/minishell_", tmp, 0);
	tmp3 = ft_strjoin(tmp2, ".tmp", 0);
	free(tmp);
	free(tmp2);
	return (tmp3);
}

int	open_fill(t_list **head, t_list **temp, int i)
{
	if ((*head)->type == in_file || (*head)->type == out_file)
		open_files(head, temp);
	else if ((*head)->type == delimiter)
	{
		(*temp)->delims[++i].type = which_delimiter((*head)->content);
		(*temp)->delims[i].delimiter = (*head)->content;
		(*temp)->delims[i].tmp_file = tmp_here_doc_file_gen();
		if ((*temp)->in_fd != -2 && !(*temp)->_errno)
		{
			close((*temp)->in_fd);
			(*temp)->in_fd = -2;
		}
	}
	if (*head)
		free_node(head, ((*head)->type != delimiter
				&& (*head)->type != in_file && (*head)->type != out_file));
	(*temp)->type = word;
	return (i);
}

void	remove_quotes(char *str)
{
	int	i;
	int	j;
	int	quote;

	i = -1;
	j = 0;
	quote = 0;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (quote == 0)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
			else
				str[j++] = str[i];
		}
		else
			str[j++] = str[i];
	}
	str[j] = '\0';
}

void	finish_node(t_list **final, t_list *temp, int i)
{
	if (i == -1)
	{
		free(temp->delims);
		temp->delims = NULL;
	}
	else
		temp->delims[++i].delimiter = NULL;
	remove_quotes_node(&temp);
	ft_lstadd_back(final, temp);
}

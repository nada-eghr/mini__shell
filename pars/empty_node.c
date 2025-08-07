/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:48:02 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/05 16:56:19 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_empty_node(t_second_token **head, t_second_token *nodeToDelete)
{
	t_second_token	*current;

	if (*head == NULL || nodeToDelete == NULL)
		return ;
	if (*head == nodeToDelete)
	{
		*head = (*head)->next;
		free(nodeToDelete->token);
		free(nodeToDelete);
		return ;
	}
	current = *head;
	while (current && current->next != nodeToDelete)
		current = current->next;
	if (current && current->next == nodeToDelete)
	{
		current->next = nodeToDelete->next;
		free(nodeToDelete->token);
		free(nodeToDelete);
	}
}

void	remove_empty_node(t_second_token **second_tokens)
{
	t_second_token	**curr;
	t_second_token	*next;

	curr = second_tokens;
	while (*curr)
	{
		if (str_cmp((*curr)->token, ""))
		{
			next = (*curr)->next;
			delete_empty_node(second_tokens, *curr);
			*curr = next;
		}
		else
			curr = &(*curr)->next;
	}
}

bool	is_line_empty(const char *line)
{
	int	i;

	if (!line)
		return (true);
	i = 0;
	while (line[i])
	{
		if (!ft_space(line[i]))
			return (false);
		i++;
	}
	return (true);
}

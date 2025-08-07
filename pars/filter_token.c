/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:15:41 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/06 17:53:47 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_specific_node(t_token **head, t_token *nodeToDelete)
{
	t_token	*current;
	t_token	*temp;

	if (*head == NULL || nodeToDelete == NULL)
		return ;
	if (*head == nodeToDelete)
	{
		temp = *head;
		*head = temp->next;
		free(temp->token);
		free(temp);
		return ;
	}
	current = *head;
	while (current != NULL && current->next != nodeToDelete)
		current = current->next;
	if (current != NULL)
	{
		temp = current->next;
		current->next = temp->next;
		free(temp->token);
		free(temp);
	}
}

t_token	*convert_to_token(t_token *token)
{
	t_token	*current;
	t_token	*prev;

	current = token;
	prev = NULL;
	while (current)
	{
		if (current->type == T_SPACE)
		{
			if (prev == NULL)
				token = current->next;
			else
				prev->next = current->next;
			delete_specific_node(&token, current);
			current = current->next;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	return (token);
}

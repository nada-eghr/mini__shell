/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listUtils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:00:43 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/04 15:21:49 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*creattoken(char *data)
{
	t_token	*newnode;

	newnode = (t_token *)malloc(sizeof(t_token));
	if (!newnode)
		return (NULL);
	newnode->token = ft_strdup(data);
	newnode->type = get_token_type(data);
	newnode->next = NULL;
	newnode->prev = NULL;
	return (newnode);
}

void	add_back(t_token **head, t_token *node)
{
	t_token	*tmp;

	if (!node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->prev = tmp;
	node->next = NULL;
}

void	printlinkedlist(t_token *head)
{
	t_token	*current;

	current = head;
	while (current != NULL)
	{
		printf(" %s -> ", current->token);
		current = current->next;
	}
	printf("NULL\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:48:36 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/28 16:10:17 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_second_token	*creat_second_token(char *data, t_token_type type)
{
	t_second_token	*newnode;

	newnode = (t_second_token *)malloc(sizeof(t_second_token));
	if (!newnode)
		return (NULL);
	newnode->token = ft_strdup(data);
	newnode->type = type;
	newnode->next = NULL;
	return (newnode);
}

void	add_b(t_second_token **head, t_second_token *node)
{
	t_second_token	*tmp;

	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->next = NULL;
}

void	printlinkedlist1(t_second_token *head)
{
	t_second_token	*current;

	current = head;
	while (current != NULL)
	{
		printf(" %s -> ", current->token);
		current = current->next;
	}
	printf("NULL\n");
}

void	free_list1(t_second_token *head)
{
	t_second_token	*current;
	t_second_token	*next_node;

	current = head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->token);
		free(current);
		current = next_node;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:54:08 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/04 13:23:28 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check(t_second_token *token)
{
	t_second_token	*tmp;
	t_second_token	*prev;
	int				herdoc;

	herdoc = 0;
	tmp = token;
	prev = tmp;
	tmp = tmp->next;
	while (tmp && tmp->type != T_PIPE)
	{
		if ((prev->type == T_HEREDOC) && (tmp->type == T_WORD
				|| tmp->type == T_D_QUOTE || tmp->type == T_S_QUOTE
				|| tmp->type == T_ENV))
			herdoc = 1;
		prev = tmp;
		tmp = tmp->next;
	}
	return (herdoc);
}

t_cmd	*creat_cmd(t_second_token *list)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->arg = get_args(list);
	cmd->redi = get_files(list);
	cmd->herdoc = check(list);
	cmd->next = NULL;
	return (cmd);
}

void	add_back_cmd(t_cmd **head, t_cmd *node)
{
	t_cmd	*tmp;

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

t_cmd	*list_cmd(t_second_token *tokens)
{
	t_cmd			*node_cmd;
	t_cmd			*head;
	t_second_token	*curr;
	t_second_token	*prev;

	if (!tokens)
		return (NULL);
	node_cmd = NULL;
	head = NULL;
	curr = tokens;
	node_cmd = creat_cmd(curr);
	add_back_cmd(&head, node_cmd);
	prev = curr;
	curr = curr->next;
	while (curr)
	{
		if (prev->type == T_PIPE)
		{
			node_cmd = creat_cmd(curr);
			add_back_cmd(&head, node_cmd);
		}
		prev = curr;
		curr = curr->next;
	}
	return (head);
}

void	print_cmd(t_cmd *node_cmd)
{
	int	i;
	int	j;

	j = 0;
	while (node_cmd)
	{
		i = 0;
		printf("command [%d] -->", j);
		while (node_cmd->arg[i])
		{
			printf(" [ %s ] ", node_cmd->arg[i++]);
		}
		printf("\n");
		while (node_cmd->redi)
		{
			printf("type : [ %d ] <-------> file : [ %s ]  ,------> is %d\n",
				node_cmd->redi->type, node_cmd->redi->file,
				node_cmd->redi->her_doc);
			node_cmd->redi = node_cmd->redi->next;
		}
		node_cmd = node_cmd->next;
		j++;
	}
}

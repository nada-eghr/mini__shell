/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:53:35 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/05 17:38:05 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_token *head)
{
	t_token	*current;
	t_token	*next_node;

	current = head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->token);
		free(current);
		current = next_node;
	}
}
void	free_second_tokens(t_second_token **head)
{
	t_second_token *tmp;

	while (*head)
	{
		tmp = (*head)->next;
		if ((*head)->token)
			free((*head)->token);
		free(*head);
		*head = tmp;
	}
	*head = NULL;
}

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_redirections(t_redirection *redi)
{
	t_redirection	*tmp;

	while (redi)
	{
		tmp = redi->next;
		if (redi->file)
			free(redi->file);
		free(redi);
		redi = tmp;
	}
}

void	free_cmd_list(t_vmin *v)
{
	t_cmd	*tmp;

	while (v->cmd)
	{
		tmp = v->cmd->next;
		if (v->cmd->arg)
			free_str_array(v->cmd->arg);
		if (v->cmd->redi)
			free_redirections(v->cmd->redi);
		free(v->cmd);
		v->cmd= tmp;
	}
	v->filter_lst = NULL;
}

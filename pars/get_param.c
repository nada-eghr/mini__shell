/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:56:54 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/12 17:10:27 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(t_second_token *list)
{
	int				count;
	t_second_token	*tmp;
	t_second_token	*prev;

	count = 0;
	tmp = list;
	if (tmp->type == T_WORD || tmp->type == T_S_QUOTE || tmp->type == T_D_QUOTE
		|| tmp->type == T_ENV)
		count++;
	prev = tmp;
	tmp = tmp->next;
	while (tmp && tmp->type != T_PIPE)
	{
		if ((prev->type == T_PIPE || prev->type == T_WORD
				|| prev->type == T_S_QUOTE || prev->type == T_D_QUOTE
				|| prev->type == T_ENV) && (tmp->type == T_WORD
				|| tmp->type == T_D_QUOTE || tmp->type == T_S_QUOTE
				|| tmp->type == T_ENV))
			count++;
		prev = tmp;
		tmp = tmp->next;
	}
	return (count);
}

static int	is_arg_token(t_second_token *t)
{
	return (t && (t->type == T_WORD || t->type == T_S_QUOTE
			|| t->type == T_D_QUOTE || t->type == T_ENV));
}

char	**get_args(t_second_token *token)
{
	char			**cmd;
	int				i;
	t_second_token	*tmp;

	if (!token)
		return (NULL);
	cmd = malloc(sizeof(char *) * (count_args(token) + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	tmp = token;
	if (is_arg_token(tmp))
		cmd[i++] = ft_strdup(tmp->token);
	while (tmp && tmp->next && tmp->next->type != T_PIPE)
	{
		if (is_arg_token(tmp) && is_arg_token(tmp->next))
			cmd[i++] = ft_strdup(tmp->next->token);
		tmp = tmp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

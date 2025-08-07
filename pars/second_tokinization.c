/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_tokinization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:33:36 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/01 13:38:11 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_second_token	*merge_word_tokens(t_token **tmp)
{
	char			*str;
	t_second_token	*new_node;
	char			*tmp_join;
	t_token_type	sav_tp;

	str = ft_strdup("");
	while (*tmp && ((*tmp)->type == T_WORD || (*tmp)->type == T_ENV
			|| (*tmp)->type == T_S_QUOTE || (*tmp)->type == T_D_QUOTE))
	{
		tmp_join = str;
		str = ft_strjoin(str, (*tmp)->token);
		sav_tp = (*tmp)->type;
		free(tmp_join);
		*tmp = (*tmp)->next;
	}
	new_node = creat_second_token(str, sav_tp);
	free(str);
	return (new_node);
}

t_second_token	*handle_operator_token(t_token **tmp)
{
	t_second_token	*new_node;

	new_node = creat_second_token((*tmp)->token, (*tmp)->type);
	*tmp = (*tmp)->next;
	return (new_node);
}

t_second_token	*second_tokinization(t_token *token)
{
	t_second_token	*head;
	t_second_token	*new_node;
	t_token			*tmp;

	head = NULL;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == T_WORD || tmp->type == T_ENV || tmp->type == T_S_QUOTE
			|| tmp->type == T_D_QUOTE)
			new_node = merge_word_tokens(&tmp);
		else if (tmp->type == T_PIPE || tmp->type == T_RED_IN
			|| tmp->type == T_RED_OUT || tmp->type == T_APPEND
			|| tmp->type == T_HEREDOC)
			new_node = handle_operator_token(&tmp);
		else
		{
			tmp = tmp->next;
			continue ;
		}
		add_b(&head, new_node);
	}
	return (head);
}

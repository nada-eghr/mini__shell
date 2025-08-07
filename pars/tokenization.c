/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:57:56 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/05 16:56:19 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token_type	get_token_type(char *token)
{
	int	len;

	if (!token || str_cmp(token, " "))
		return (T_UNKNOWN);
	len = ft_strlen(token);
	if (str_cmp(token, " ") )
		return (T_SPACE);
	if (str_cmp(token, "|"))
		return (T_PIPE);
	if (str_cmp(token, "<"))
		return (T_RED_IN);
	if (str_cmp(token, ">"))
		return (T_RED_OUT);
	if (str_cmp(token, ">>"))
		return (T_APPEND);
	if (str_cmp(token, "<<"))
		return (T_HEREDOC);
	if (token[0] == '"' && token[len - 1] == '"')
		return (T_D_QUOTE);
	if (token[0] == '\'' && token[len - 1] == '\'')
		return (T_S_QUOTE);
	if (token[0] == '$' && len > 1 && (ft_isalpha(token[1]) || token[1] == '_'
			|| token[1] == '?'))
		return (T_ENV);
	return (T_WORD);
}

t_token	*convert_to_node(char *data)
{
	int		i;
	t_token	*head;
	t_token	*token;

	i = 0;
	head = NULL;
	token = NULL;
	while (data[i])
	{
		if (ft_space(data[i]))
			token = handle_spaces(data, &i);
		else if (data[i] == '>' || data[i] == '<' || data[i] == '|')
			token = parse_operator_token(data, &i);
		else if (data[i] == '\'' || data[i] == '"')
		{
			token = handle_quotes(data, &i);
			if (!token)
				return (free_list(head), NULL);
		}
		else
			token = parse_word_token(data, &i);
		if (token)
			add_back(&head, token);
	}
	return (head);
}

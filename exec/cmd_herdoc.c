/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_herdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:20:17 by slamhaou          #+#    #+#             */
/*   Updated: 2025/08/06 14:59:58 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_heredoc(t_cmd *list, int n)
{
	t_redirection	*red;
	int				count;

	count = 0;
	red = list->redi;
	if (n == HERDC_IN_LIST)
	{
		while (list)
		{
			if (list->herdoc)
				count++;
			list = list->next;
		}
	}
	if (n == HERDC_IN_CMD)
	{
		while (red)
		{
			if (red->type == T_HEREDOC)
				count++;
			red = red->next;
		}
	}
	return (count);
}

void	type_of_red_is_heredoc(t_redirection *red, t_var *var,
	t_env_list *env, int fd)
{
	char	*input;

	while (red->type == T_HEREDOC)
	{
		write(1, "> ", 2);
		input = get_next_line(0);
		if (!input || serch_del(input, red->file))
		{
			if (input)
				free(input);
			if (!input)
				var->exit_stat = 0;
			break ;
		}
		if (var->len_hrd == 0)
		{
			if (serch(input, '$') && red->her_doc == 0)
				input = expand_herdoc(input, env);
			write(fd, input, ft_strlen(input));
		}
		free(input);
	}
}

void	child_heredoc(int *herdoc, t_redirection *red
	, t_var *var, t_env_list *env)
{
	int	len;

	signal(SIGINT, handler_sig_herd);
	close (herdoc[0]);
	len = var->len_hrd;
	while (var->len_hrd > 0)
	{
		if (red->type == T_HEREDOC)
			var->len_hrd--;
		type_of_red_is_heredoc(red, var, env, herdoc[1]);
		red = red->next;
	}
	var->len_hrd = len;
	exit (0);
}

void	creat_child_herdoc(t_cmd *list, t_var *var, t_env_list *env)
{
	int	id;
	int	herdoc[2];

	var->len_hrd = len_heredoc(list, HERDC_IN_CMD);
	if (pipe(herdoc))
	{
		write_err("Minishell: ", "pipe error: ", "p");
		var->exit_stat = 1;
		return ;
	}
	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id < 0)
	{
		write_err("Minishell: ", "fork: ", "p");
		var->exit_stat = 1;
		return ;
	}
	if (id == 0)
		child_heredoc(herdoc, list->redi, var, env);
	wait_heredoc(herdoc, var, id);
	signal (SIGINT, handler);
}

int	*open_all_heredoc(t_cmd *list, t_var *var, t_env_list *env)
{
	int	i;
	int	*arr_fd_herdoc;
	int	len_cmd_her;

	i = 0;
	len_cmd_her = len_heredoc(list, HERDC_IN_LIST);
	var->len_hrd = len_cmd_her;
	if (len_cmd_her == 0)
		return (NULL);
	arr_fd_herdoc = malloc(sizeof(int) * len_cmd_her);
	if (!arr_fd_herdoc)
		return (NULL);
	while (list)
	{
		if (list->herdoc)
		{
			creat_child_herdoc(list, var, env);
			arr_fd_herdoc[i++] = var->last_in;
		}
		list = list->next;
	}
	return (arr_fd_herdoc);
}

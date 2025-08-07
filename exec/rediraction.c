/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:27:05 by slamhaou          #+#    #+#             */
/*   Updated: 2025/08/06 14:08:19 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_err(char *s, char *arg, char *last)
{
	if (s)
		write(2, s, ft_strlen(s));
	if (arg)
		write(2, arg, ft_strlen(arg));
	if (last[0] != 'p' && last[1])
		write(2, last, ft_strlen(last));
	if (last[0] == 'p' && !last[1])
	{
		write(2, ": ", 2);
		perror(NULL);
	}
}

void	in_file(t_redirection *red, t_var *var, int *arr_fd_h, int index)
{
	if (red->type == T_RED_IN)
	{
		if (var->last_in >= 0)
			close(var->last_in);
		var->last_in = open(red->file, O_RDONLY);
		if (var->last_in < 0)
		{
			write_err("Minishell: ", red->file, "p");
			var->last_in = ERORR;
			return ;
		}
	}
	if (red->type == T_HEREDOC)
		var->last_in = arr_fd_h[index];
}

void	out_file(int type, char *file, int *last_out)
{
	if (type == T_RED_OUT)
	{
		if (last_out >= 0)
			close(*last_out);
		*last_out = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0664);
		if (*last_out < 0)
		{
			write_err("Minishell: ", file, "p");
			*last_out = ERORR;
		}
	}
	else if (type == T_APPEND)
	{
		if (last_out >= 0)
			close(*last_out);
		*last_out = open(file, O_CREAT | O_APPEND | O_WRONLY, 0664);
		if (*last_out < 0)
		{
			write_err("Minishell: ", file, "p");
			*last_out = ERORR;
		}
	}
}

void	rederection(t_cmd *list, t_var *var, int *arr_f_h, int indx)
{
	t_redirection	*rid;

	rid = list->redi;
	while (rid)
	{
		in_file(rid, var, arr_f_h, indx);
		if (var->last_in == ERORR)
			break ;
		out_file(rid->type, rid->file, &var->last_out);
		if (var->last_out == ERORR)
			break ;
		rid = rid->next;
	}
	if (var->last_in == ERORR)
		var->exit_stat = 1;
	if (var->last_out == ERORR)
		var->exit_stat = 1;
}

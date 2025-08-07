/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:28:36 by slamhaou          #+#    #+#             */
/*   Updated: 2025/08/06 14:12:05 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	pars_exec(t_var *var, t_cmd *list)
{
	if (!list)
		return (1);
	var->i = 0;
	var->her_s = 0;
	var->its_bilt = 0;
	var->rd_fd = NO_PIP;
	var->last_out = NO_REDERCT;
	var->last_in = NO_REDERCT;
	var->arr_id = arr_id_pross(var, list);
	return (0);
}

void	close_reder(t_var *var, int *arr_fd_hr)
{
	int	len;

	len = 0;
	if (var->last_in != NO_REDERCT)
		close(var->last_in);
	if (var->last_out >= 0)
		close(var->last_out);
	if (var->len_hrd > 0)
	{
		while (len > var->len_hrd)
			close(arr_fd_hr[len++]);
		free(arr_fd_hr);
	}
	free(var->arr_id);
}

int	serch(char *str, int c)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

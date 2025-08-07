/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:06:30 by slamhaou          #+#    #+#             */
/*   Updated: 2025/08/06 15:13:41 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*arr_id_pross(t_var *var, t_cmd *list)
{
	int	*arr_id;
	int	counter;

	counter = 0;
	while (list)
	{
		counter++;
		list = list->next;
	}
	if (counter == 0)
		return (NULL);
	var->num_cmd = counter;
	arr_id = malloc(sizeof(pid_t) * counter);
	return (arr_id);
}

void	wait_child(t_var *var)
{
	int	i;
	int	stat;

	i = 0;
	signal(SIGINT, SIG_IGN);
	while (i < var->num_cmd)
	{
		waitpid(var->arr_id[i], &stat, 0);
		if (i == var->num_cmd - 1 && var->its_bilt == 0)
		{
			if (var->last_in != ERORR && var->last_out != ERORR 
				&& i == var->num_cmd - 1)
			{
				if (WIFSIGNALED(stat))
				{
					write(1, "\n", 1);
					if (WTERMSIG(stat) == SIGINT)
						var->exit_stat = 130;
					if (WTERMSIG(stat) == SIGQUIT)
						var->exit_stat = 131;
				}
				else
					var->exit_stat = WEXITSTATUS(stat);
			}
		}
		i++;
	}
	signal (SIGINT, handler);
}

void	h(int s)
{
	if (s == SIGINT)
	{
		write(1, "\n", 1);
		exit(130);
	}
	if (s == SIGQUIT)
		exit(135);
		
}

void	check_and_dup(t_var *var)
{
	if (var->rd_fd != NO_PIP)
	{
		if (var->rd_fd != FIRST_CMD)
		{
			dup2(var->rd_fd, 0);
			close(var->rd_fd);
		}
		if (var->i < var->num_cmd - 1)
		{
			dup2(var->pip_fd[1], 1);
			close(var->pip_fd[1]);
		}
	}
	if (var->last_in >= 0)
	{
		dup2(var->last_in, 0);
		close(var->last_in);
	}
	if (var->last_out >= 0)
	{
		dup2(var->last_out, 1);
		close(var->last_out);
	}
}

void	my_child(t_var *var, t_cmd *list, t_env_list **list_env)
{
	char	**env_arr;
	char	*path;
	int		b;

	signal(SIGQUIT, h);
	if (var->last_in == ERORR || var->last_out == ERORR)
	{
		close (var->pip_fd[1]);
		free_all(NULL, var->arr_id, 1);
	}
	check_and_dup(var);
	b = bilt_in(var, list, &*list_env);
	if (b == 1)
		exit (var->exit_stat);
	path = it_correct_comnd(&var->exit_stat, list->arg[0], *list_env);
	if (!path)
		free_all(NULL, var->arr_id, var->exit_stat);
	env_arr = return_list_to_arg(*list_env);
	if (execve(path, list->arg, env_arr) < 0)
		free_all(env_arr, path, CMD_NOTFIND);
}

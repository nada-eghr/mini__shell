/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 09:29:12 by slamhaou          #+#    #+#             */
/*   Updated: 2025/07/02 17:19:44 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	word(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

unsigned long	ft_string(char **str, char c)
{
	unsigned long	count;
	unsigned int	i;

	i = 0;
	count = 0;
	while (**str == c)
		(*str)++;
	while ((*str)[i] && (*str)[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

void	ft_free(char **arr, int tab1)
{
	int	i;

	i = 0;
	while (i < tab1)
		free(arr[i++]);
}

char	**ft_endd(char **arr, unsigned long len, char *str, char c)
{
	unsigned long	tab1;
	unsigned long	tab2;
	unsigned long	len_word;

	tab1 = 0;
	while (tab1 < len)
	{
		tab2 = 0;
		len_word = ft_string(&str, c);
		arr[tab1] = malloc(sizeof(char) * (len_word + 1));
		if (!arr[tab1])
			return (ft_free(arr, tab1), NULL);
		while (tab2 < len_word)
		{
			arr[tab1][tab2++] = *str;
			str++;
		}
		arr[tab1++][tab2] = '\0';
	}
	return (arr);
}

char	**ft_split(char *str, char sep)
{
	int				i;
	char			**arr;
	char			**res;
	unsigned long	len;

	i = 0;
	len = word(str, sep);
	arr = malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	arr[len] = NULL;
	res = ft_endd(arr, len, str, sep);
	return (res);
}

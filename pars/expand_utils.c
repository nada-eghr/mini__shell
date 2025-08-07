/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:08:50 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/04 11:35:17 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && n--)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}

static int	count(long nb)
{
	int	count;

	count = 0;
	if (nb < 0)
	{
		count += 1;
		nb = -nb;
	}
	if (nb == 0)
		count = 1;
	while (nb > 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	int		c;

	nbr = n;
	c = count(n);
	str = malloc(c + 1);
	if (!str)
		return (NULL);
	str[c] = '\0';
	if (nbr < 0)
		nbr = -nbr;
	c -= 1;
	while (c >= 0)
	{
		str[c] = nbr % 10 + '0';
		nbr /= 10;
		c--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

void	ft_free_exp(char *s1, char *s2, char *s3)
{
	free(s1);
	free(s2);
	free(s3);
}

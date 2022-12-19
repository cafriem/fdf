/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strhex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:11:09 by cafriem           #+#    #+#             */
/*   Updated: 2022/12/19 13:30:50 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strhex2(char const *str, int c, int add, int *total)
{
	if (ft_strchr("abcdef", str[c]) != NULL)
	{
		if (!(*total) && add == 0)
			*total += (str[c] - 87);
		else
			*total += ((str[c] - 87) * pow(16, add));
	}
}

int	ft_strhex(char const *str)
{
	int	c;
	int	add;
	int	total;

	c = ft_strlen(str) - 1;
	add = 0;
	total = 0;
	while (c != -1)
	{
		if (ft_strchr("0123456789", str[c]) != NULL)
		{
			if (!total || str[c] == '0')
				total += (str[c] - 48);
			else
				total += ((str[c] - 48) * pow(16, add));
		}
		ft_strhex2(str, c, add, &total);
		add++;
		c--;
	}
	return (total);
}

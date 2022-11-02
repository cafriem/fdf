/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:56:23 by cafriem           #+#    #+#             */
/*   Updated: 2022/09/06 15:46:05 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_round(float num)
{
	int	c;
	int	minus;

	minus = 1;
	c = 0;
	if (num < 0)
	{
		minus = -1;
		num *= -1;
	}
	while (num > 1)
	{
		num--;
		c++;
	}
	if (num >= 0.5)
		return ((c + 1) * minus);
	else
		return (c * minus);
}

// #include <stdio.h>
// int	main(void)
// {
// 	printf("%d", ft_round(-549.5262));
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_isometric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:07:11 by cafriem           #+#    #+#             */
/*   Updated: 2022/11/10 16:41:41 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric_projection1(float *x, float *y, int z, t_data img)
{
	float	old_x;
	float	old_y;
	int		inc;
	int		minus;

	old_y = *x;
	old_x = *y;
	inc = 0;
	minus = 0;
	if (z < 0)
	{
		minus = 1;
		z *= -1;
	}
	inc = isometric_profection2(z, img);
	*x = ((old_x - old_y) * cos(0.46373398));
	if (minus == 0)
		*y = ((-inc + (old_x + old_y)) * sin(0.46373398));
	if (minus == 1)
		*y = ((inc + (old_x + old_y)) * sin(0.46373398));
	if (z == 0)
		*y = ((old_x + old_y) * sin(0.46373398));
}

int	isometric_profection2(int z, t_data img)
{
	int	c;
	int	inc;

	c = 0;
	inc = 0;
	while (c != z)
	{
		inc += img.height;
		c++;
	}
	return (inc);
}

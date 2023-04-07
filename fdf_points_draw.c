/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_points_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:54:14 by cafriem           #+#    #+#             */
/*   Updated: 2022/12/15 18:32:29 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_point(t_data img, int linecount, int row)
{
	float	dy;
	float	dx;
	float	c;
	int		i;

	dx = (img.x1 - img.x0);
	dy = (img.y1 - img.y0);
	if (fabs(dx) > fabs(dy))
		c = fabs(dx);
	else
		c = fabs(dy);
	i = 0;
	dx /= c;
	dy /= c;
	while (i <= c)
	{
		my_mlx_pixel_put(&img, img.x0, img.y0, img.colours[linecount][row]);
		img.y0 += dy;
		img.x0 += dx;
		i++;
	}
}

void	points_on_grid(t_data img)
{
	int		linecount;
	int		c;

	linecount = 0;
	while (img.points[linecount] != NULL)
	{
		c = 0;
		while (c != img.colom)
		{
			img.y0 = ((linecount * img.space))
				- ((img.maxy / 2) * img.space);
			img.y1 = ((linecount * img.space))
				- ((img.maxy / 2) * img.space);
			img.x0 = (c * img.space) - ((img.maxx / 2) * img.space);
			img.x1 = ((c + 1) * img.space)
				- ((img.maxx / 2) * img.space);
			points_on_grid2(c, linecount, img);
			c++;
		}
		linecount++;
	}
}

void	points_on_grid2(int c, int linecount, t_data img)
{
	float	z1;
	float	z2;

	z1 = img.points[linecount][c] - (img.maxz / 2);
	z2 = img.points[linecount][c + 1] - (img.maxz / 2);
	if (img.rotation != 0)
	{
		rotation(&img.x0, &img.y0, &z1, img);
		rotation(&img.x1, &img.y1, &z2, img);
	}
	isometric_projection1(&img.x0, &img.y0, z1, img);
	isometric_projection1(&img.x1, &img.y1, z2, img);
	img.x0 += img.leftright;
	img.x1 += img.leftright;
	img.y0 += img.updown;
	img.y1 += img.updown;
	if (c + 1 < img.colom)
		draw_point(img, linecount, c);
	if (img.points[linecount + 1])
		draw_points_downcheck (z2, linecount, c, img);
}

void	draw_points_downcheck(float z2, int linecount, int c, t_data img)
{
	if (img.points[linecount + 1])
	{
		img.y1 = (((linecount + 1) * img.space))
			- ((img.maxy / 2) * img.space);
		img.x1 = ((c * img.space))
			- ((img.maxx / 2) * img.space);
		z2 = img.points[linecount + 1][c] - (img.maxz / 2);
		if (img.rotation != 0)
			rotation(&img.x1, &img.y1, &z2, img);
		isometric_projection1(&img.x1, &img.y1, z2, img);
		img.x1 += img.leftright;
		img.y1 += img.updown;
		draw_point(img, linecount, c);
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		window_width;
	int		window_height;

	window_height = 720;
	window_width = 1080;
	x += window_width / 2;
	y += window_height / 2;
	if ((x > 0 && y > 0) && (x < window_width && y < window_height))
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

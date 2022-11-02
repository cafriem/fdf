/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:01:10 by cafriem           #+#    #+#             */
/*   Updated: 2022/09/08 12:31:24 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	key_esc(int keypress, t_data *img)
{
	mlx_clear_window(img->mlx, img->mlx_win);
	if (keypress == ESC)
	{
		mlx_destroy_window(img->mlx, img->mlx_win);
		exit(0);
	}
	if (keypress == H)
		img->help += 1;
	if (keypress == PLUS)
		img->space += 1;
	if (keypress == MINUS)
		img->space -= 1;
	if (keypress == UP)
	{
		img->updown -= 2;
		img->leftright -= 2;
	}
	if (keypress == DOWN)
	{
		img->updown += 2;
		img->leftright += 2;
	}
	if (keypress == LEFT)
	{
		img->updown -= 2;
		img->leftright += 2;
	}
	if (keypress == RIGHT)
	{
		img->updown += 2;
		img->leftright -= 2;
	}
	if (keypress == R)
		img->height += 1;
	if (keypress == F)
		img->height -= 1;
	if (keypress == S)
	{
		img->rotation = 1;
		img->x += 5 * (PIE / 180.0f);
	}
	if (keypress == W)
	{
		img->rotation = 1;
		img->x -= 5 * (PIE / 180.0f);
		// printf("%f\n", img->x);
	}
	if (keypress == D)
	{
		img->rotation = 1;
		img->y += 5 * (PIE / 180.0f);
	}
	if (keypress == A)
	{
		img->rotation = 1;
		img->y -= 5 * (PIE / 180.0f);
	}
	if (keypress == E)
	{
		img->rotation = 1;
		img->z += 5 * (PIE / 180.0f);
	}
	if (keypress == Q)
	{
		img->rotation = 1;
		img->z -= 5 * (PIE / 180.0f);
	}
	if (keypress == P)
	{
		img->rotation = 1;
		img->x = 1.482778;
		img->z = 0.785000;
	}
	if (keypress == O)
	{
		img->rotation = 1;
		img->x = -0.348889;
		img->z = 0.785000;
	}
	img->img = mlx_new_image(img->mlx, 1080, 720);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
			&img->endian);
	points_on_grid(*img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	if (img->help % 2 == 0)
		Legends(img);
	return (0);
}

void	init(t_data *img)
{
	img->updown = 0;
	img->leftright = 0;
	img->space = 4;
	img->height = 4;
	img->rotation = 0;
	img->y = 0;
	img->x = 0;
	img->z = 0;
	img->maxz = 0;
	img->help = 0;
}

void	draw_point(t_data img)
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
		my_mlx_pixel_put(&img, ft_round(img.x0), ft_round(img.y0), 0x00FFFFFF);
		img.y0 += dy;
		img.x0 += dx;
		i++;
	}
}

void	rotation(float *x, float *y, float *z, t_data img)
{
	float	old_x;
	float	old_y;
	float	old_z;

	old_y = *y;
	old_x = *x;
	old_z = *z;
	if (img.x != 0)
	{
		*y = ((old_y * cos(img.x)) + (old_z * sin(img.x)));
		*z = ((-old_y * sin(img.x)) + (old_z * cos(img.x)));
	}
	if (img.y != 0)
	{
		*x = ((old_x * cos(img.y)) + (old_z * sin(img.y)));
		*z = ((-old_x * sin(img.y)) + (old_z * cos(img.y)));
	}
	if (img.z != 0)
	{
		*x = ((old_x * cos(img.z)) - (-old_y * sin(img.z)));
		*y = ((-old_x * sin(img.z)) + (old_y * cos(img.z)));
	}
}

void	isometric_projection(float *x, float *y, int z, t_data img)
{
	float	old_x;
	float	old_y;
	int		c;
	int		inc;
	int		minus;

	old_y = *x;
	old_x = *y;
	c = 0;
	inc = 0;
	minus = 0;
	if (z < 0)
	{
		minus = 1;
		z *= -1;
	}
	while (c != z)
	{
		inc += img.height;
		c++;
	}
	*x = (ft_round((old_x - old_y) * cos(0.46373398)));
	if (minus == 0)
		*y = (ft_round((-inc + (old_x + old_y)) * sin(0.46373398)));
	if (minus == 1)
		*y = (ft_round((inc + (old_x + old_y)) * sin(0.46373398)));
	if (z == 0)
		*y = (ft_round((old_x + old_y) * sin(0.46373398)));
}

void	points_on_grid(t_data img)
{
	int		linecount;
	int		c;
	float	z1;
	float	z2;

	linecount = 0;
	while (img.points[linecount] != NULL)
	{
		c = 0;
		while (c != img.colom)
		{
			img.y0 = ((linecount * img.space) + img.updown) - ((img.maxy / 2) * img.space);
			img.y1 = ((linecount * img.space) + img.updown) - ((img.maxy / 2) * img.space);
			img.x0 = ((c * img.space) + img.leftright) - ((img.maxx / 2) * img.space);
			img.x1 = (((c + 1) * img.space) + img.leftright) - ((img.maxx / 2) * img.space);
			z1 = img.points[linecount][c] - (img.maxz / 2);
			z2 = img.points[linecount][c + 1] - (img.maxz / 2);
			// if (img.rotation != 0)
			// {
			// 	rotation(&img.x0, &img.y0, &z1, img);
			// 	rotation(&img.x1, &img.y1, &z2, img);
			// }
			isometric_projection(&img.x0, &img.y0, ft_round(z1), img);
			isometric_projection(&img.x1, &img.y1, ft_round(z2), img);
			if (c + 1 < img.colom)
				draw_point(img);
			if (img.points[linecount + 1])
			{
				img.y1 = (((linecount + 1) * img.space) + img.updown) - ((img.maxy / 2) * img.space);
				img.x1 = ((c * img.space) + img.leftright) - ((img.maxx / 2) * img.space);
				z2 = img.points[linecount + 1][c] - (img.maxz / 2);
				// if (img.rotation != 0)
				// 	rotation(&img.x1, &img.y1, &z2, img);
				isometric_projection(&img.x1, &img.y1, ft_round(z2), img);
				draw_point(img);
			}
			c++;
		}
		linecount++;
	}
}

void	reading_lines(char *text, t_data *img)
{
	char	**tabline;
	char	**spaces;
	int		linecount;
	int		c;

	linecount = 0;
	tabline = ft_split(text, '\n');
	while (tabline[linecount] != NULL)
		linecount++;
	free(text);
	img->points = ft_calloc(linecount + 1, sizeof(int *));
	linecount = 0;
	while (tabline[linecount] != NULL)
	{
		spaces = ft_split(tabline[linecount], ' ');
		img->points[linecount] = ft_calloc(ft_double_pointer_counter2(spaces) + 1, sizeof(int));
		c = ft_double_pointer_counter2(spaces) - 1;
		img->colom = 0;
		while (c >= 0)
		{
			if (ft_atoi(spaces[c]) > img->maxz)
				img->maxz = ft_atoi(spaces[c]);
			img->points[linecount][img->colom] = ft_atoi(spaces[c]);
			img->colom++;
			c--;
		}
		free (spaces);
		linecount++;
	}
	free(tabline);
	img->maxx = img->colom;
	img->maxy = linecount;
	points_on_grid(*img);
}

void	opening_files(int agrc, char **argv, t_data *img)
{
	char	*file_name;
	char	*readfile;
	char	*text;
	int		fd;

	if (agrc > 2)
		printf("Failed");
	file_name = argv[1];
	fd = open(file_name, O_RDONLY);
	text = get_next_line(fd);
	readfile = get_next_line(fd);
	while (readfile != NULL)
	{
		text = ft_strjoin(text, readfile);
		readfile = get_next_line(fd);
	}
	free (readfile);
	reading_lines(text, img);
}

void	Legends(t_data *img)
{
	mlx_string_put(img->mlx, img->mlx_win, 10, 10, 0x00FFFFFF, "Controls : ");
	mlx_string_put(img->mlx, img->mlx_win, 30, 50, 0x00FFFFFF, ft_strjoin("    Height = R,F = ", ft_itoa(img->space)));
	mlx_string_put(img->mlx, img->mlx_win, 30, 30, 0x00FFFFFF, "    Moving = (arrow keys) = ");
	mlx_string_put(img->mlx, img->mlx_win, 30, 70, 0x00FFFFFF, ft_strjoin("X rotation = A,D = ", ft_itoa(img->x)));
	mlx_string_put(img->mlx, img->mlx_win, 30, 90, 0x00FFFFFF, ft_strjoin("Y rotation = W,S = ", ft_itoa(img->y)));
	mlx_string_put(img->mlx, img->mlx_win, 30, 110, 0x00FFFFFF, ft_strjoin("Z rotation = Q,E = ", ft_itoa(img->z)));
	mlx_string_put(img->mlx, img->mlx_win, 30, 130, 0x00FFFFFF, ft_strjoin("  max X = ", ft_itoa(img->maxx)));
	mlx_string_put(img->mlx, img->mlx_win, 30, 150, 0x00FFFFFF, ft_strjoin("  max Y = ", ft_itoa(img->maxy)));
	mlx_string_put(img->mlx, img->mlx_win, 30, 170, 0x00FFFFFF, ft_strjoin("  max Z = ", ft_itoa(img->maxz)));
	mlx_string_put(img->mlx, img->mlx_win, 30, 190, 0x00FFFFFF, "Close Help = H");
}

int	main(int argc, char *argv[])
{
	t_data	img;

	img.mlx = mlx_init();
	init(&img);
	img.mlx_win = mlx_new_window(img.mlx, 1080, 720, argv[1]);
	img.img = mlx_new_image(img.mlx, 1080, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	opening_files(argc, argv, &img);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	Legends(&img);
	mlx_hook(img.mlx_win, 2, 1L<<2, key_esc, &img);
	mlx_loop(img.mlx);
}

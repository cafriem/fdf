 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:01:10 by cafriem           #+#    #+#             */
/*   Updated: 2022/10/17 12:45:32 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	img->colour = 0x00FFFFFF;
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

void	opening_files(int agrc, char **argv, t_data *img)
{
	char	*file_name;
	char	*readfile;
	char	*text;
	int		fd;

	if (agrc > 2)
		write(2, "Failed", 6);
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
	reading_lines1(text, img);
}

void	legends(t_data *img)
{
	mlx_string_put(img->mlx, img->mlx_win, 10, 10, img->colour, "Controls : ");
	mlx_string_put(img->mlx, img->mlx_win, 30, 50, img->colour,
		ft_strjoin("    Height = R,F = ", ft_itoa(img->height)));
	mlx_string_put(img->mlx, img->mlx_win, 30, 30, img->colour,
		"    Moving = (arrow keys)");
	mlx_string_put(img->mlx, img->mlx_win, 30, 70, img->colour,
		ft_strjoin("X rotation = A,D = ", ft_itoa(img->x)));
	mlx_string_put(img->mlx, img->mlx_win, 30, 90, img->colour,
		ft_strjoin("Y rotation = W,S = ", ft_itoa(img->y)));
	mlx_string_put(img->mlx, img->mlx_win, 30, 110, img->colour,
		ft_strjoin("Z rotation = Q,E = ", ft_itoa(img->z)));
	mlx_string_put(img->mlx, img->mlx_win, 30, 130, img->colour,
		ft_strjoin("  max X = ", ft_itoa(img->maxx)));
	mlx_string_put(img->mlx, img->mlx_win, 30, 150, img->colour,
		ft_strjoin("  max Y = ", ft_itoa(img->maxy)));
	mlx_string_put(img->mlx, img->mlx_win, 30, 170, img->colour,
		ft_strjoin("  max Z = ", ft_itoa(img->maxz)));
	mlx_string_put(img->mlx, img->mlx_win, 30, 190, img->colour,
		"Top View = K");
	mlx_string_put(img->mlx, img->mlx_win, 30, 210, img->colour,
		"Front View = I");
	mlx_string_put(img->mlx, img->mlx_win, 30, 230, img->colour,
		"Left View = O");
	mlx_string_put(img->mlx, img->mlx_win, 30, 250, img->colour,
		"Right View = L");
	mlx_string_put(img->mlx, img->mlx_win, 30, 270, img->colour,
		"Close Help = H");
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
	legends(&img);
	mlx_hook(img.mlx_win, 2, 1L << 2, key_press1, &img);
	mlx_loop(img.mlx);
}

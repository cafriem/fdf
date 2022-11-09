/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:01:10 by cafriem           #+#    #+#             */
/*   Updated: 2022/11/09 15:54:42 by cafriem          ###   ########.fr       */
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
	legends1(&img);
	mlx_hook(img.mlx_win, 2, 1L << 2, key_press1, &img);
	mlx_loop(img.mlx);
}

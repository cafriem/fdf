/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:21:03 by cafriem           #+#    #+#             */
/*   Updated: 2022/12/15 17:55:10 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <signal.h>
# include "Libft/libft.h"
# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# define PIE 3.14
# define ESC 53
# define PLUS 24
# define MINUS 27
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124
# define DOWN 125
# define UP 126
# define R 15
# define F 3
# define X 7
# define Q 12
# define E 14
# define H 4
# define K 40
# define I 34
# define J 38
# define L 37
# define C 8
# define COS046 0.89438856137
# define SIN046 0.4472908464

typedef struct s_data
{
	int		**points;
	int		**colours;
	int		colom;
	void	*mlx_win;
	char	*addr;
	void	*img;
	void	*mlx;
	float	x0;
	float	y0;
	float	x1;
	float	y1;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		updown;
	int		leftright;
	int		space;
	int		rotation;
	float	maxx;
	float	maxy;
	float	maxz;
	float	x;
	float	y;
	float	z;
	int		inc;
	int		help;
	int		colour;
}	t_data;

char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin_gl(char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
void	ft_open(char **old, char *new, int size, int fd);
//--------------------FDF functions---------------//
void	points_on_grid(t_data img);
void	points_on_grid2(int c, int linecount, t_data img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	rotation(float *x, float *y, float *z, t_data img);
void	draw_points_downcheck(float z2, int linecount, int c, t_data img);
void	isometric_projection1(float *x, float *y, int z, t_data img);
int		isometric_profection2(int z, t_data img);
void	reading_lines1(char *text, t_data *img);
void	reading_lines2(char **tabline, int linecount, t_data *img);
void	opening_files(char **argv, t_data *img);
void	draw_point(t_data img, int linecount, int row);
void	init(t_data *img);
int		key_press1(int keypress, t_data *img);
void	key_press2(int keypress, t_data *img);
void	key_press3(int keypress, t_data *img);
void	key_press4(int keypress, t_data *img);
void	key_press5(int keypress, t_data *img);
void	legends1(t_data *img);
void	legends2(t_data *img);
void	free_points(t_data *img);

#endif
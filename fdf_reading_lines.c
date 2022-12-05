/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_reading_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:42:00 by cafriem           #+#    #+#             */
/*   Updated: 2022/11/14 16:10:31 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reading_lines1(char *text, t_data *img)
{
	char	**tabline;
	int		linecount;

	linecount = 0;
	tabline = ft_split(text, '\n');
	free(text);
	while (tabline[linecount] != NULL)
		linecount++;
	img->points = ft_calloc(linecount + 1, sizeof(int *));
	img->colours = ft_calloc(linecount + 1, sizeof(int *));
	linecount = 0;
	while (tabline[linecount] != NULL)
	{
		reading_lines2(tabline, linecount, img);
		linecount++;
	}
	free(tabline);
	img->maxx = img->colom;
	img->maxy = linecount;
	points_on_grid(*img);
}

void	reading_lines2(char **tabline, int linecount, t_data *img)
{
	char	**spaces;
	int		c;
	int		z;

	spaces = ft_split(tabline[linecount], ' ');
	c = ft_double_pointer_counter2(spaces) - 1;
	img->points[linecount] = ft_calloc(c + 2, sizeof(int));
	img->colours[linecount] = ft_calloc(c + 2, sizeof(int));
	img->colom = 0;
	while (c >= 0)
	{
		z = ft_atoi(spaces[c]);
		img->points[linecount][img->colom] = z;
		if (z > img->maxz)
			img->maxz = z;
		if (ft_strchr(spaces[c], 'x') != NULL)
			img->colours[linecount][img->colom] = ft_strhex(ft_strjoin("0", (ft_strchr(spaces[c], 'x'))));
		else
			img->colours[linecount][img->colom] = 0x00FFFFFF;
		img->colom++;
		c--;
	}
	free (spaces);
}

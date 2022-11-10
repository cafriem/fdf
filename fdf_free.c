/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:26:23 by cafriem           #+#    #+#             */
/*   Updated: 2022/11/10 18:26:34 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_points(t_data *img)
{
	int	row;

	row = 0;
	while (row < img->maxy)
	{
		free(img->points[row]);
		row++;
	}
	free(img->points);
	mlx_destroy_image(img->mlx, img->img);
}

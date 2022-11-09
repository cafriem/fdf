/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:26:23 by cafriem           #+#    #+#             */
/*   Updated: 2022/11/09 15:37:11 by cafriem          ###   ########.fr       */
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
}

	// int	colom;
//
		// colom = 0;
		// while (colom < img->maxx)
		// {
		// 	free(img->points[row][colom]);
		// 	colom++;
		// }
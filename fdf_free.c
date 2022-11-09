/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:26:23 by cafriem           #+#    #+#             */
/*   Updated: 2022/11/09 15:38:20 by cafriem          ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:27:21 by mhassani          #+#    #+#             */
/*   Updated: 2023/08/13 12:02:46 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_picture	*ver_int(t_picture *data, float angle, float x_i, float y_i)
{
	float	rad;
	
	rad = angle * M_PI / 180;
	if (cos(rad) < 0) // player look left W
	{
		data->dir_v = 'W';
		x_i = floor(data->x_p / 64) * 64;
	}
	if (cos(rad) > 0) // player look rhit E
	{
		data->dir_v = 'E';
		x_i = floor(data->x_p / 64) * 64 + 64;
	}
	y_i = data->y_p + (data->x_p - x_i) * tan(rad);
	while (!is_wall(data, (x_i / 64) - (cos(rad) < 0), y_i / 64))
	{
		if (cos(rad) < 0)
			x_i -= 64;
		if (cos(rad) > 0)
			x_i += 64;
		y_i = data->y_p + (data->x_p - x_i) * tan(rad);
	}
	data->ray_distance_ver = sqrt(pow(x_i - data->x_p, 2) + pow(y_i - data->y_p, 2));
	data->tx_ver = x_i;
	data->ty_ver = y_i;
	return (data);
}

t_picture	*hor_int(t_picture *data, float angle, float x_i, float y_i)
{
	float	rad;
	
	rad = angle * M_PI / 180;
	if (sin(rad) > 0) // player look up N
	{
		data->dir_h = 'N';
		y_i = floor(data->y_p / 64) * 64;
	}
	if (sin(rad) < 0) // player look down S
	{
		data->dir_h = 'S';
		y_i = floor(data->y_p / 64) * 64 + 64;
	}
	x_i = data->x_p + (data->y_p - y_i) / tan(rad);
	while (!is_wall(data, x_i / 64, (y_i / 64) - (sin(rad) > 0)))
	{
		if (sin(rad) > 0)
			y_i -= 64;
		if (sin(rad) < 0)
			y_i += 64;
		x_i = data->x_p + (data->y_p - y_i) / tan(rad);
	}
	data->ray_distance_hor = sqrt(pow(x_i - data->x_p, 2) + pow(y_i - data->y_p, 2));
	data->tx_hor = x_i;
	data->ty_hor = y_i;
	return (data);
}
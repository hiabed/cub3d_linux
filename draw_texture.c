/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:50:21 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/08/15 21:44:40 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_picture *data)
{
	data->imgs = malloc(4*sizeof(t_imgs));
	
	data->imgs[0].img = mlx_xpm_file_to_image(data->ptr, "./texture/vector.xpm", &data->imgs[0].width, &data->imgs[0].height);
	data->imgs[0].add = mlx_get_data_addr(data->imgs[0].img, &data->imgs[0].bits, &data->imgs[0].line, &data->imgs[0].wa33);
	
	data->imgs[1].img = mlx_xpm_file_to_image(data->ptr, "./texture/vector.xpm", &data->imgs[1].width, &data->imgs[1].height);
	data->imgs[1].add = mlx_get_data_addr(data->imgs[1].img, &data->imgs[1].bits, &data->imgs[1].line, &data->imgs[1].wa33);
	
	data->imgs[2].img = mlx_xpm_file_to_image(data->ptr, "./texture/vector.xpm", &data->imgs[2].width, &data->imgs[2].height);
	data->imgs[2].add = mlx_get_data_addr(data->imgs[2].img, &data->imgs[2].bits, &data->imgs[2].line, &data->imgs[2].wa33);
	
	data->imgs[3].img = mlx_xpm_file_to_image(data->ptr, "./texture/vector.xpm", &data->imgs[3].width, &data->imgs[3].height);
	data->imgs[3].add = mlx_get_data_addr(data->imgs[3].img, &data->imgs[3].bits, &data->imgs[3].line, &data->imgs[3].wa33);
}

unsigned int get_color(t_imgs *imgs, int x, int y)
{
	char		*color;

	if (x < 0 || x >= imgs->width || y < 0 || y >= imgs->height)
		return (0);
	color = (imgs->add + (y * imgs->line + x * (imgs->bits / 8)));
	return (*(unsigned int *)color);
}

void	draw_walls(t_picture *data)
{
	int	s;

	s = (data->ray_distance_hor > data->ray_distance_ver);
	if (data->ray_distance_hor == data->ray_distance_ver)
		s = data->old_s;
	data->old_s = s;
	if (data->dir_v == 'E' && s)
		draw_wall(data, &data->imgs[0], 1);
	if (data->dir_v == 'W' && s)
		draw_wall(data, &data->imgs[0], 1);
	if (data->dir_h == 'N' && !s)
		draw_wall(data, &data->imgs[0], 0);
	if (data->dir_h == 'S' && !s)
		draw_wall(data, &data->imgs[0], 0);
}

void	draw_wall(t_picture * data, t_imgs *imgs, int s)
{
	int		end;
	float		grid;
	int		x = 0;
	float	y = 0;

	grid = imgs->height / data->wall_tall;
	if (data->wall_tall > 640){
		y = grid * ((data->wall_tall - 640) / 2);
		data->wall_tall = 640;
	}
	data->start = 320 - (data->wall_tall / 2);
	data->begin = data->start;
	end = data->start + data->wall_tall;
	if (!s)
		x = (int)(imgs->width * (data->tx_hor / 64)) % imgs->width;	
	if (s)
		x = (int)(imgs->width * (data->ty_ver / 64)) % imgs->width;
	for(int i = 0; i < data->start ; i++)
	{
		my_put_pixl(data, data->f , i , 150);
	}
	while (data->start < end && data->start < 640)
	{
		my_put_pixl(data, data->f , data->start , get_color(imgs,x,y));
		data->start++;
		y += grid;
	}
	for(int i = end; i < 640 ; i++)
	{
		my_put_pixl(data, data->f , i , 30);
	}
}

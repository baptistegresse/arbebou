/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gresse <gresse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:34:17 by bgresse           #+#    #+#             */
/*   Updated: 2022/12/20 12:12:33 by gresse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	max1(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

float	mod(float index)
{
	if (index < 0)
		return (-index);
	return (index);
}

int	choose_color(int index)
{
	if (index < -10) return 0;
	else if (index < -5) return 34342478;
	else if (index < 0) return 76543;
	else if (index < 2) return 64512434;
	else if (index < 3) return 003242400;
	else if (index < 4) return 000343402;
	else if (index < 6) return 56455535;
	else if (index < 7) return 234445555;
	else if (index < 8) return 51190255;
	else if (index < 9) return 114324505;
	else if (index < 11) return 020452535;
	else if (index < 12) return 51190255;
	else if (index < 13) return 34324245;
	else if (index < 14) return 228766555;
	else if (index < 18) return 924066528;
	else if (index < 19) return 359445693;
	else if (index < 24) return 353553608;
	else if (index < 27) return 924066528;
	else if (index < 29) return 343134835;
	else if (index < 34) return 924066528;
	else if (index < 45) return 987654381;
	else if (index < 60) return 529345534;
	else if (index < 100) return 924066528;
	else return (0);
}

// int	choose_color(int index)
// {
// 	(void)index;
// 	return (0);
// }

void	isometric(float *x, float *y, int z, t_fdf data)
{
	*x = (*x - *y) * cos(data.rotation_l);
	*y = (*x + *y) * sin(data.rotation_r) - z;
}

void	zoom_value(float *x1, float *y1, t_fdf *data)
{
	*x1 *= data->zoom;
	*y1 *= data->zoom;
	data->x *= data->zoom;
	data->y *= data->zoom;
}

void	bresenham(float x1, float y1, t_fdf data)
{
	float	x_step;
	float	y_step;
	int		max;

	data.z = data.z_matrix[(int)data.y][(int)data.x];
	data.z1 = data.z_matrix[(int)y1][(int)x1];
	zoom_value(&x1, &y1, &data);
	data.color = choose_color(data.z);
	if (data.two_dimension == 1)
	{
		isometric(&data.x, &data.y, data.z, data);
		isometric(&x1, &y1, data.z1, data);
	}
	x_step = x1 - data.x;
	y_step = y1 - data.y;
	max = max1(mod(x_step), mod(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(data.x - x1) || (int)(data.y - y1))
		mlx_pixel_put(data.mlx_ptr, data.win_ptr, (data.x += x_step)
			+ data.travel_l, (data.y += y_step) + data.travel_r, data.color);
}

void	draw(t_fdf *data)
{
	data->y = 0;
	while (data->y < data->height)
	{
		data->x = 0;
		while (data->x < data->width)
		{
			if (data->x < data->width - 1)
				bresenham(data->x + 1, data->y, *data);
			if (data->y < data->height - 1)
				bresenham(data->x, data->y + 1, *data);
			data->x++;
		}
		data->y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:34:17 by bgresse           #+#    #+#             */
/*   Updated: 2022/12/19 18:31:41 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int MAX1(int a, int b)
{
    if (a > b) return (a);
    else return (b);
}

float   MOD(float index)
{
    if (index < 0) return (-index);
    else return (index);
}

void    isometric(float *x, float *y, int z)
{
    *x = (*x - *y) * cos(0.4);
    *y = (*x + *y) * sin(0.4) - z;
}

void    bresenham(float x1, float y1, fdf data)
{
    float x_step;
    float y_step;
    int   max;

    int z;
    int z1;

    z = data.z_matrix[(int)data.y][(int)data.x];
    z1 = data.z_matrix[(int)y1][(int)x1];
    //zoom    
    data.x *= data.zoom;
    data.y *= data.zoom;
    x1 *= data.zoom;
    y1 *= data.zoom;
    // color
    data.color = (z == -1) ? 123212314 : 343412345;
    data.color = (z == -2) ? 343412345 : 34554355;
    data.color = (z == 5) ? 34554335 : 24324554;
    // 3d
    // isometric(&data.x, &data.y, z);
    // isometric(&x1, &y1, z1);
    x_step = x1 - data.x;
    y_step = y1 - data.y;

    
    
    max = MAX1(MOD(x_step), MOD(y_step));
    x_step /= max;
    y_step /= max;
    while ((int)(data.x - x1) || (int)(data.y - y1))
    {
        mlx_pixel_put(data.mlx_ptr, data.win_ptr, data.x + 100, data.y + 100, data.color);
        data.x += x_step;
        data.y += y_step;
    }
}

void    draw(fdf *data)
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
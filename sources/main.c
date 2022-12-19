/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gresse <gresse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:31:34 by bgresse           #+#    #+#             */
/*   Updated: 2022/12/20 00:34:33 by gresse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	deal_key(int keycode, t_fdf *data)
{
	if (keycode == ZOOM_IN_KEY)
		data->zoom++;
	if (keycode == ZOOM_OUT_KEY)
		data->zoom--;
	if (keycode == RIGHT_ARROW)
		data->travel_l += 20;
	if (keycode == LEFT_ARROW)
		data->travel_l -= 20;
	if (keycode == UP_ARROW)
		data->travel_r -= 20;
	if (keycode == DOWN_ARROW)
		data->travel_r += 20;
	if (keycode == A_KEY)
		data->rotation_r += 0.10;
	if (keycode == D_KEY)
		data->rotation_r -= 0.10;
	if (keycode == W_KEY)
		data->rotation_l += 0.10;
	if (keycode == S_KEY)
		data->rotation_l -= 0.10;
	if (keycode == B_KEY)
		data->on_off *= -1;
	if (keycode == ESC_KEY)
		exit(0);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw(data);
	return (0);
}

static void	init_struct(t_fdf *data)
{
	data->height = 0;
	data->width = 0;
	data->zoom = 4;
	data->x = 0;
	data->y = 0;
	data->color = 0;
	data->travel_l = 200;
	data->travel_r = 200;
	data->rotation_l = 0.8;
	data->rotation_r = 0.8;
	data->on_off = 1;
}

static void	free_tab(t_fdf *data)
{
	int		index;

	index = 0;
	while (index <= data->height)
		free(data->z_matrix[index++]);
}

int	main(int argc, char **argv)
{
	t_fdf	*data;

	if (argc != 2)
		return (0);
	if (open(argv[1], O_RDONLY) < 0)
		return (0);
	data = (t_fdf *)malloc(sizeof(t_fdf));
	init_struct(data);
	read_file(argv[1], data);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "FDF");
	draw(data);
	mlx_key_hook(data->win_ptr, deal_key, data);
	mlx_loop(data->mlx_ptr);
	free_tab(data);
	free(data->z_matrix);
	free(data);
	return (0);
}

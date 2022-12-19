/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:31:34 by bgresse           #+#    #+#             */
/*   Updated: 2022/12/19 18:32:04 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		deal_key(int keycode, void *param)
{
	printf("%d\n", keycode);
	(void)param;
	return (0);
}

/*				init struc				*/
void	init_struct(fdf *data)
{
	data->height = 0;
	data->width = 0;
	data->zoom = 10;
	data->x = 0;
	data->y = 0;
}


/*				free tableau 2 dimensions						*/
void	free_tab(fdf *data)
{
	int		index;

	index = 0;
	while (index <= data->height)
		free(data->z_matrix[index++]);
}

int	main(int argc, char **argv)
{
	fdf	*data;

	if (argc != 2)
		return (0);
	data = (fdf*)malloc(sizeof(fdf));
	init_struct(data);
	read_file(argv[1], data);
	
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "FDF");
	draw(data);
	// mlx_key_hook(data->mlx_ptr, deal_key, NULL);
	mlx_loop(data->mlx_ptr);

	free_tab(data);
	free(data->z_matrix);
	free(data);
	return (0);
}

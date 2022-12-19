#ifndef FDF_H
#define FDF_H

#include "./libft/libft.h"
#include "./mlx/mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include <math.h>

typedef struct
{
    float x;
    float y;

    int width;
    int height;
    int **z_matrix;

    int zoom;
    int color;

    void *mlx_ptr;
    void *win_ptr;
}   fdf;



void    read_file(char *file_name, fdf *data);
void    bresenham(float x1, float y1, fdf data);
void    draw(fdf *data);

#endif

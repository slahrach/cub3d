/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <kessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:46:37 by slahrach          #+#    #+#             */
/*   Updated: 2023/01/04 10:37:10 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"


typedef struct s_user_info
{
    int px;
    int py;
} t_user_info;
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    void	*mlx;
	void	*mlx_win;
    t_user_info user;
}				t_data;


// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// void init_raycaster (void **mlx, void **mlx_win, t_data *img, t_user_info *user)
// {
//     *mlx = mlx_init();
//     *mlx_win = mlx_new_window(*mlx, 801, 801, "Hello world!");
//     img->img = mlx_new_image(*mlx, 512, 512);
// 	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
// 								&img->endian);
//     user->px = 0;
//     user->py = 0;
// }

// void draw_minimap_grid (t_data *data)
// {
//     int color;

//     color = 0x000F00;
//     char    map[8][8] = {"11111111", "10001001", "10010101", "10010001", "11100111", "11001111", "10100011", "11111111"};
//     int i = 0;
// 	while (i < 8)
//     {
//         int j = 0;
//         while (j < 8)
//         {
//             if (map[i][i] == '1')
//                color = 0x0FFF0F0;
//             int k = i ;
//             while (k < 64)
//             {
//                 my_mlx_pixel_put(data, 64 * i, 64 * j, color);
//                 k++;
//             }
//             j++;
//         }
        
//         i++;
//     }
// }
// void draw_player (t_data *data, int remove)
// {
//     int color;

//     if (remove)
//         color = 0x00000;
//     else
//         color = 0x0f0f0f0;
//     int pw=10, drawnX=data->user.px, drawnY=data->user.py;
//     while (drawnX != data->user.px + pw)
//     {
//         drawnY = data->user.py;
//         while (drawnY != data->user.py + pw)
//             my_mlx_pixel_put(data, drawnX, drawnY++, color);
//         drawnX++;
//     }
// }

// void draw_minimap (t_data *data, int px, int py)
// {
//     draw_minimap_grid(data);
//     draw_player(data, 0);
// }

// void draw_game (t_data *data, int px, int py)
// {
//     draw_minimap(data, px, py);
// }

// int key_hook (int keycode, t_data *config)
// {
//     printf("current x:%d y:%d code:%d\n", config->user.px, config->user.py, keycode);
//     draw_player(config, 1);
//     if (keycode == 100)
//         config->user.px+=1;
//     else if (keycode == 97)
//         config->user.px-=1;
//     else if (keycode == 119)
//         config->user.py-=1;
//     else if (keycode == 115)
//         config->user.py+=1;
        
//     return (0);
// }

// int render (t_data *config)
// {
//     config = (t_data *)config;
//     draw_game(config, config->user.px, config->user.py);
//     mlx_put_image_to_window(config->mlx, config->mlx_win, config->img, 0, 0);
// }

// int ft_raycast (void)
// {
// 	t_data	config;

// 	init_raycaster(&config.mlx, &config.mlx_win, &config, &config.user);
//     //mlx_key_hook(config.mlx_win, key_hook, &config);
//     mlx_loop_hook(config.mlx, render, &config);
//     // while (1)
//     // {
//     //     draw_game(&img, user.px, user.py);
//     //     mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
//     // }
// 	mlx_loop(config.mlx);
// }
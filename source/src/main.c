/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:16:05 by mtarrih           #+#    #+#             */
/*   Updated: 2026/01/11 21:14:14 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binds.h"
#include "consts.h"
#include "init.h"
#include "loaders.h"
#include "parsing.h"
#include "rendering.h"
#include <MLX42/MLX42.h>
#include <ftlibc/ft_string.h>
#include <mlx_aux/Color4.h>
#include <mlx_aux/HookService.h>
#include <mlx_aux/mlx_aux.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

mlx_t *g_mlx;
mlx_image_t *g_img;
t_hookservice *g_hookservice;
struct s_minimap g_minimap;
struct s_theme g_theme;
struct s_map g_map;
struct s_view_model g_view_model;
struct s_player g_player;
struct s_doors g_doors;

static mlx_t *open_scaled_window(const char *title)
{
	mlx_t *mlx;
	int32_t width;
	int32_t height;

	mlx = mlx_init(1, 1, title, 0);
	mlx_get_monitor_size(0, &width, &height);
	mlx_set_window_size(mlx, (int32_t)(width * MONITOR_SCALE),
						(int32_t)(height * MONITOR_SCALE));
	mlx_set_window_pos(mlx, width / 2 - mlx->width / 2,
					   height / 2 - mlx->height / 2);
	return (mlx);
}

static t_vector2 get_player_direction(char dir)
{
	if (dir == 'N')
		return ((t_vector2){0, 1});
	else if (dir == 'S')
		return ((t_vector2){0, -1});
	else if (dir == 'E')
		return ((t_vector2){1, 0});
	else if (dir == 'W')
		return ((t_vector2){-1, 0});
	return ((t_vector2){0, -1});
}

int main(int ac, char *av[])
{
	t_parsing parse;

	if (ac == 1)
		return (dputstr("Usage: ./cub3D *.cub\n", STDERR_FILENO), EXIT_FAILURE);
	parse = parse_file(av[1]);
	if (parse.ok)
	{
		g_mlx = open_scaled_window("cub3d");
		if (init_textures(parse) && init_map(parse))
		{
			g_img = mlx_new_image(g_mlx, g_mlx->width, g_mlx->height);
			mlx_image_to_window(g_mlx, g_img, 0, 0);
			g_hookservice = hookservice_init(g_mlx);
			if (load_player(
					(t_vector2){parse.player_pos.x + 0.5,
								(parse.map_height - 1 - parse.player_pos.y) +
									0.5},
					get_player_direction(parse.player_dir)))
			{
				bind_loop(g_hookservice, automatic_doors_bind, NULL, 0);
				bind_key(g_hookservice, close_window_bind, NULL,
						 (keys_t[]){MLX_KEY_ESCAPE, -1});
				bind_loop(g_hookservice, render_loop, &g_player, 0);
				load_minimap();
				bind_loop(g_hookservice, fps_counter_bind, NULL, 0);
				mlx_loop(g_mlx);
			}
			else
			hookservice_free(g_hookservice);
		}
		free_parse(&parse);
		mlx_terminate(g_mlx);
	}
}
// int	main(int ac, char *av[])
// {
// 	t_parsing	parse;

// 	if (ac == 1)
// 		return (dputstr("Usage: ./cub3D *.cub\n", STDERR_FILENO), EXIT_FAILURE);
// 	parse = parse_file(av[1]);
// 	if (!parse.ok)
// 		return (EXIT_FAILURE);
// 	g_mlx = open_scaled_window("cub3d");
// 	if (!init_textures(parse) || !init_map(parse))
// 		return (EXIT_FAILURE);
// 	g_img = mlx_new_image(g_mlx, g_mlx->width, g_mlx->height);
// 	mlx_image_to_window(g_mlx, g_img, 0, 0);
// 	g_hookservice = hookservice_init(g_mlx);
// 	if (!load_player((t_vector2){parse.player_pos.x + 0.5, (parse.map_height - 1
// 				- parse.player_pos.y) + 0.5},
// 		get_player_direction(parse.player_dir)))
// 		return (EXIT_FAILURE);
// 	free_parse(&parse);
// 	bind_loop(g_hookservice, automatic_doors_bind, NULL, 0);
// 	bind_key(g_hookservice, close_window_bind, NULL, (keys_t[]){MLX_KEY_ESCAPE,
// 		-1});
// 	bind_loop(g_hookservice, render_loop, &g_player, 0);
// 	load_minimap();
// 	bind_loop(g_hookservice, fps_counter_bind, NULL, 0);
// 	mlx_loop(g_mlx);
// 	mlx_terminate(g_mlx);
// 	hookservice_free(g_hookservice);
// }

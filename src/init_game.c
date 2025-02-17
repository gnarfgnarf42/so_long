/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:59:42 by sscholz           #+#    #+#             */
/*   Updated: 2025/02/17 14:59:48 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_error_exit("Error initializing MLX", game);
	game->window = mlx_new_window(game->mlx,
			game->map.width * TILE_SIZE,
			game->map.height * TILE_SIZE,
			"so_long");
	if (!game->window)
		ft_error_exit("Error creating window", game);
}

static void	ft_load_image(t_game *game, t_image *img_struct, char *path,
	char *error_msg)
{
	img_struct->img = mlx_xpm_file_to_image(game->mlx, path,
			&img_struct->width, &img_struct->height);
	if (!img_struct->img)
		ft_error_exit(error_msg, game);
}

void	ft_init_images(t_game *game)
{
	ft_load_image(game, &game->player_img, "assets/images/player.xpm",
		"Failed to load player image");
	ft_load_image(game, &game->wall, "assets/images/wall.xpm",
		"Failed to load wall image");
	ft_load_image(game, &game->collectible, "assets/images/collectible.xpm",
		"Failed to load collectible image");
	ft_load_image(game, &game->exit, "assets/images/exit.xpm",
		"Failed to load exit image");
	ft_load_image(game, &game->background, "assets/images/background.xpm",
		"Failed to load background image");
}

void	ft_init_map(t_game *game, char *map_file)
{
	t_map_error	err;
	char		*raw_data;
	t_map		*temp_map;

	raw_data = ft_read_map(map_file);
	if (!raw_data)
		ft_error_exit("Failed to read map file", game);
	temp_map = ft_parse_map_data(raw_data);
	free(raw_data);
	if (!temp_map)
		ft_error_exit("Failed to parse map data", game);
	game->map = *temp_map;
	free(temp_map);
	err = ft_validate_map(&game->map);
	if (err != MAP_OK)
		ft_error_exit(ft_map_error_to_string(err), game);
	if (!ft_valid_path(&game->map))
		ft_error_exit("The Map has no valid path.", game);
}

void	ft_init_player(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == 'P')
			{
				game->player.x = x;
				game->player.y = y;
				game->map.grid[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
	ft_error_exit("Player starting position not found", game);
}

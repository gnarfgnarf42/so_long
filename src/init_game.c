#include "so_long.h"

void	ft_init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_error_exit("Error initializing MLX", game);
	game->win = mlx_new_window(game->mlx,
			game->map->width * TILE_SIZE,
			game->map->height * TILE_SIZE,
			"so_long");
	if (!game->win)
		ft_error_exit("Error creating window", game);
}

void	ft_init_images(t_game *game)
{
	game->images.player_img = mlx_xpm_file_to_image(game->mlx,
			"assets/images/player.xpm",
			&game->images.width, &game->images.height);
	if (!game->images.player_img)
		ft_error_exit("Failed to load player image", game);
	game->images.wall = mlx_xpm_file_to_image(game->mlx,
			"assets/images/wall.xpm",
			&game->images.width, &game->images.height);
	if (!game->images.wall)
		ft_error_exit("Failed to load wall image", game);
	game->images.collectible = mlx_xpm_file_to_image(game->mlx,
			"assets/images/collectible.xpm",
			&game->images.width, &game->images.height);
	if (!game->images.collectible)
		ft_error_exit("Failed to load collectible image", game);
	game->images.exit = mlx_xpm_file_to_image(game->mlx,
			"assets/images/exit.xpm",
			&game->images.width, &game->images.height);
	if (!game->images.exit)
		ft_error_exit("Failed to load exit image", game);
	game->images.background = mlx_xpm_file_to_image(game->mlx,
			"assets/images/background.xpm",
			&game->images.width, &game->images.height);
	if (!game->images.background)
		ft_error_exit("Failed to load background image", game);
}

void	ft_init_map(t_game *game, char *map_file)
{
	game->map = ft_read_map(map_file);
	if (!game->map)
		ft_error_exit("Failed to parse map", game);
	if (!ft_validate_map(game->map))
		ft_error_exit("Invalid map", game);
}

void	ft_init_player(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (game->map->grid[y][x] == 'P')
			{
				game->player.x = x;
				game->player.y = y;
				game->map->grid[y][x] = '0'; // Replace 'P' with empty space
				return ;
			}
			x++;
		}
		y++;
	}
	ft_error_exit("Player starting position not found", game);
}
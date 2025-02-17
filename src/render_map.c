/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:09:40 by sscholz           #+#    #+#             */
/*   Updated: 2025/02/13 20:09:41 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_draw_tile(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->window, img,
		x * TILE_SIZE, y * TILE_SIZE);
}

void	ft_render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == '1')
				ft_draw_tile(game, game->wall.img, x, y);
			else if (game->map.grid[y][x] == 'C')
				ft_draw_tile(game, game->collectible.img, x, y);
			else if (game->map.grid[y][x] == 'E')
				ft_draw_tile(game, game->exit.img, x, y);
			else
				ft_draw_tile(game, game->background.img, x, y);
			x++;
		}
		y++;
	}
	ft_draw_tile(game, game->player_img.img, game->player.x, game->player.y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:26:10 by sscholz           #+#    #+#             */
/*   Updated: 2025/02/13 20:26:12 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_compute_new_position(int keycode, t_game *game,
	int *new_x, int *new_y)
{
	*new_x = game->player.x;
	*new_y = game->player.y;
	if (keycode == KEY_UP)
		*new_y = game->player.y - 1;
	else if (keycode == KEY_DOWN)
		*new_y = game->player.y + 1;
	else if (keycode == KEY_LEFT)
		*new_x = game->player.x - 1;
	else if (keycode == KEY_RIGHT)
		*new_x = game->player.x + 1;
}

int	ft_is_valid_move(t_game *game, int new_x, int new_y)
{
	if (game->map.grid[new_y][new_x] == '1')
		return (0);
	return (1);
}

void	ft_handle_collectible(t_game *game, int new_x, int new_y)
{
	if (game->map.grid[new_y][new_x] == 'C')
	{
		game->map.grid[new_y][new_x] = '0';
		game->map.collectibles = game->map.collectibles - 1;
	}
}

int	ft_handle_exit(t_game *game, int new_x, int new_y)
{
	if (game->map.grid[new_y][new_x] == 'E')
	{
		if (game->map.collectibles == 0)
		{
			ft_close_game(game);
			return (1);
		}
		else
			return (0);
	}
	return (1);
}

void	ft_update_player_position(t_game *game, int new_x, int new_y)
{
	game->player.x = new_x;
	game->player.y = new_y;
	game->player.moves = game->player.moves + 1;
}

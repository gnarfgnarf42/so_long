/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:30:04 by sscholz           #+#    #+#             */
/*   Updated: 2025/02/14 20:30:05 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_destroy_images(t_game *game)
{
	if (game->wall.img)
		mlx_destroy_image(game->mlx, game->wall.img);
	if (game->collectible.img)
		mlx_destroy_image(game->mlx, game->collectible.img);
	if (game->exit.img)
		mlx_destroy_image(game->mlx, game->exit.img);
	if (game->player_img.img)
		mlx_destroy_image(game->mlx, game->player_img.img);
	if (game->background.img)
		mlx_destroy_image(game->mlx, game->background.img);
}

static void	ft_free_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.grid)
	{
		while (game->map.grid[i])
		{
			free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
	}
}

int	ft_close_game(t_game *game)
{
	ft_destroy_images(game);
	ft_free_map(game);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	exit(0);
	return (0);
}

void	ft_error_exit(const char *msg, t_game *game)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	ft_destroy_images(game);
	ft_free_map(game);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	exit(1);
}

const char	*ft_map_error_to_string(t_map_error error)
{
	if (error == MAP_ERR_RECTANGULAR)
		return ("The Map is not rectangular.");
	else if (error == MAP_ERR_CLOSED)
		return ("The Map is not closed.");
	else if (error == MAP_ERR_INVALID_ENTITIES)
		return ("Not exactly one starting position and one exit.");
	else if (error == MAP_ERR_NO_COLLECTIBLE)
		return ("The Map has no collectibles.");
	else if (error == MAP_ERR_NO_VALID_PATH)
		return ("The Map has no valid path.");
	return ("Unknown map error.");
}

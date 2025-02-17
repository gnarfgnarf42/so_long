/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:03:44 by sscholz           #+#    #+#             */
/*   Updated: 2025/02/17 15:03:55 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (!ft_arg_check(argc, argv))
		return (1);
	if (ft_init_game(&game, argv[1]) != 0)
	{
		write(2, "Error\nFailed to initialize game\n", 34);
		return (1);
	}
	ft_render_map(&game);
	mlx_hook(game.window, 2, 1L << 0, ft_key_press, &game);
	mlx_hook(game.window, 17, 1L << 17, ft_close_game, &game);
	mlx_loop(game.mlx);
	return (0);
}

int	ft_init_game(t_game *game, char *map_file)
{
	ft_bzero(game, sizeof(t_game));
	ft_init_map(game, map_file);
	ft_init_window(game);
	ft_init_images(game);
	ft_init_player(game);
	return (0);
}

void	ft_flood_fill(t_map *m, int x, int y)
{
	if (x < 0 || x >= m->width || y < 0 || y >= m->height)
		return ;
	if (m->grid[y][x] == '1' || m->grid[y][x] == 'F')
		return ;
	m->grid[y][x] = 'F';
	ft_flood_fill(m, x + 1, y);
	ft_flood_fill(m, x - 1, y);
	ft_flood_fill(m, x, y + 1);
	ft_flood_fill(m, x, y - 1);
}

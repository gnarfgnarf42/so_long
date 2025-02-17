/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:29:17 by sscholz           #+#    #+#             */
/*   Updated: 2025/02/14 20:29:22 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_display_move_count(t_game *game)
{
	char	*move_str;

	move_str = ft_itoa(game->player.moves);
	if (!move_str)
		return ;
	write(1, "Moves: ", 7);
	write(1, move_str, ft_strlen(move_str));
	write(1, "\n", 1);
	free(move_str);
}

int	ft_key_press(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	if (keycode == KEY_ESC)
		ft_close_game(game);
	ft_compute_new_position(keycode, game, &new_x, &new_y);
	if (new_x == game->player.x && new_y == game->player.y)
		return (0);
	if (!ft_is_valid_move(game, new_x, new_y))
		return (0);
	ft_handle_collectible(game, new_x, new_y);
	if (!ft_handle_exit(game, new_x, new_y))
		return (0);
	ft_update_player_position(game, new_x, new_y);
	ft_display_move_count(game);
	ft_render_map(game);
	return (0);
}

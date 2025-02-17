/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:26:48 by sscholz           #+#    #+#             */
/*   Updated: 2025/02/13 17:26:51 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include "libft.h"

# define TILE_SIZE 64

# define KEY_UP 119
# define KEY_LEFT 97
# define KEY_DOWN 115
# define KEY_RIGHT 100
# define KEY_ESC 65307

typedef struct s_point {
	int		x;
	int		y;
}	t_point;
typedef struct s_image
{
	void	*img;
	int		width;
	int		height;
}	t_image;

typedef struct s_player
{
	int		x;
	int		y;
	int		moves;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_map		map;
	t_player	player;
	t_image		wall;
	t_image		collectible;
	t_image		exit;
	t_image		player_img;
	t_image		background;
}	t_game;

typedef enum e_map_error
{
	MAP_OK = 0,
	MAP_ERR_RECTANGULAR,
	MAP_ERR_CLOSED,
	MAP_ERR_INVALID_ENTITIES,
	MAP_ERR_NO_COLLECTIBLE,
	MAP_ERR_NO_VALID_PATH
}	t_map_error;

//so_long.c
int			main(int argc, char **argv);
int			ft_init_game(t_game *game, char *map_file);
void		ft_flood_fill(t_map *m, int x, int y);

//end_game.c
int			ft_close_game(t_game *game);
void		ft_error_exit(const char *msg, t_game *game);
const char	*ft_map_error_to_string(t_map_error error);

//file_io.c
int			ft_arg_check(int argc, char **argv);
char		*ft_read_map(const char *map_file);

//handle_input.c
void		ft_compute_new_position(int keycode, t_game *game,
				int *new_x, int *new_y);
int			ft_is_valid_move(t_game *game, int new_x, int new_y);
void		ft_handle_collectible(t_game *game, int new_x, int new_y);
int			ft_handle_exit(t_game *game, int new_x, int new_y);
void		ft_update_player_position(t_game *game, int new_x, int new_y);

//init_game.c
void		ft_init_window(t_game *game);
void		ft_init_images(t_game *game);
void		ft_init_map(t_game *game, char *map_file);
void		ft_init_player(t_game *game);

//key_hooks.c
int			ft_key_press(int keycode, t_game *game);

//parse_map.c
t_map		*ft_parse_map_data(char *raw_data);
int			ft_validate_map(t_map *m);

//render_map.c
void		ft_render_map(t_game *game);

//valid_path.c
int			ft_valid_path(t_map *m);

#endif

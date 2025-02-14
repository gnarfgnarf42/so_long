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
	int		x;	   // Player's current x position on the map
	int		y;	   // Player's current y position on the map
	int		moves; // Total moves made by the player
}	t_player;

typedef struct s_map
{
	char	**grid;	  // 2D array representing the map layout
	int		width;		  // Map width (number of columns)
	int		height;		  // Map height (number of rows)
	int		collectibles; // Count of collectibles to be picked
}	t_map;

typedef struct s_game
{
	void *mlx;			 // Pointer to the MiniLibX instance
	void *window;		 // Pointer to the game window
	t_map map;			 // Struct holding map data
	t_player player;	 // Struct holding player data
	t_image wall;		 // Image struct for wall texture
	t_image collectible; // Image struct for collectible texture
	t_image exit;		 // Image struct for exit texture
	t_image player_img;	 // Image struct for player texture
	t_image background;	 // Image struct for background texture
}	t_game;

t_game	*init_game(char *map_file);
void	init_window(t_game *game);
void	init_player(t_game *game);
void	init_map(t_game *game, char *map_file);
void	init_images(t_game *game);
void	init_window(t_game *game);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:32:41 by sscholz           #+#    #+#             */
/*   Updated: 2025/02/12 20:32:42 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Duplicates the grid. Returns NULL on error.
static char	**copy_grid(t_map *m)
{
	char	**cp;
	int		i;

	cp = malloc(sizeof(char *) * (m->height + 1));
	if (cp == NULL)
		return (NULL);
	i = 0;
	while (i < m->height)
	{
		cp[i] = ft_strdup(m->grid[i]);
		if (cp[i] == NULL)
		{
			while (i > 0)
			{
				i--;
				free(cp[i]);
			}
			free(cp);
			return (NULL);
		}
		i++;
	}
	cp[i] = NULL;
	return (cp);
}

// Searches for the player's position in the grid.
// px and py are set to the coordinates if found; otherwise, they remain -1.
static void	find_player(char **cp, int height, int width,
	int *px, int *py)
{
	int	i;
	int	j;

	i = 0;
	*px = -1;
	*py = -1;
	while (i < height && *px == -1)
	{
		j = 0;
		while (j < width && *px == -1)
		{
			if (cp[i][j] == 'P')
			{
				*px = j;
				*py = i;
			}
			j++;
		}
		i++;
	}
}

// Checks for remaining 'C' or 'E' characters in the grid.
// Returns 1 if none remain (all are reachable), 0 otherwise.
static int	check_remaining(char **cp, int height, int width)
{
	int	i;
	int	j;
	int	valid;

	valid = 1;
	i = 0;
	while (i < height && valid)
	{
		j = 0;
		while (j < width && valid)
		{
			if (cp[i][j] == 'C' || cp[i][j] == 'E')
				valid = 0;
			j++;
		}
		i++;
	}
	return (valid);
}

// Frees the duplicated grid.
static void	free_copy_grid(char **cp, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(cp[i]);
		i++;
	}
	free(cp);
}

// Main valid_path function that uses the above helpers.
static int	valid_path(t_map *m)
{
	char	**cp;
	int		px;
	int		py;
	int		valid;

	cp = copy_grid(m);
	if (cp == NULL)
		return (0);
	find_player(cp, m->height, m->width, &px, &py);
	if (px == -1)
		valid = 0;
	else
	{
		flood_fill(cp, px, py, m->height, m->width);
		valid = check_remaining(cp, m->height, m->width);
	}
	free_copy_grid(cp, m->height);
	return (valid);
}

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
static char	**ft_copy_grid(t_map *m)
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
static t_point	ft_find_player(t_map *map)
{
	t_point	p;
	int		i;
	int		j;
	char	**cp;

	cp = map->grid;
	p.x = -1;
	p.y = -1;
	i = 0;
	while (i < map->height && p.x == -1)
	{
		j = 0;
		while (j < map->width && p.x == -1)
		{
			if (cp[i][j] == 'P')
			{
				p.x = j;
				p.y = i;
			}
			j++;
		}
		i++;
	}
	return (p);
}

// Checks for remaining 'C' or 'E' characters in the grid.
// Returns 1 if none remain (all are reachable), 0 otherwise.
static int	ft_check_remaining(char **cp, int height, int width)
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
static void	ft_free_copy_grid(char **cp, int height)
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

int	ft_valid_path(t_map *m)
{
	char	**cp;
	t_map	temp;
	t_point	p;
	int		valid;

	cp = ft_copy_grid(m);
	if (cp == NULL)
		return (0);
	temp.grid = cp;
	temp.height = m->height;
	temp.width = m->width;
	p = ft_find_player(&temp);
	if (p.x == -1 || p.y == -1)
		valid = 0;
	else
	{
		ft_flood_fill(&temp, p.x, p.y);
		valid = ft_check_remaining(cp, m->height, m->width);
	}
	ft_free_copy_grid(cp, m->height);
	return (valid);
}

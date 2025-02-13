/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:29:30 by sscholz           #+#    #+#             */
/*   Updated: 2025/02/12 18:29:31 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// 1. Initializes the t_map structure from an array of lines.
static t_map	*ft_init_map_struct(char **lines)
{
	t_map	*map;

	if (!lines || !lines[0])
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->grid = lines;
	map->height = 0;
	while (lines[map->height])
		map->height++;
	map->width = ft_strlen(lines[0]);
	map->collectibles = 0;
	return (map);
}

// 2. Validates that all rows have the same length (the map is rectangular).
static int	ft_validate_row(t_map *m, int row, int *p, int *e, int *c)
{
	int	j;

	j = 0;
	while (j < m->width)
	{
		if (m->grid[row][j] != '0' &&
			m->grid[row][j] != '1' &&
			m->grid[row][j] != 'C' &&
			m->grid[row][j] != 'E' &&
			m->grid[row][j] != 'P')
			return (0);
		if ((row == 0 || row == m->height - 1 || j == 0 ||
				j == m->width - 1) && m->grid[row][j] != '1')
			return (0);
		if (m->grid[row][j] == 'P')
			*p = *p + 1;
		else if (m->grid[row][j] == 'E')
			*e = *e + 1;
		else if (m->grid[row][j] == 'C')
			*c = *c + 1;
		j++;
	}
	return (1);
}
// 3. Counts required elements: one player ('P'), one exit ('E'),
// and at least one collectible ('C').

static int	ft_validate_map(t_map *m)
{
	int		i;
	int		player;
	int		exit;
	int		collectible;
	int		row_valid;

	i = 0;
	player = 0;
	exit = 0;
	collectible = 0;
	while (i < m->height)
	{
		if (ft_strlen(m->grid[i]) != (size_t)m->width)
			return (0);
		row_valid = ft_validate_row(m, i, &player, &exit, &collectible);
		if (row_valid == 0)
			return (0);
		i++;
	}
	if (player != 1 || exit != 1 || collectible < 1)
		return (0);
	m->collectibles = collectible;
	return (1);
}

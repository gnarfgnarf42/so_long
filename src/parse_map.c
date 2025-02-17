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

static int	ft_validate_row(t_map *m, int row, int *counts)
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
		if ((row == 0 || row == m->height - 1 || j == 0
				|| j == m->width - 1) && m->grid[row][j] != '1')
			return (0);
		if (m->grid[row][j] == 'P')
			counts[0]++;
		else if (m->grid[row][j] == 'E')
			counts[1]++;
		else if (m->grid[row][j] == 'C')
			counts[2]++;
		j++;
	}
	return (1);
}

t_map	*ft_parse_map_data(char *raw_data)
{
	char	**lines;
	t_map	*map;
	int		i;

	i = 0;
	lines = ft_split(raw_data, '\n');
	if (!lines)
		return (NULL);
	map = ft_init_map_struct(lines);
	if (!map)
	{
		while (lines[i])
			free(lines[i++]);
		free(lines);
	}
	return (map);
}

int	ft_validate_map(t_map *m)
{
	int		i;
	int		counts[3];
	int		row_valid;

	i = 0;
	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	while (i < m->height)
	{
		if (ft_strlen(m->grid[i]) != (size_t)m->width)
			return (MAP_ERR_RECTANGULAR);
		row_valid = ft_validate_row(m, i, counts);
		if (row_valid == 0)
			return (MAP_ERR_CLOSED);
		i++;
	}
	if (counts[0] != 1 || counts[1] != 1)
		return (MAP_ERR_INVALID_ENTITIES);
	if (counts[2] < 1)
		return (MAP_ERR_NO_COLLECTIBLE);
	m->collectibles = counts[2];
	return (MAP_OK);
}

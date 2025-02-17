/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:30:48 by sscholz           #+#    #+#             */
/*   Updated: 2025/02/12 16:30:51 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

#define MAP_BUFFER_SIZE 1024

int	ft_arg_check(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		write(2, "Error\nInvalid number of arguments\n", 34);
		return (0);
	}
	len = ft_strlen(argv[1]);
	if (len < 4)
	{
		write(2, "Error\nFilename too short\n", 25);
		return (0);
	}
	if (ft_strncmp(argv[1] + len - 4, ".ber", 4) != 0)
	{
		write(2, "Error\nInvalid file extension. Only .ber files allowed\n", 54);
		return (0);
	}
	return (1);
}

// Helper function to read from file descriptor
static char	*ft_append_to_map(char *map_data, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(map_data, buffer);
	free(map_data);
	return (temp);
}

// Opens the file and validates the file descriptor.
static int	ft_open_valid_file(char *map_file)
{
	int		fd;
	char	dummy;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read(fd, &dummy, 0) < 0)
	{
		close(fd);
		return (-1);
	}
	return (fd);
}

// Reads the file content into a string using a while loop.
static char	*ft_read_file_to_string(int fd)
{
	char	buffer[MAP_BUFFER_SIZE + 1];
	char	*map_data;
	ssize_t	bytes_read;

	map_data = ft_strdup("");
	if (!map_data)
		return (NULL);
	bytes_read = read(fd, buffer, MAP_BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		map_data = ft_append_to_map(map_data, buffer);
		if (!map_data)
			return (NULL);
		bytes_read = read(fd, buffer, MAP_BUFFER_SIZE);
	}
	return (map_data);
}

// Orchestrator: Opens, reads, and closes the file, returning the map string.
char	*ft_read_map(const char *map_file)
{
	char	*map_data;
	int		fd;

	fd = ft_open_valid_file((char *)map_file);
	if (fd < 0)
		return (NULL);
	map_data = ft_read_file_to_string(fd);
	close(fd);
	return (map_data);
}

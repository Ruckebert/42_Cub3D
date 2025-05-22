/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcreator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:09:26 by aruckenb          #+#    #+#             */
/*   Updated: 2025/04/24 13:41:22 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft/libft.h"

int line_checker_spaces(char *line)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0')
			count++;
		i++;
	}
	if (count == 0)
		return (1);
	else
		return (0);
}

void	map_clearer(char **map, int i)
{
	free(map[i]);
	map[i] = NULL;
	int k = 0;
	while (k <= i)
	{
		free(map[k]);
		k++;
	}
	free(map);
}

int	get_map_char_len_loop(char *line, char **map, int fd, t_data *vars)
{
	int	i;
	i = 0;

	while (line[0] != '1' && line[0] != '0' && line[0] != ' ')
	{
		free(line);
		line = get_next_line(fd, vars);
		if (!line && vars->error == 1)
			return (1);
	}

	while (line)
	{
		map[i] = ft_calloc(sizeof(char), ft_strlen(line) + 1);
		if (!map[i])
		{
			while (--i >= 0)
				free(map[i]);
			return (free(map), free(line), get_next_line(-1, NULL), 1);
		}
		if (ft_strlen(line) <= 0 || line[0] == '\n' || line_checker_spaces(line) == 1)
			return (map_clearer(map, i), free(line), get_next_line(-1, NULL), 1);
		ft_strcpy(map[i], line);
		i++;
		free(line);
		line = get_next_line(fd, vars);
		if (!line && vars->error == 1)
			return (free_array(map), 1);
	}
	return (0);
}

char	**get_map_char_len(int map_size, char *str, t_data *vars)
{
	int		fd;
	char	*line;
	char	**map;

	map = ft_calloc(sizeof(char *), map_size);
	if (!map)
		return (NULL);
	fd = open(str, O_RDWR);
	if (fd == -1)
	{
		free(map);
		error_exit(vars, "Error\nOpen Error\n");
	}
	line = get_next_line(fd, vars);
	if (!line)
		return (free(map), close(fd), error_exit(vars, "Error\nGet Next Line Error\n"),  NULL);
	if (get_map_char_len_loop(line, map, fd, vars) == 1)
	{
		close(fd);
		error_exit(vars, "Error\nMap Invalid!\n");
	}
	close(fd);
	return (map);
}

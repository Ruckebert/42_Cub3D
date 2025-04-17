/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcreator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:09:26 by aruckenb          #+#    #+#             */
/*   Updated: 2025/04/17 11:49:55 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
			return (free(map), free(line), get_next_line(-1, NULL), 0);
		}
		ft_strcpy(map[i], line);
		i++;
		if (ft_strlen(line) == 1)
			return (free_array(map), 1);
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
		//We might need to use a different function since it does not free the char strings i.e. north south west east
		map_error(fd, "File Error!\n");
	}
	line = get_next_line(fd, vars);
	if (!line) //Different error handling but we will keep it for now.
		return (free(map), close(fd), NULL);
	if (get_map_char_len_loop(line, map, fd, vars) == 1)
	{
		map_error(fd, "Map Invalid\n");
	}
	close(fd);
	return (map);
}

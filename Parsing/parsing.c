/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:12:04 by aruckenb          #+#    #+#             */
/*   Updated: 2025/06/19 09:30:23 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	rgbcreator(int *type, char *line, long long i)
{
	int	red;
	int	green;
	int	blue;

	i = rgbfirst(line, i);
	if (i == -1)
		return (1);
	i = rgbloop(line, i, &red);
	if (i == -1)
		return (1);
	i = rgbloop(line, i, &green);
	if (i == -1)
		return (1);
	if (line[i] == '\n' || line[i] == '\0')
		return (1);
	blue = ft_atoi1(&line[i]);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (red >= 256 || green >= 256 || blue >= 256)
		return (free(line), 1);
	*type = (red << 16) | (green << 8) | blue;
	if (line[i] != '\0' && line[i] != '\n')
		return (free(line), 1);
	return (0);
}

void	extractc(t_data *core, char *line, int fd)
{
	if (ft_strncmp(line, "C", 1) == 0)
	{
		core->dubbot++;
		if (rgbcreator(&core->bottom, line, 1) == 1 || core->dubbot > 1)
		{
			if (core->dubbot > 1)
				free(line);
			close(fd);
			get_next_line(-1, NULL);
			error_exit(core, "Error\nRGB Incorrect Format2!\n");
		}
	}
}

int	extractf_c(t_data *core, char *line, int count, int fd)
{
	if ((ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0))
	{
		if (ft_strncmp(line, "F", 1) == 0)
		{
			core->dubtop++;
			if (rgbcreator(&core->top, line, 1) == 1 || core->dubtop > 1)
			{
				if (core->dubtop > 1)
					free(line);
				close(fd);
				get_next_line(-1, NULL);
				error_exit(core, "Error\nRGB Incorrect Format1!\n");
			}
		}
		extractc(core, line, fd);
		count--;
	}
	return (count);
}

void	textures(t_data *core, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		core->checker++;
		if (!core->north)
			core->north = ft_strdup(line);
	}
	if (ft_strncmp(line, "SO", 2) == 0)
	{
		core->checker += 2;
		if (!core->south)
			core->south = ft_strdup(line);
	}
	if (ft_strncmp(line, "WE", 2) == 0)
	{
		core->checker += 4;
		if (!core->west)
			core->west = ft_strdup(line);
	}
	if (ft_strncmp(line, "EA", 2) == 0)
	{
		core->checker += 8;
		if (!core->east)
			core->east = ft_strdup(line);
	}
}

int	getdata(char *file, t_data *core, unsigned int count)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(file, O_RDWR);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd, core);
	if (!line)
		map_error(fd, "Empty File!\n");
	while (line)
	{
		textures(core, line);
		count = extractf_c(core, line, count, fd);
		if (ft_strlen(line) == 1)
			count--;
		count++;
		free(line);
		line = get_next_line(fd, core);
		if (!line && core->error == 1)
			return (free(line), close(fd), -1);
	}
	if (count == 4)
		return (-1);
	return (close(fd), (count - 4));
}

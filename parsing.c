/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:12:04 by aruckenb          #+#    #+#             */
/*   Updated: 2025/04/23 15:12:45 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


int	rgbcreator(int *type, char *line)
{
	int i;
	i = 1;
	while (line[i] && !ft_isdigit(line[i]))
		i++;
	int red = atoi(&line[i]);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] != ',') 
		return (1);
	i++;
	int green = atoi(&line[i]);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] != ',') 
		return (1);
	i++;
	int blue = atoi(&line[i]);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	*type = (red << 16) | (green << 8) | blue;
	if (line[i] != '\0' && line[i] != '\n')
		return (free(line), 1);
	return (0);
}

int	extractF_C(t_data *core, char *line, int count,int fd)
{
	if (ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
	{
		if (ft_strncmp(line, "F", 1) == 0)
		{
			if (rgbcreator(&core->Top, line) == 1)
			{
				close(fd);
				get_next_line(-1, NULL);
				error_exit(core, "Error\nRGB Incorrect Format!\n");
			}
		}
		if (ft_strncmp(line, "C", 1) == 0)
		{
			if (rgbcreator(&core->Bottom, line) == 1)
			{
				close(fd);
				get_next_line(-1, NULL);
				error_exit(core, "Error\nRGB Incorrect Format!\n");
			}
		}
		count--;
	}
	return (count);
}

void	textures(t_data *core, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		core->North = ft_strdup(line);
	if (ft_strncmp(line, "SO", 2) == 0)
		core->South = ft_strdup(line);
	if (ft_strncmp(line, "WE", 2) == 0)
		core->West = ft_strdup(line);
	if (ft_strncmp(line, "EA", 2) == 0)
		core->East = ft_strdup(line);
}

int GetData(char *file, t_data *core)
{
	int				fd;
	unsigned int	count;
	char			*line;
	
	line = NULL;
	count = 0;
	fd = open(file, O_RDWR);
	if (fd == -1)
		exit(write(2, "Error\nInvalid File!\n", 21)); //Change this since the exit code is 1
	if (ft_strlen(file) < 5 || ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4)	!= 0 || ft_strncmp(file + ft_strlen(file) - 5, "/.cub", 5) == 0)
		map_error(fd, "Invalid File Type!\n");
	line = get_next_line(fd, core);
	if (!line)
		map_error(fd, "Empty File!\n");
	while (line)
	{
		textures(core, line);
		count = extractF_C(core, line, count, fd);
		if (ft_strlen(line) == 1)
			count--;
		count++;
		free(line);
		line = get_next_line(fd, core);
		if (!line && core->error == 1)
			return (free(line), close(fd), -1);
	}
	return (close(fd), (count - 4));
}

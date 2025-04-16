/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:12:04 by aruckenb          #+#    #+#             */
/*   Updated: 2025/04/16 14:24:20 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	rgbcreator(int *type, char *line)
{
	int i;
	i = 1;
	while (line[i] && !ft_isdigit(line[i]))
		i++;
	int red;
	red = atoi(&line[i]);
	while (line[i] && line[i] != ',')
		i++;
	i++;
	int green; 
	green = atoi(&line[i]);
	while (line[i] && line[i] != ',')
		i++;
	i++;
	int blue; 
	blue = atoi(&line[i]);
	*type = (red << 16) | (green << 8) | blue;
	i++;
	if (line[i] != '\n') //Improve this error handling but basically states that the rgb numbers have too many inputs
		write(2, "Error\n", 6);
}


int	extractF_C(t_data *core, char *line, int count)
{
	if (ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
	{
		if (ft_strncmp(line, "F", 1) == 0)
			rgbcreator(&core->Top, line);
		if (ft_strncmp(line, "C", 1) == 0)
			rgbcreator(&core->Bottom, line);
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
		exit(write(2, "Error\nInvalid File!\n", 21));
	if (ft_strlen(file) < 5 || ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4)	!= 0 || ft_strncmp(file + ft_strlen(file) - 5, "/.cub", 5) == 0)
		map_error(fd, "Invalid File Type!\n");
	line = get_next_line(fd, core);
	if (!line)
		map_error(fd, "Empty File!\n");
	while (line)
	{
		textures(core, line);
		count = extractF_C(core, line, count);
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

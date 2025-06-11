/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:55:56 by aruckenb          #+#    #+#             */
/*   Updated: 2025/06/11 11:35:29 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	clear_free(char **point)
{
	if (point && *point)
	{
		free(*point);
		*point = NULL;
	}
}

static char	*fill_buffer(int fd, char *red_buf)
{
	int		reader;
	char	*temp;
	char	*line;

	reader = 1;
	line = malloc((sizeof(char) * BUFFER_SIZE + 1));
	if (line == NULL)
		return (clear_free(&red_buf), NULL);
	while ((ft_strchr1(red_buf, '\n') == NULL) && reader > 0)
	{
		reader = read(fd, line, BUFFER_SIZE);
		if (reader == -1)
			return (clear_free(&line), clear_free(&red_buf), NULL);
		else if (reader == 0)
			break ;
		line[reader] = '\0';
		if (red_buf == NULL)
			red_buf = ft_strdup1("");
		temp = ft_strjoin1(red_buf, line);
		clear_free(&red_buf);
		if (temp == NULL)
			return (clear_free(&line), clear_free(&red_buf), NULL);
		red_buf = temp;
	}
	return (clear_free(&line), red_buf);
}

static char	*get_line(char *line, t_data *vars)
{
	int		count;
	char	*temp;

	count = 0;
	while (line[count] != '\0' && line[count] != '\n')
		count++;
	if (line[count] == '\n')
		count++;
	if (count == 0)
		return (NULL);
	temp = malloc(count + 1);
	if (temp == NULL)
	{
		vars->error = 1;
		return (NULL);
	}
	temp[count] = '\0';
	while (--count >= 0)
		temp[count] = line[count];
	return (temp);
}

static char	*line_clear(char *line)
{
	int		count;
	int		count_tmp;
	char	*temp;

	count = 0;
	count_tmp = 0;
	if (line == NULL)
		return (NULL);
	while (line[count] != '\0' && line[count] != '\n')
		count++;
	if (line[count] == '\n')
		count++;
	temp = malloc(ft_strlen1(line) - count + 1);
	if (temp == NULL)
		return (clear_free(&line), NULL);
	while (line[count] != '\0')
	{
		temp[count_tmp++] = line[count];
		count++;
	}
	temp[count_tmp] = '\0';
	clear_free(&line);
	return (temp);
}

char	*get_next_line(int fd, t_data *vars)
{
	char		*next_line;
	static char	*red_buf;

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (clear_free(&red_buf), NULL);
	red_buf = fill_buffer(fd, red_buf);
	if (red_buf == NULL)
	{
		vars->error = 1;
		return (clear_free(&red_buf), NULL);
	}
	next_line = get_line(red_buf, vars);
	if (next_line == NULL || next_line[0] == '\0')
		return (clear_free(&red_buf), clear_free(&next_line), NULL);
	red_buf = line_clear(red_buf);
	if (red_buf == NULL)
	{
		vars->error = 1;
		return (clear_free(&next_line), clear_free(&red_buf), NULL);
	}
	return (next_line);
}

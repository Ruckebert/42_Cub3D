/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:07:45 by aruckenb          #+#    #+#             */
/*   Updated: 2025/04/17 11:08:17 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	extracting_link(char **core)
{
	char *str;
	char *temp;
	str = NULL;
	str = ft_strchr(*core, ' ');
	if (str != NULL)
		str++;
	temp = ft_strdup(str);
	free(*core);
	*core = ft_strdup(temp);
	free(temp);
}

void	valid_file_checker(char *str, t_data *core)
{
	int fd;
	fd = 0;

	fd = open(str, O_RDONLY);
	if (fd == -1) //Note that this should free the elements
	{
		free_array(core->Map);
		write(2, "Error\nInvalid Texture Files!\n", 30);
		exit(2);
	}
	
}

void	AllLinkExtractor(t_data *core)
{
	extracting_link(&core->North);
	core->North[ft_strlen(core->North) - 1] = '\0';
	valid_file_checker(core->North, core);
	extracting_link(&core->South);
	core->South[ft_strlen(core->South) - 1] = '\0';
	valid_file_checker(core->South, core);
	extracting_link(&core->East);
	core->East[ft_strlen(core->East) - 1] = '\0';
	valid_file_checker(core->East, core);
	extracting_link(&core->West);
	core->West[ft_strlen(core->West) - 1] = '\0';
	valid_file_checker(core->West, core);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:57:24 by aruckenb          #+#    #+#             */
/*   Updated: 2025/04/16 15:10:21 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft/libft.h"

/*Buffer for get next_line*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20000000000
# endif

//So_Long Functions but also math.h
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_data 
{
	char	**Map;		//Full Map
	int		Top;
	int		Bottom; //This contains the rbg for the ceiling and floor

	//These char contain the file path for the images
	char	*North;
	char	*South;
	char	*East;
	char	*West;
	
	int		error;

} t_data;

/*Parsing && Map Functions*/
int		GetData(char *file, t_data *core);
char	**get_map_char_len(int map_size, char *str, t_data *vars);

/*Get_Next_Line*/
char	*get_next_line(int fd, t_data *vars);
size_t	ft_strlen1(const char *str);
char	*ft_strchr1(const char *str, int c);
char	*ft_strjoin1(char const *s1, char const *s2);
char	*ft_strdup1(const char *src);

/*Utils Function*/
void	free_array(char **example);
char	*ft_strcpy(char *dest, char *src);
void	map_error(int fd, char *str);

#endif
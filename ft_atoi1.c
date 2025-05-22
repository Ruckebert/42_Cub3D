/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:38:27 by aruckenb          #+#    #+#             */
/*   Updated: 2025/05/22 10:38:28 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_atoi1(const char *nptr)
{
	int				minus;
	unsigned long	num;
	long			n;

	n = 0;
	num = 0;
	minus = 1;
	while ((*nptr >= 9 && *nptr <= 13) || (*nptr == ' '))
		nptr++;
	if (*nptr == '-')
		minus = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		n = (n + *nptr - '0') * 10;
		num = (num + *nptr - '0') * 10;
		if ((num != (unsigned long)n) && (minus == -1))
			return (0);
		else if ((num != (unsigned long)n) && (minus == 1))
			return (-1);
		nptr++;
	}
	n /= 10;
	return ((int)(n * minus));
}

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned long	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

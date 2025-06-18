/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_wall2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:01 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/18 11:59:54 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_orthogonally_adjacent(int px, int py, int x, int y)
{
	if ((abs(px - x) == 1 && py == y) || (abs(py - y) == 1 && px == x))
		return (1);
	return (0);
}

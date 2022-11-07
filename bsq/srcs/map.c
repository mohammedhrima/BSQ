/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:03:11 by zfarini           #+#    #+#             */
/*   Updated: 2022/06/29 13:31:23 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	init_map(t_map *map)
{
	map->rows = 0;
	map->row_count = 0;
	map->col_count = 0;
	map->sum = 0;
	map->is_valid = 1;
}

void	check_line(char *line, t_map *map)
{
	while (*line)
	{
		if (*line != map->obstacle && *line != map->empty)
			map->is_valid = 0;
		line++;
	}
}

void	clean_map(t_map *map)
{
	int	i;

	if (map->rows)
	{
		i = 0;
		while (i < map->row_count)
			free(map->rows[i++]);
		free(map->rows);
	}
	free(map->sum);
}

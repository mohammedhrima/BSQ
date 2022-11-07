/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:44:57 by zfarini           #+#    #+#             */
/*   Updated: 2022/06/29 14:38:26 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int	get_sum_at(t_map *map, int i, int j)
{
	if (i < 0 || j < 0 || i >= map->row_count || j >= map->col_count)
		return (0);
	return (map->sum[i * map->col_count + j]);
}

void	find_sum(t_map *map)
{
	int	i;
	int	j;

	map->sum = malloc(map->row_count * map->col_count * sizeof(int));
	i = 0;
	while (i < map->row_count)
	{
		j = 0;
		while (j < map->col_count)
		{
			map->sum[i * map->col_count + j] = (
					map->rows[i][j] == map->obstacle);
			map->sum[i * map->col_count + j] += get_sum_at(map, i - 1, j);
			map->sum[i * map->col_count + j] += get_sum_at(map, i, j - 1);
			map->sum[i * map->col_count + j] -= get_sum_at(map, i - 1, j - 1);
			j++;
		}
		i++;
	}
}

int	is_square_valid(t_map *map, int row, int col, int length)
{
	int	obstacles_count;

	obstacles_count = get_sum_at(map, row + length - 1, col + length - 1);
	obstacles_count -= get_sum_at(map, row + length - 1, col - 1);
	obstacles_count -= get_sum_at(map, row - 1, col + length - 1);
	obstacles_count += get_sum_at(map, row - 1, col - 1);
	return (obstacles_count == 0);
}

t_solution	find_solution(t_map *map)
{
	int			i;
	int			j;
	int			k;
	t_solution	s;

	s.length = 0;
	i = 0;
	while (i < map->row_count)
	{
		j = 0;
		while (j < map->col_count)
		{
			k = s.length + 1;
			while (i + k <= map->row_count && j + k <= map->col_count
				&& is_square_valid(map, i, j, k))
			{
				s.row = i;
				s.col = j;
				s.length = k++;
			}
			j++;
		}
		i++;
	}
	return (s);
}

void	print_biggest_square(t_map *map)
{
	int			i;
	int			j;
	t_solution	s;

	find_sum(map);
	s = find_solution(map);
	i = 0;
	while (i < map->row_count)
	{
		if (i >= s.row && i < s.row + s.length)
		{
			write(1, map->rows[i], s.col);
			j = s.col;
			while (j < s.col + s.length)
			{
				write(1, &map->full, 1);
				j++;
			}
			write(1, map->rows[i] + j, map->col_count - j);
		}
		else
			write(1, map->rows[i], map->col_count);
		write(1, "\n", 1);
		i++;
	}
}

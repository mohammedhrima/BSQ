/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_next_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:35:28 by zfarini           #+#    #+#             */
/*   Updated: 2022/06/28 15:14:20 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	check_size(char **s, int *size, int i)
{
	char	*temp;

	if (i + 1 == *size)
	{
		*size *= 2;
		temp = malloc(*size);
		ft_memcpy(temp, *s, i);
		free(*s);
		*s = temp;
	}
}

char	*read_line_size(int fd, t_map *map)
{
	char	*s;
	int		bytes_read;

	s = malloc(map->col_count + 1);
	bytes_read = read(fd, s, map->col_count + 1);
	map->is_valid &= (bytes_read == map->col_count + 1
			&& s[map->col_count] == '\n');
	s[map->col_count] = 0;
	return (s);
}

char	*read_next_line(int fd, t_map	*map)
{
	char	*s;
	int		i;
	int		bytes_read;
	int		size;

	if (map->col_count)
		return (read_line_size(fd, map));
	size = 4096;
	s = malloc(size);
	i = 0;
	while (1)
	{
		bytes_read = read(fd, &s[i], 1);
		if (bytes_read < 0)
			map->is_valid = 0;
		if (bytes_read <= 0)
			break ;
		if (s[i] == '\n')
			break ;
		i++;
		check_size(&s, &size, i);
	}
	map->is_valid &= (s[i] == '\n');
	s[i] = 0;
	return (s);
}

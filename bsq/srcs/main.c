/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:41:14 by zfarini           #+#    #+#             */
/*   Updated: 2022/06/29 14:41:16 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	read_first_line(int fd, t_map *map)
{
	char	*first_line;
	int		first_line_len;
	int		i;

	first_line = read_next_line(fd, map);
	first_line_len = ft_strlen(first_line);
	if (first_line_len >= 4)
	{
		map->empty = first_line[first_line_len - 3];
		map->obstacle = first_line[first_line_len - 2];
		map->full = first_line[first_line_len - 1];
		i = 0;
		while (i < first_line_len - 3)
		{
			if (first_line[i] < '0' || first_line[i] > '9')
			{
				map->is_valid = 0;
				break ;
			}
			map->row_count = map->row_count * 10 + first_line[i++] - '0';
		}
	}
	else
		map->is_valid = 0;
	free(first_line);
}

int	check_if_map_is_valid(t_map *map)
{
	if (map->row_count <= 0)
		map->is_valid = 0;
	if (!(is_printable(map->empty) && is_printable(map->obstacle)
			&& is_printable(map->full)))
			map->is_valid = 0;
	if (map->empty == map->obstacle || map->empty == map->full
		|| map->obstacle == map->full)
		map->is_valid = 0;
	return (map->is_valid);
}

void	read_map(int fd, t_map *map)
{
	int	i;

	map->rows = malloc(map->row_count * sizeof(char *));
	map->rows[0] = read_next_line(fd, map);
	check_line(map->rows[0], map);
	map->col_count = ft_strlen(map->rows[0]);
	if (map->col_count <= 0)
			map->is_valid = 0;
	i = 1;
	while (i < map->row_count)
	{
		map->rows[i] = read_next_line(fd, map);
		check_line(map->rows[i], map);
		if (ft_strlen(map->rows[i]) != map->col_count)
			map->is_valid = 0;
		i++;
	}
	if (read(fd, &i, 1) > 0)
		map->is_valid = 0;
}

int	get_map_from_file(char *filename, t_map *map)
{
	int	fd;

	if (!filename)
		fd = 0;
	else
		fd = open(filename, O_RDONLY);
	if (fd >= 0)
	{
		read_first_line(fd, map);
		if (check_if_map_is_valid(map))
			read_map(fd, map);
		if (fd)
			close(fd);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	map;
	int		read_stdin;

	(void)argc;
	read_stdin = !(*(++argv));
	while (*argv || read_stdin)
	{
		init_map(&map);
		if (!get_map_from_file(*argv, &map) || !map.is_valid)
			write(STDERR_FILENO, "map error\n", 10);
		else
			print_biggest_square(&map);
		clean_map(&map);
		if (read_stdin)
			break ;
		if (*(argv + 1))
			write(1, "\n", 1);
		argv++;
	}
	return (0);
}

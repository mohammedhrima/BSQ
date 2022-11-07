/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarini <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:32:53 by zfarini           #+#    #+#             */
/*   Updated: 2022/06/29 14:37:59 by zfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_map {
	char	**rows;
	int		row_count;
	int		col_count;
	char	empty;
	char	obstacle;
	char	full;
	int		is_valid;
	int		*sum;
}			t_map;

typedef struct s_solution {
	int	row;
	int	col;
	int	length;
}				t_solution;

/*read_next_line.c*/
char	*read_next_line(int fd, t_map	*map);
/*utils.c*/
int		ft_strlen(char *s);
void	ft_memcpy(char *dest, char *src, int n);
int		is_printable(char c);
/*bsq.c*/
void	print_biggest_square(t_map *map);
/*map.c*/
void	init_map(t_map *map);
void	check_line(char *line, t_map *map);
void	clean_map(t_map *map);

#endif

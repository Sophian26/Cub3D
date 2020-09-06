/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 01:24:26 by amonteli          #+#    #+#             */
/*   Updated: 2020/02/19 01:16:03 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void				format_map_line(t_game *vars, int index, int items)
{
	char			*formatted_line;
	int				count;
	int				formatted_index;

	count = 0;
	formatted_index = 0;
	if (!(formatted_line = ft_calloc(items + 1, sizeof(char))))
		exit_programs(vars, "Failed to create formatted line!");
	while (vars->map[index][count])
	{
		if (vars->map[index][count] != ' ')
			formatted_line[formatted_index++] = vars->map[index][count];
		count++;
	}
	free(vars->map[index]);
	vars->map[index] = formatted_line;
}

void				check_map_line(t_game *vars, char *line, int size)
{
	int				items;
	int				i;

	items = 0;
	i = 0;
	while (line[i])
	{
		if (!ft_strchr(MAP_FLAGS, line[i]))
			exit_programs(vars, "Invalid char in map!");
		if (line[i] != ' ')
			items++;
		i++;
	}
	if (items != size)
		exit_programs(vars, "Map is not rectangular!");
	if (line[i - 1] != '1')
		exit_programs(vars, "Map not closed at right!");
}

void				check_map(t_game *vars)
{
	int				index;
	int				walls;

	index = 0;
	walls = 0;
	while (vars->map[0][index])
	{
		if (vars->map[0][index] != '1' && vars->map[0][index] != ' ')
			exit_programs(vars, "Invalid map (TOP)");
		if (vars->map[0][index] == '1')
			walls++;
		index++;
	}
	if (vars->map[0][index - 1] != '1')
		exit_programs(vars, "Line not ending with a walls!");
	index = 0;
	while (vars->map[index])
	{
		check_map_line(vars, vars->map[index], walls);
		format_map_line(vars, index, walls);
		index++;
	}
}

void				assign_map(t_game *vars, int fd, char *line)
{
	int			ret;

	vars->map_buf = ft_strjoin_free(line, "\n", 1);
	while ((ret = get_next_line(fd, &line)))
	{
		line = ft_strjoin_free(line, "\n", 1);
		vars->map_buf = ft_strjoin_free(vars->map_buf, line, 2);
		free(line);
	}
	vars->map = ft_split(vars->map_buf, '\n');
	if (!vars->map)
		exit_programs(vars, "Failed to read map.");
	free(vars->map_buf);
}

void				read_map(t_game *vars, int fd)
{
	int		ret;
	char	*line;

	while ((ret = get_next_line(fd, &line)))
	{
		if (*line == ' ')
			while (*line)
				*line == ' ' ? line++ :
				exit_programs(vars, "Spaces not at good place!");
		if (*line != '1')
		{
			free(line);
			exit_programs(vars, "Map left not closed!");
		}
		if (*line == '1')
			break ;
	}
	if (ret == -1)
		exit_programs(vars, "Failed to read map.");
	assign_map(vars, fd, line);
}
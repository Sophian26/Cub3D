/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 02:04:59 by amonteli          #+#    #+#             */
/*   Updated: 2020/02/17 00:54:26 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void			raycast_init_values(t_game *vars)
{
	vars->cameraX = 2 * vars->x / (float)vars->width - 1;
	vars->raydirX = vars->dirX + vars->planeX * vars->cameraX;
	vars->raydirY = vars->dirY + vars->planeY * vars->cameraX;
	vars->mapX = (int)vars->posX;
	vars->mapY = (int)vars->posY;
	vars->deltadistX = ft_fabs(1 / vars->raydirX);
	vars->deltadistY = ft_fabs(1 / vars->raydirY);
	vars->hit = 0;
}

void			get_steps(t_game *vars)
{
	if (vars->raydirX < 0)
	{
		vars->stepX = -1;
		vars->sidedistX = (vars->posX - vars->mapX) * vars->deltadistX;
	}
	else
	{
		vars->stepX = 1;
		vars->sidedistX = (vars->mapX + 1.0 - vars->posX) * vars->deltadistX;
	}
	if (vars->raydirY < 0)
	{
		vars->stepY = -1;
		vars->sidedistY = (vars->posY - vars->mapY) * vars->deltadistY;
	}
	else
	{
		vars->stepY = 1;
		vars->sidedistY = (vars->mapY + 1.0 - vars->posY) * vars->deltadistY;
	}
}

void			perform_dda(t_game *vars)
{
	while (!vars->hit)
	{
		if (vars->sidedistX < vars->sidedistY)
		{
			vars->sidedistX += vars->deltadistX;
			vars->mapX += vars->stepX;
			vars->side = 0;
		}
		else
		{
			vars->sidedistY += vars->deltadistY;
			vars->mapY += vars->stepY;
			vars->side = 2;
		}
		if (vars->map[vars->mapY][vars->mapX] == '1')
			vars->hit = 1;
		if (vars->side == 0)
		{
			if (vars->mapX < vars->posX)
				vars->side = 1;
		}
		else
		{
			if (vars->mapY < vars->posY)
				vars->side = 3;
		}
	}
}

void			set_pixels(t_game *vars)
{
	int			i;
	int			color;

	i = 0;
	color = 0x0CFF00;
	if (vars->side == 1)
		color = 0xFF0000; // red
	if (vars->side == 2)
		color = 0x0012FF; // red
	if (vars->side == 3)
		color = 0x8D00FF; // red
	while (i < vars->drawstart)//add draw start
	{
		vars->img_data[i * vars->width + (int)vars->x] = color;
		i++;
	}
	while (vars->drawstart < vars->drawend)	// sol? wtf
	{
		vars->img_data[vars->drawstart * vars->width + (int)vars->x] = color;
		vars->drawstart++;
	}
	i = vars->drawend;
	while (i < vars->height - 1)
	{
		vars->img_data[i * vars->width + (int)vars->x] = color;
		i++;
	}
}

int				raycast(t_game *vars)
{
	vars->x = 0;
	vars->wall_height = vars->height / 1.35; // height of a walls
	while (vars->x < vars->width)
	{
		raycast_init_values(vars);
		get_steps(vars);
		perform_dda(vars);

		if (vars->side == 0 || vars->side == 1)
			vars->perpwalldist = (vars->mapX - vars->posX + (1 - vars->stepX) / 2) / vars->raydirX;
		else
			vars->perpwalldist = (vars->mapY - vars->posY + (1 - vars->stepY) / 2) / vars->raydirY;

		vars->lineheight = (long int)(vars->wall_height / vars->perpwalldist);

		vars->drawstart = -vars->lineheight / 2 + vars->wall_height / 2;

		if (vars->drawstart < 0)
			vars->drawstart = 0;

		vars->drawend = vars->lineheight / 2 + vars->wall_height / 2;

		if (vars->drawend >= vars->height)
			vars->drawend = vars->height - 1;
		set_pixels(vars);
		vars->x++;
	}
	mlx_clear_window(vars->mlx, vars->window);
	mlx_put_image_to_window(vars->mlx, vars->window, vars->img, 0, 0);
	return (1);
}

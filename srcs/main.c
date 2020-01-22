/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/17 05:58:07 by aplat        #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 19:44:04 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

int		main(int argc, char **argv)
{
	t_data	*data;

	if (!(data = check_error_arg(argc, argv)))
		return (0);
	render(data);
	mlx_hook(data->mlx->win_ptr, 2, 303, key_press, (void *)data);
	mlx_hook(data->mlx->win_ptr, 3, 303, key_release, (void *)data);
	mlx_hook(data->mlx->win_ptr, 17, (1L << 17), close_cross, (void *)data);
	mlx_loop_hook(data->mlx->mlx_ptr, &print_loop_image, (void *)data);
	mlx_put_image_to_window(data->mlx->mlx_ptr,
			data->mlx->win_ptr, data->mlx->img_ptr, 0, 0);
	mlx_loop(data->mlx->mlx_ptr);
	return (0);
}

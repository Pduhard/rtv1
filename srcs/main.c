/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/21 21:07:09 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/21 22:45:58 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"


int		main(int argc, char **argv)
{
	t_data	*data;

	if (!(data = init_data()))
		return (0);

	
	render(data);
	//data->fractal_fct(data);
	mlx_put_image_to_window(data->mlx->mlx_ptr,
			data->mlx->win_ptr, data->mlx->img_ptr, 0, 0);
	mlx_loop(data->mlx->mlx_ptr);
	ft_printf("i%s", argv[0]);

	(void)argc;
	return (0);
}

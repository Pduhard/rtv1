/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/21 02:10:54 by aplat        #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 11:34:41 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

t_data		*check_error_arg(int argc, char **argv)
{
	t_data	*data;

	if (NB_THREADS < 1 || NB_THREADS > 16)
	{
		ft_fdprintf(2, "Invalid thread number\n");
		return (NULL);
	}
	if (WIN_WIDTH < 400 || WIN_WIDTH > 2560 ||
		WIN_HEIGHT < 400 || WIN_HEIGHT > 1420)
	{
		ft_fdprintf(2, ERRORSIZE);
		return (NULL);
	}
	if (argc != 2)
	{
		ft_fdprintf(2, ERRORARG);
		return (NULL);
	}
	else
	{
		if (!(data = init_data(argv[1])))
			return (0);
	}
	return (data);
}

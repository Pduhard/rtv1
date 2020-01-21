/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/21 05:59:47 by aplat        #+#   ##    ##    #+#       */
/*   Updated: 2020/01/21 08:34:52 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

int		return_update(char *error, int ret)
{
	ft_fdprintf(2, error);
	return (ret);
}

int     solve_quadra(t_polynome p, float *dist, float min_dist, float max_dist)
{
	int	check;

	check = 0;
	if (p.delta > 0)
	{
		//h = sub_3vecf(cone_param->center, cone_param->tip);
		// floating point exception ???
		if (p.a == 0)
			return (0);
		p.hit_point.val[0] = (-p.b + sqrtf(p.delta)) / (2 * p.a);
		p.hit_point.val[1] = (-p.b - sqrtf(p.delta)) / (2 * p.a);
		if (p.hit_point.val[0] < *dist && p.hit_point.val[0] > min_dist && p.hit_point.val[0] < max_dist)
		{
			check = 1;
			*dist = p.hit_point.val[0];
		}
		if (p.hit_point.val[1] < *dist && p.hit_point.val[1] > min_dist && p.hit_point.val[1] < max_dist)
		{
			check = 1;
			*dist = p.hit_point.val[1];
		}
		return (check);
	}
	return (0);
}
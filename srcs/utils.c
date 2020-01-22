/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/21 05:59:47 by aplat        #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 10:08:16 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

int		return_update(char *error, int ret)
{
	ft_fdprintf(2, error);
	return (ret);
}

int		solve_quadra(t_polynome p, float *dist, float min_dist, float max_dist)
{
	int	check;

	check = 0;
	if (p.delta > 0)
	{
		if (p.a == 0)
			return (0);
		p.hit_point.val[0] = (-p.b + sqrtf(p.delta)) / (2 * p.a);
		p.hit_point.val[1] = (-p.b - sqrtf(p.delta)) / (2 * p.a);
		if (p.hit_point.val[0] < *dist && p.hit_point.val[0] > min_dist
			&& p.hit_point.val[0] < max_dist)
		{
			check = 1;
			*dist = p.hit_point.val[0];
		}
		if (p.hit_point.val[1] < *dist && p.hit_point.val[1] > min_dist
			&& p.hit_point.val[1] < max_dist)
		{
			check = 1;
			*dist = p.hit_point.val[1];
		}
		return (check);
	}
	return (0);
}

int		parse_float(char *line, int i, float *val)
{
	if (line[i] == '(')
		i++;
	*val = ft_atold(&(line[i]));
	while (line[i] && line[i] != ')')
		++i;
	if (!line[i])
		return (-1);
	return (i + 1);
}

int		parse_2vecf(char *line, int i, t_2vecf *vec)
{
	int		cpt;

	cpt = 0;
	if (line[i] == '(')
		i++;
	while (cpt < 2)
	{
		vec->val[cpt++] = ft_atold(&(line[i]));
		while (line[i] && ((line[i] != ',' && cpt < 2)
			|| (line[i] != ')' && cpt == 2)))
			++i;
		if (!line[i])
			return (-1);
		++i;
	}
	return (i);
}

int		parse_3vecf(char *line, int i, t_3vecf *vec)
{
	int		cpt;

	cpt = 0;
	if (line[i] == '(')
		i++;
	while (cpt < 3)
	{
		vec->val[cpt++] = ft_atold(&(line[i]));
		while (line[i] && ((line[i] != ',' && cpt < 3)
			|| (line[i] != ')' && cpt == 3)))
			++i;
		if (!line[i])
			return (-1);
		++i;
	}
	return (i);
}

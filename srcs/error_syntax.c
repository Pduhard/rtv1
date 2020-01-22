/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_syntax.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/21 08:35:22 by aplat        #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 10:11:08 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

int		syntax_plane(char *line, int i, t_plane *p, t_3vecf *color)
{
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_3vecf(line, i, &p->origin)) == -1)
		return (return_update(SERRORPLANE, 0));
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_3vecf(line, i, &p->normal)) == -1)
		return (return_update(SERRORPLANE, 0));
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_3vecf(line, i, color)) == -1)
		return (return_update(SERRORPLANE, 0));
	return (1);
}

int		syntax_cone(char *line, int i, t_cone *c, t_3vecf *color)
{
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_3vecf(line, i, &c->center)) == -1)
		return (return_update(SERRORCONE, 0));
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_3vecf(line, i, &c->tip)) == -1)
		return (return_update(SERRORCONE, 0));
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_float(line, i, &c->radius)) == -1)
		return (return_update(SERRORCONE, 0));
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_3vecf(line, i, color)) == -1)
		return (return_update(SERRORCONE, 0));
	return (1);
}

int		syntax_cylinder(char *line, int i, t_cylinder *c, t_3vecf *color)
{
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '(' || (i = parse_3vecf(line, i, &c->center)) == -1)
		return (return_update(SERRORCYL, 0));
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_3vecf(line, i, &c->tip)) == -1)
		return (return_update(SERRORCYL, 0));
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_float(line, i, &c->radius)) == -1)
		return (return_update(SERRORCYL, 0));
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_3vecf(line, i, color)) == -1)
		return (return_update(SERRORCYL, 0));
	return (1);
}

int		syntax_sphere(char *line, int i, t_sphere *s, t_3vecf *color)
{
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_3vecf(line, i, &s->origin)) == -1)
		return (return_update(SERRORSPHERE, 0));
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_float(line, i, &s->radius)) == -1)
		return (return_update(SERRORSPHERE, 0));
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_3vecf(line, i, color)) == -1)
		return (return_update(SERRORSPHERE, 0));
	return (1);
}

int		syntax_light(char *line, int i, t_light *l)
{
	while (ft_isspace(line[i]))
		++i;
	if (line[i++] != ')')
		return (return_update(SERRORLIGHT, 0));
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_3vecf(line, i, &l->origin)) == -1)
		return (return_update(SERRORLIGHT, 0));
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_float(line, i, &l->intensity)) == -1)
		return (return_update(SERRORLIGHT, 0));
	return (1);
}

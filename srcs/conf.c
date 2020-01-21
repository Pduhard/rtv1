/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conf.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/23 01:19:51 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/21 06:42:52 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

int		parse_scene_name(char *line, t_data *data)
{
	int	i;
	int start;

	i = 4;
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(')
		return (return_update(SERRORNAME, 0));
	if (data->scene_name)
		ft_strdel(&data->scene_name);
	start = ++i;
	while (line[i] && line[i] != ')')
		++i;
	if (line[i] != ')')
		return (return_update(SERRORNAME, 0));
	data->scene_name = ft_strsub(line, start, i - start);
	return (1);
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
		while (line[i] && ((line[i] != ',' && cpt < 2) || (line[i] != ')' && cpt == 2)))
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
		while (line[i] && ((line[i] != ',' && cpt < 3) || (line[i] != ')' && cpt == 3)))
			++i;
		if (!line[i])
			return (-1);
		++i;
	}
	return (i);
}

int		parse_camera(char *line, t_data *data)
{
	int	i;
	t_cam	*cam;

	if (!(cam = malloc(sizeof(t_cam))))
		return (0);
	i = 6;
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_3vecf(line, i, &cam->origin)) == -1)
		return (return_update(SERRORCAM, 0));
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_2vecf(line, i, &cam->rotation)) == -1)
		return (return_update(SERRORCAM, 0));
	if (data->camera)
		free(data->camera);
	data->camera = cam;
	return (1);
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

int		parse_light(char *line, t_data *data)
{
	int			i;
	t_light		*light;

	if (!(light = malloc(sizeof(t_light))))
		return (0);
	i = 5;
	while (ft_isspace(line[i]))
		++i;
	if (line[i++] != '(')
		return (return_update(SERRORLIGHT, 0));
	if (!ft_strncmp(&(line[i]), "point", 5))
	{
		light->light_type = LIGHT_POINT;
		i += 5;
	}
	else if (!ft_strncmp(&(line[i]), "ambient", 7))
	{
		light->light_type = LIGHT_AMBIENT;
		i += 7;
	}
	else if (!ft_strncmp(&(line[i]), "directional", 11))
	{
		light->light_type = LIGHT_DIRECTIONAL;	
		i += 11;
	}
	else
		return (return_update(SERRORLIGHT, 0));
	while (ft_isspace(line[i]))
		++i;
	if (line[i++] != ')')
		return (return_update(SERRORLIGHT, 0));
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_3vecf(line, i, &light->origin)) == -1)
		return (return_update(SERRORLIGHT, 0));
	while (ft_isspace(line[i]))
		++i;
	if (line[i] != '(' || (i = parse_float(line, i, &light->intensity)) == -1)
		return (return_update(SERRORLIGHT, 0));
	if (data->lights)
	{
		light->next = data->lights;
	}
	else
		light->next = NULL;
	data->lights = light;
	return (1);
}

int		parse_rt_line(char *line, t_data *data)
{
	printf("%s\n", line);
	if (!ft_strncmp(line, "name", 4))
		return (parse_scene_name(line, data));
	else if (!ft_strncmp(line, "camera", 6))
		return (parse_camera(line, data));
	else if (!ft_strncmp(line, "light", 5))
		return (parse_light(line, data));
	else if (!ft_strncmp(line, "sphere", 6))
		return (parse_sphere(line, data));
	else if (!ft_strncmp(line, "plane", 5))
		return (parse_plane(line, data));
	else if (!ft_strncmp(line, "cone", 4))
		return (parse_cone(line, data));
	else if (!ft_strncmp(line, "cylinder", 8))
		return (parse_cylinder(line, data));
	else
	{
		ft_printf("Unrecognized element: \n%s\n", line);
		return (0);
	}
	return (1);
}

int		parse_rt_conf(char *file_name, t_data *data)
{
	int		fd;
	char	*line = NULL;
	int		ret;

	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		ft_printf("%s: invalid rt_conf file\n", file_name);
		return (0);
	}
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!parse_rt_line(line, data))
		{
			ft_strdel(&line);
			return (0);
		}
		ft_strdel(&line);
	}
	if (ret == -1)
	{
		ft_printf("%s: invalid rt_conf file\n", file_name);
		return (0);
	}
	return (1);
}

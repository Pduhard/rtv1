/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conf.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/23 01:19:51 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 11:44:42 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

int		parse_scene_name(char *line, t_data *data)
{
	int		i;
	int		start;

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

int		parse_camera(char *line, t_data *data)
{
	int		i;
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

int		parse_light(char *line, t_data *data)
{
	int		i;
	t_light	*light;

	if (!(light = malloc(sizeof(t_light))))
		return (0);
	if (!(i = determine_light(line, light)))
		return (0);
	if (!(syntax_light(line, i, light)))
		return (0);
	if (data->lights)
		light->next = data->lights;
	else
		light->next = NULL;
	data->lights = light;
	return (1);
}

int		parse_rt_line(char *line, t_data *data)
{
	ft_printf("%s\n", line);
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
	char	*line;
	int		ret;

	line = NULL;
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

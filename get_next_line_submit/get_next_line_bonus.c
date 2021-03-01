/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunze <hyunze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 14:13:48 by hann              #+#    #+#             */
/*   Updated: 2020/08/30 16:07:31 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	backup_to_line(char **line,
	char **backup, char *is_newline)
{
	char	*tmp;

	if (is_newline != NULL)
	{
		*line = ft_strndup(*backup, is_newline - *backup);
		tmp = ft_strndup(is_newline + 1, ft_strlen(is_newline + 1));
		free(*backup);
		*backup = tmp;
		return (SUCCESS);
	}
	if (*backup != NULL)
	{
		*line = *backup;
		*backup = NULL;
	}
	else
		*line = ft_strndup("", 1);
	return (EOF);
}

int			get_next_line(int fd, char **line)
{
	static char	*backup[MAX_FD];
	char		buff[BUFFER_SIZE + 1];
	int			byte;
	char		*tmp;
	char		*is_newline;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (ERROR);
	while ((is_newline = ft_strchr(backup[fd], '\n')) == 0
			&& (byte = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[byte] = 0;
		tmp = (backup[fd] == NULL) ?
			ft_strndup(buff, byte) : ft_strjoin(backup[fd], buff);
		if (backup[fd] != 0)
			free(backup[fd]);
		backup[fd] = tmp;
	}
	if (byte < 0)
		return (ERROR);
	return (backup_to_line(line, &backup[fd], is_newline));
}

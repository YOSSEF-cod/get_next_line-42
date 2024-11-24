/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:21:46 by ybounite          #+#    #+#             */
/*   Updated: 2024/11/24 18:53:05 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_strchar(char *str, char c);
static char	*ft_full_buffer_line(int fd, char *buffer, char *remaider);
static char	*chack_if_newline(char *line);

static int	ft_strchar(char *str, char c)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*chack_if_newline(char *line)
{
	size_t	i;
	char	*remainder;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	remainder = ft_substr(line, i + 1, ft_strlen(line) - i - 1);
	line[i + 1] = '\0';
	if (remainder && remainder[0] == '\0')
	{
		free(remainder);
		remainder = NULL;
	}
	return (remainder);
}

static char	*ft_full_buffer_line(int fd, char *buffer, char *remaider)
{
	ssize_t	read_char;
	char	*ptr;

	while (1)
	{
		read_char = read(fd, buffer, BUFFER_SIZE);
		if (read_char == -1)
		{
			free(remaider);
			return (remaider = NULL, NULL);
		}
		else if (read_char == 0)
			break ;
		buffer[read_char] = '\0';
		if (!remaider)
			remaider = ft_strdup("");
		ptr = remaider;
		remaider = ft_strjoin(ptr, buffer);
		free(ptr);
		ptr = NULL;
		if (ft_strchar(buffer, '\n'))
			break ;
	}
	return (remaider);
}

char	*get_next_line(int fd)
{
	static char	*remainder[OPEN_MAX];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
	{
		//free(remainder);
		remainder[fd] = NULL;
		return (NULL);
	}
	buffer = malloc((BUFFER_SIZE + 1));
	if (!buffer)
		return (free(remainder[fd]), remainder[fd] = NULL, NULL);
	line = ft_full_buffer_line(fd, buffer, remainder[fd]);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (free(line), line = NULL, NULL);
	remainder[fd] = chack_if_newline(line);
	return (line);
}
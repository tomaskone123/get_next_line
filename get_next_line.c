/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkonecny <tkonecny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:47:06 by tkonecny          #+#    #+#             */
/*   Updated: 2024/06/27 17:34:35 by tkonecny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *left_chars)
{
	char	*buffer;
	int		bytes_read;

	bytes_read = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(left_chars, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		left_chars = ft_strjoin(left_chars, buffer);
	}
	free(buffer);
	return (left_chars);
}

char	*get_line(char *left_chars)
{
	int		i;
	char	*line;

	i = 0;
	if (!left_chars[i])
		return (NULL);
	while (left_chars[i] && left_chars[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (left_chars[i] && left_chars[i] != '\n')
	{
		line[i] = left_chars[i];
		i++;
	}
	if (left_chars[i] == '\n')
	{
		line[i] = left_chars[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_left_chars(char *left_chars)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (left_chars[i] && left_chars[i] != '\n')
		i++;
	if (!left_chars[i])
	{
		free(left_chars);
		return (NULL);
	}
	line = (char *)malloc(sizeof(char) * (ft_strlen(left_chars) - i + 1));
	if (!line)
		return (NULL);
	i++;
	j = 0;
	while (left_chars[i])
		line[j++] = left_chars[i++];
	line[j] = '\0';
	free(left_chars);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*left_chars;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	left_chars = ft_read(fd, left_chars);
	if (!left_chars)
		return (NULL);
	line = get_line(left_chars);
	left_chars = get_left_chars(left_chars);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*ch;

	fd = open("/nfs/homes/tkonecny/core/get_next_line/my/test.txt",
			O_RDONLY | O_RDWR);
	ch = get_next_line(fd);
	printf("%s", ch);
	ch = get_next_line(fd);
	printf("%s", ch);
	ch = get_next_line(fd);
	printf("%s", ch);
	ch = get_next_line(fd);
	printf("%s", ch);
	ch = get_next_line(fd);
	printf("%s", ch);
	ch = get_next_line(fd);
	printf("%s", ch);
	ch = get_next_line(fd);
	printf("%s", ch);
	ch = get_next_line(fd);
	printf("%s", ch);
}

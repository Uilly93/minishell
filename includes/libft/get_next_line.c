/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:33:05 by wnocchi           #+#    #+#             */
/*   Updated: 2024/05/20 11:26:12 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*join_free(char *line, char *buffer)
{
	char	*temp;

	temp = ft_strcat_malloc(line, buffer);
	if (!temp)
		return (NULL);
	if (line)
		free(line);
	return (temp);
}

char	*ft_line_cpy(char *s)
{
	int		i;
	char	*line;

	if (!s || *s == 0)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] && s[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_new_line(char *buffer)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] != 0)
		i++;
	new_line = malloc(ft_strlen_gnl(buffer) - i + 1);
	if (!new_line)
		return (NULL);
	while (buffer[i])
		new_line[j++] = buffer[i++];
	new_line[j] = '\0';
	free(buffer);
	return (new_line);
}

char	*ft_get_first_line(int fd, char *line)
{
	int				bytes;
	static char		buffer[BUFFER_SIZE + 1];

	bytes = 1;
	if (!line)
		line = ft_strdup_gnl("");
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(line);
			return (NULL);
		}
		buffer[bytes] = '\0';
		line = join_free(line, buffer);
		if (ft_strchr_gnl(buffer, '\n'))
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (((BUFFER_SIZE <= 0) || fd < 0 || read(fd, 0, 0) < 0))
		return (NULL);
	buffer = ft_get_first_line(fd, buffer);
	if (*buffer == 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = ft_line_cpy(buffer);
	if (!line)
		return (NULL);
	buffer = ft_new_line(buffer);
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	return (line);
}

/*int main(void)
{
	char *str;
	int fd = open("trip/files/empty", O_RDONLY);

	str = get_next_line(fd);
	printf("%s", str);
	//if (str)
	//	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	//if (str)
	//	free(str);
}*/

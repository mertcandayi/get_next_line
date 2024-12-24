/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medayi    <medayi@student.42istanbul>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:49:44 by medayi            #+#    #+#             */
/*   Updated: 2024/12/16 23:49:44 by medayi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (!s || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = start;
	j = 0;
	while (s[i] && j < len)
	{
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	*read_line(int fd, char *str)
{
	char	*buff;
	int		rd;

	rd = 1;
	if (!str)
	{
		str = ft_strdup("");
		if (!str)
			return (NULL);
	}
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (free(str), NULL);
	while (rd > 0 && !ft_strchr(str, '\n'))
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd < 0)
			return (free(buff), free(str), NULL);
		buff[rd] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*write_line(const char *str)
{
	char	*bf_line;
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	bf_line = malloc(sizeof(char) * (i + 2));
	if (!bf_line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		bf_line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		bf_line[i] = '\n';
		i++;
	}
	bf_line[i] = '\0';
	return (bf_line);
}

char	*re_line(char *str)
{
	char	*new_line;
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	new_line = ft_substr(str, i + 1, ft_strlen(str) - (i + 1));
	free(str);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*garbage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	garbage = read_line(fd, garbage);
	if (!garbage || !*garbage)
	{
		free(garbage);
		garbage = NULL;
		return (NULL);
	}
	line = write_line(garbage);
	garbage = re_line(garbage);
	return (line);
}

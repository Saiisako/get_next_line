/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:24:12 by skock             #+#    #+#             */
/*   Updated: 2024/11/27 12:01:12 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*str[4096];
	char			*temp;
	char			*line;
	int				bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if (!temp)
		return NULL;
	line = NULL;
	while (1)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == 0)
		{
			free (temp);
			line = NULL;
			break ;
		}
		if (bytes_read < 0)
		{
			free(temp);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		str[fd] = ft_strjoin(str[fd], temp);
		if (ft_strchr(str[fd], '\n'))
		{
			free(temp);
			break;
		}
	}
	line = ft_str_n_chr_cpy(str[fd]);
	str[fd] = ft_remove_line(str[fd], line);
	return (line);
}

// int main()
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	if (fd == -1) 
// 	{
// 		perror("Erreur lors de l'ouverture du fichier");
// 			return 1;
// 	}
// 	char *line;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:19:28 by nalfonso          #+#    #+#             */
/*   Updated: 2025/06/12 17:11:33 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/libft.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	ssize_t		bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(buffer), buffer = NULL, NULL);
	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	while (!ft_check_nl(buffer, '\n'))
	{
		bytes = read(fd, line, BUFFER_SIZE);
		if (bytes < 0)
			return (free(line), free(buffer), buffer = NULL, NULL);
		if (bytes == 0)
			break ;
		line[bytes] = '\0';
		buffer = ft_strjoin_gn(buffer, line);
	}
	free(line);
	if (!buffer)
		return (free(buffer), buffer = NULL, NULL);
	line = extract_line(buffer);
	buffer = buffer_rest(buffer);
	return (line);
}

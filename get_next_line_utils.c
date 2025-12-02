/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elwilks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:03:13 by elwilks           #+#    #+#             */
/*   Updated: 2025/11/22 12:03:15 by elwilks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_detect_new_line(char *s)
{
	int	x;

	x = 0;
	if (s == 0)
		return (0);
	while (s[x])
	{
		if (s[x] == '\n')
			return (1);
		x++;
	}
	return (0);
}

char	*ft_calloc(int count, int size)
{
	int		x;
	char	*str;

	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	x = 0;
	while (x < count * size)
		str[x++] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		l_s1;
	int		l_s2;
	int		x;
	int		y;

	x = 0;
	y = 0;
	l_s1 = ft_strlen(s1);
	l_s2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (l_s1 + l_s2 + 1));
	if (str == NULL)
		return (NULL);
	while (s1[x])
	{
		str[x] = s1[x];
		x++;
	}
	while (s2[y])
		str[x++] = s2[y++];
	str[x] = '\0';
	free (s1);
	return (str);
}

int	ft_strlen(char *s)
{
	int	x;

	x = 0;
	if (s == NULL)
		return (0);
	while (s[x])
		x++;
	return (x);
}

char	*free_str(char *s)
{
	free(s);
	return (NULL);
}

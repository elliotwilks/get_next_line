/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elwilks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:02:26 by elwilks           #+#    #+#             */
/*   Updated: 2025/11/22 12:02:29 by elwilks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

char	*get_next_line(int fd);
char	*ft_read_file(int fd, char *s);
char	*ft_get_line(char *s);
int		ft_detect_new_line(char *s);
char	*ft_calloc(int count, int size);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
char	*free_str(char *s);

#endif

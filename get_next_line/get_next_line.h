/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:24:39 by obelkhad          #+#    #+#             */
/*   Updated: 2022/07/26 09:05:01 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include<stdlib.h>
# include<fcntl.h>
# include<unistd.h>
# include "../libft/libft.h"
# define BUFFER_SIZE 42

char	*get_next_line(int fd);
size_t	check_end_of_line(char	*buf);
char	*read_and_store(int fd, char **line, char **lost);
void	ft_strsplit(char *holder, char **first, char **secend, size_t check);
void	creat_line(char **line, char **lost, char **buffer);
char	*ft_strjoin1(char **line, char **str);
void	ft_strncpy(char *dest, char *src, size_t len);
#endif
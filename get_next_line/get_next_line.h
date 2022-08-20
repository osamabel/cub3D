/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:57:31 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/19 14:23:43 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 42

//Extrnal Functions
char	*ft_strchr2(char *s, int c);
char	*ft_strjoin2(char *s1, char *s2);

//Internal Functions
char	*get_next_line(int fd);

char	*ft_read_and_save(int fd, char	*save);
char	*ft_extract_line(char	*save);
char	*ft_rm_line(char	*save);

#endif
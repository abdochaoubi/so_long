/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:48:02 by aechaoub          #+#    #+#             */
/*   Updated: 2022/12/16 19:56:42 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#define BUFFER_SIZE 6

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h> 

typedef struct	s_vars {
	void	*pht;
	char 	*adr;
	int		img_width;
	int		img_height;
	int		y;
	int		x;
	int		many;
	int		yplace;
	int		xplace;
}				t_img;

typedef struct	s_map {
	int 	**map;
	int		y;
	int		x;
	int		ystart;
	int		xstart;
	int		yend;
	int		xend;
}				t_map;


typedef struct	s_data {
	t_img gras;
	// t_img back;
	t_img small;
	t_img lol;
	t_img mywin;
	// t_img winty;
	// t_img lard;
	t_img dollar;
	t_img door;
	t_img enemy;
	t_map map;
	void	*img;
	char d[5][15];
	char enemyframe[5][15];
	
	char	*addr;
	void	*mlx;
	void	*win;
	char	**frame_coins;
	char	**frame_enemy;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		stillplay;
}				t_data;
char	*ft_itoa(int n);

char				*get_next_line(int fd);
char				*ft_strdup(const char *str);
char				*ft_substr(char *s, unsigned int start, size_t len);
char				*ft_strjoin(char *s1, char *s2);
void				ft_bzero(void *str, size_t n);
size_t				ft_strlen(const char *str);

#endif
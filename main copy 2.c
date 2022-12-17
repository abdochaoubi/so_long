#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <mlx.h>
#include "./getsky/get_next_line.h"

// typedef struct	s_vars {
// 	void	*pht;
// 	char 	*adr;
// 	int		img_width;
// 	int		img_height;
// 	int		y;
// 	int		x;
// 	int		yplace;
// 	int		xplace;
// }				t_img;

// typedef struct	s_map {
// 	int 	**map;
// 	int		y;
// 	int		x;
// 	int		ystart;
// 	int		xstart;
// 	int		yend;
// 	int		xend;
// }				t_map;


// typedef struct	s_data {
// 	t_img gras;
// 	t_img back;
// 	t_img small;
// 	t_img lol;
// 	t_img dollar;
// 	t_map map;
// 	void	*img;
// 	char	*addr;
// 	void	*mlx;
// 	void	*win;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }				t_data;

int **getrslt(void *map);


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	destroy( t_data *vars)
{
	// printf("%d  %d\n",x,y);
	write(1,"closed\n",7);
	// mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}
 
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}


void callimage(t_data img)
{
	static int frame=0;
	img.lol.pht = mlx_xpm_file_to_image(img.mlx, "rock.xpm", &img.lol.img_width, &img.lol.img_height);
	img.lol.adr = mlx_get_data_addr(img.lol.pht, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.gras.pht = mlx_xpm_file_to_image(img.mlx, "easy.xpm", &img.gras.img_width, &img.gras.img_height);
	img.gras.adr = mlx_get_data_addr(img.gras.pht, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.small.pht = mlx_xpm_file_to_image(img.mlx, "small.xpm", &img.small.img_width, &img.small.img_height);
	img.small.adr = mlx_get_data_addr(img.small.pht, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.dollar.pht = mlx_xpm_file_to_image(img.mlx, "dollar.xpm", &img.dollar.img_width, &img.dollar.img_height);
	img.dollar.adr = mlx_get_data_addr(img.dollar.pht, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.door.pht = mlx_xpm_file_to_image(img.mlx, "door.xpm", &img.door.img_width, &img.door.img_height);
	img.door.adr = mlx_get_data_addr(img.door.pht, &img.bits_per_pixel, &img.line_length, &img.endian);
	// img.lard.pht = mlx_xpm_file_to_image(img.mlx, "door.xpm", &img.lard.img_width, &img.lard.img_height);
	// img.lard.adr = mlx_get_data_addr(img.lard.pht, &img.bits_per_pixel, &img.line_length, &img.endian);

	// mlx_put_image_to_window(img.mlx, img.win, img.gras.pht, 0, 0);
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	while(j<img.map.y)
    {
        i=0;
        x=0;
        while(i<(img.map.x))
        {
            if(img.map.map[j][i]==1)
			{
	mlx_put_image_to_window(img.mlx, img.win, img.gras.pht,i*50, j*50);
				mlx_put_image_to_window(img.mlx, img.win, img.lol.pht,x, y);
			}
			else if(img.map.map[j][i]==5)
			{
	mlx_put_image_to_window(img.mlx, img.win, img.gras.pht,i*50, j*50);
				mlx_put_image_to_window(img.mlx, img.win, img.dollar.pht,x, y);
			}
			else if(img.map.map[j][i]==8)
			{
	mlx_put_image_to_window(img.mlx, img.win, img.gras.pht,i*50, j*50);
				mlx_put_image_to_window(img.mlx, img.win, img.door.pht,i*50, j*50);
			}
			else
			{
	mlx_put_image_to_window(img.mlx, img.win, img.gras.pht,i*50, j*50);
				// mlx_put_image_to_window(img.mlx, img.win, img.lard.pht,i*50, j*50);

			}
            i++;
			x+=41;
			printf("%d\n",x);
        }
            // printf("\n");
			y+=50;
        j++;

    }
	if(frame>10)
	{
	// img->small.x+=5;
	img.small.y+=5;
	}
	else{
	img.small.y-=5;
	}
	printf("%d\n",frame);
	mlx_put_image_to_window(img.mlx, img.win, img.small.pht,img.small.x, img.small.y);

	frame++;
	if(frame >20)
		frame=0;
}

int	key_hook(int keycode, t_data *vars)
{
	if(keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		destroy(vars);
	}
	if((keycode == 0 ||keycode == 1|| keycode == 2|| keycode == 13 ) && vars->stillplay )
	{
		// mlx_clear_window(vars->mlx,vars->win);
			int move =50;
		if(keycode == 0  && vars->map.map[vars->small.yplace][vars->small.xplace-1] !=1)
		{
			vars->small.x-=move;
			vars->small.xplace-=1;
		}
		if(keycode == 1 && vars->map.map[vars->small.yplace+1][vars->small.xplace] !=1){
			vars->small.y+=move;
			vars->small.yplace+=1;
			}
		if(keycode == 2 && vars->map.map[vars->small.yplace][vars->small.xplace+1] !=1){
			vars->small.x+=move;
			vars->small.xplace+=1;
		}
		if(keycode == 13 && vars->map.map[vars->small.yplace-1][vars->small.xplace] !=1 ){
			vars->small.y-=move;	
			vars->small.yplace-=1;
		}
			if(vars->map.map[vars->small.yplace][vars->small.xplace] ==5)
			{
				vars->door.many-=1;
				vars->map.map[vars->small.yplace][vars->small.xplace] =0;
			}
			if(vars->map.map[vars->small.yplace][vars->small.xplace] ==8 && vars->door.many==0)
			{
				vars->stillplay=0;
				printf("youuu winn");
			}
		// callimage(*vars);
		// mlx_put_image_to_window(vars->mlx, vars->win, vars->small.pht,vars->small.x, vars->small.y);

	}
				printf("stillplay = %d\n",vars->stillplay);
	printf("Hello from key_hook!  %d   %d \n",keycode,vars->door.many);
	return (0);
}


int render_next_frame(t_data *img)
{
	static int ds=1;
	if(ds%100000)
	{
	img->small.x+=1;
	img->small.y+=1;

	}
		mlx_put_image_to_window(img->mlx, img->win, img->small.pht,img->small.x, img->small.y);
		ds++;
		// mlx_put_image_to_window(img.mlx, img.win, img.small.pht,img.small.x, img.small.y);
		return 0;

}



int	main(void)
{
	
	t_data	img;
	// printf("%d %d \n",img.map.x,img.map.y);
	int **map=getrslt(&img);
	// printf("%d %d \n",img.map.x,img.map.y);
	int i=0;
	int j=0;
    while(j<img.map.y)
    {
        i=0;
        while(i<img.map.x)
        {
            printf("%d",map[j][i]);
            i++;
        }
            printf("\n");
        j++;

    }

	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, img.map.x*50, img.map.y*50, "Hello world!");
	img.stillplay=1;
	// img.img = mlx_new_image(img.mlx, 1900, 1050);
	img.small.x=img.map.xstart*50;
	img.small.y=img.map.ystart*50;
	img.small.xplace=img.map.xstart;
	img.small.yplace=img.map.ystart;
	img.dollar.many=0;
	img.map.map=map;
	img.gras.pht = mlx_xpm_file_to_image(img.mlx, "back98.xpm", &img.gras.img_width, &img.gras.img_height);
	img.gras.adr = mlx_get_data_addr(img.gras.pht, &img.bits_per_pixel, &img.line_length, &img.endian);
	callimage(img);
	// mlx_key_hook(img.win, key_hook, &img);
	// mlx_loop_hook(img.mlx, render_next_frame, &img);

	mlx_hook(img.win, 2, 1L<<0, key_hook, &img);

	
	mlx_loop(img.mlx);
}
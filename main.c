#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "mlx/mlx.h"
// #include <mlx.h>
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

int **getrslt(void *map,char *av);


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	destroy( )
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
char	**ft_split(char const *s, char c);


void callimage(t_data *img)
{
	// char d[7][12]={"frame_0.xpm","frame_1.xpm","frame_2.xpm","frame_3.xpm","frame_4.xpm","frame_5.xpm","frame_6.xpm"};
	static int frame=0;
	img->lol.pht = mlx_xpm_file_to_image(img->mlx, "rock.xpm", &img->lol.img_width, &img->lol.img_height);
	// img->lol.adr = mlx_get_data_addr(img->lol.pht, &img->bits_per_pixel, &img->line_length, &img->endian);
	// img->gras.pht = mlx_xpm_file_to_image(img->mlx, "back98.xpm", &img->gras.img_width, &img->gras.img_height);
	// img->gras.adr = mlx_get_data_addr(img->gras.pht, &img->bits_per_pixel, &img->line_length, &img->endian);
	img->small.pht = mlx_xpm_file_to_image(img->mlx, "small.xpm", &img->small.img_width, &img->small.img_height);
	// img->small.adr = mlx_get_data_addr(img->small.pht, &img->bits_per_pixel, &img->line_length, &img->endian);
	img->dollar.pht = mlx_xpm_file_to_image(img->mlx, img->frame_coins[(frame)%7], &img->dollar.img_width, &img->dollar.img_height);
	// img->dollar.adr = mlx_get_data_addr(img->dollar.pht, &img->bits_per_pixel, &img->line_length, &img->endian);
	img->enemy.pht = mlx_xpm_file_to_image(img->mlx, img->frame_enemy[(frame)%4], &img->enemy.img_width, &img->enemy.img_height);
	// img->enemy.adr = mlx_get_data_addr(img->enemy.pht, &img->bits_per_pixel, &img->line_length, &img->endian);
	img->door.pht = mlx_xpm_file_to_image(img->mlx, "door.xpm", &img->door.img_width, &img->door.img_height);
	// img->door.adr = mlx_get_data_addr(img->door.pht, &img->bits_per_pixel, &img->line_length, &img->endian);
	img->mywin.pht = mlx_xpm_file_to_image(img->mlx, "youwin.xpm", &img->mywin.img_width, &img->mywin.img_height);
	// img->mylose.pht = mlx_xpm_file_to_image(img->mlx, "youwin.xpm", &img->mywin.img_width, &img->mywin.img_height);
	// img->mywin.adr = mlx_get_data_addr(img->mywin.pht, &img->bits_per_pixel, &img->line_length, &img->endian);

	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	mlx_put_image_to_window(img->mlx, img->win, img->gras.pht, 0, 0);
	while(j<img->map.y)
    {
        x=0;
        i=0;
        while(i<img->map.x)
        {
            if(img->map.map[j][i]==1)
			{
				mlx_put_image_to_window(img->mlx, img->win, img->lol.pht,x, y);
			}
			if(img->map.map[j][i]==5)
			{
				mlx_put_image_to_window(img->mlx, img->win, img->dollar.pht,x, y);
			}
			if(img->map.map[j][i]==8)
			{
				mlx_put_image_to_window(img->mlx, img->win, img->door.pht,i*50, j*50);
			}
			if(img->map.map[j][i]==3)
			{
				mlx_put_image_to_window(img->mlx, img->win, img->enemy.pht,x, y);
				// mlx_put_image_to_window(img->mlx, img->win, img->door.pht,i*50, j*50);
			}
            i++;
			x+=50;
        }
            // printf("%d\n",y);
			y+=50;
        j++;
    }
	char *k=ft_itoa(img->small.many);
	char *e=ft_strjoin(ft_strdup("Moves : "),k);
	mlx_string_put(img->mlx,img->win,20,(j+1)*50 -25,0,e);
	free(e);
	free(k);
	k=ft_itoa(img->door.many);
	e=ft_strjoin(ft_strdup("Coins : "),k);
	mlx_string_put(img->mlx,img->win,(i-1)*50-49,(j+1)*50 -25,0,e);
	free(e);
	free(k);
	if(img->enemy.xplace==img->small.xplace && img->enemy.yplace==img->small.yplace)
	{
		img->stillplay=-1;
		printf("you lose\n");
		int i=0;
		int j=0;
		while(j<img->map.y)
		{
			// i=0;
			// while(i<img->map.x)
			// {
				printf("%p\n",img->map.map[j]);
				free(img->map.map[j]);
			// 	i++;
			// }
				// printf("\n");
			j++;
		}
		free(img->map.map);
		free(img->frame_enemy);
		free(img->frame_enemy);
		return ;
	}
	if(img->stillplay==0)
	{
		mlx_put_image_to_window(img->mlx, img->win, img->mywin.pht,img->map.x*25 -150, img->map.y*25 -150);
	}
	// if(frame%2==0)
	// {
	// // img->small.x+=5;
	// img->small.y+=5;
	// }
	// else{
	// img->small.y-=5;
	// }
	// printf("%d\n",frame);
	mlx_put_image_to_window(img->mlx, img->win, img->small.pht,img->small.x, img->small.y);

	frame++;
	if(frame >25)
		frame=0;
}

int	key_hook(int keycode, t_data *vars)
{
	if(keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		destroy();
	}
	if((keycode == 0 ||keycode == 1|| keycode == 2|| keycode == 13 ) && vars->stillplay>0  )
	{
		int move =50;
		if(keycode == 0  && vars->map.map[vars->small.yplace][vars->small.xplace-1] !=1)
		{
			vars->small.x-=move;
			vars->small.xplace-=1;
			vars->small.many++;
		}
		if(keycode == 1 && vars->map.map[vars->small.yplace+1][vars->small.xplace] !=1){
			vars->small.y+=move;
			vars->small.yplace+=1;
			vars->small.many++;
			}
		if(keycode == 2 && vars->map.map[vars->small.yplace][vars->small.xplace+1] !=1){
			vars->small.many++;
			vars->small.x+=move;
			vars->small.xplace+=1;
		}
		if(keycode == 13 && vars->map.map[vars->small.yplace-1][vars->small.xplace] !=1 ){
			vars->small.many++;
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
			callimage(vars);
			printf("youuu win\n");
		}
		// callimage(*vars);
		// mlx_put_image_to_window(vars->mlx, vars->win, vars->small.pht,vars->small.x, vars->small.y);

	}
	printf("Hello from key_hook!  %d   %d \n",keycode,vars->door.many);
	return (0);
}

// void changee_enemy(t_data *img,int nb)
// {
// 	static int p=0;

// 	if(img->map.map[img->enemy.yplace][img->enemy.xplace]==3)
// 	{
// 	printf("p is  %d\n",(nb+p)%4);
// 		if(img->map.map[img->enemy.yplace][img->enemy.xplace-1]!=1 && (nb-p+img->enemy.xplace-img->enemy.yplace)%4==0)
// 		{
// 			img->map.map[img->enemy.yplace][img->enemy.xplace]=0;
// 			img->map.map[img->enemy.yplace][img->enemy.xplace-1]=3;
// 			img->enemy.xplace--;
// 			p++;
// 			return;
// 		}
// 		if(img->map.map[img->enemy.yplace][img->enemy.xplace+1]!=1 && (nb+p+img->enemy.xplace+img->enemy.yplace)%4==1)
// 		{
// 			img->map.map[img->enemy.yplace][img->enemy.xplace]=0;
// 			img->map.map[img->enemy.yplace][img->enemy.xplace+1]=3;
// 			img->enemy.xplace++;
// 			p++;
// 			return;
// 		}
// 		if(img->map.map[img->enemy.yplace+1][img->enemy.xplace]!=1 && (nb+p-img->enemy.xplace-img->enemy.yplace)%4==2)
// 		{
// 			img->map.map[img->enemy.yplace][img->enemy.xplace]=0;
// 			img->map.map[img->enemy.yplace+1][img->enemy.xplace]=3;
// 			img->enemy.yplace++;
// 			p++;
// 			return;
// 		}
// 		if(img->map.map[img->enemy.yplace-1][img->enemy.xplace]!=1 && (nb-p+img->enemy.xplace+img->enemy.yplace)%4==3)
// 		{
// 			img->map.map[img->enemy.yplace][img->enemy.xplace]=0;
// 			img->map.map[img->enemy.yplace-1][img->enemy.xplace]=3;
// 			img->enemy.yplace--;
// 			p++;
// 			return;
// 		}
// 	}
// 	p++;
// 	// if(p==0)
// 	// {
// 	// 	changee_enemy(img,0);
// 	// 	printf("damn");
// 	// }

// }


 #include <math.h>

void moveright(t_data *img,int nt);
void moveleft(t_data*img,int nt);
void moveup(t_data *img,int nt);
void movedown(t_data *img,int nt)
{
	nt++;
	if(nt>3)
		return;
	if(img->map.map[img->enemy.yplace+1][img->enemy.xplace]!=1 && img->map.map[img->enemy.yplace+1][img->enemy.xplace]!=5 && img->map.map[img->enemy.yplace+1][img->enemy.xplace]!=8)
	{
		img->map.map[img->enemy.yplace][img->enemy.xplace]=0;
		img->map.map[img->enemy.yplace+1][img->enemy.xplace]=3;
		img->enemy.yplace++;
	}
	else if(img->enemy.xplace>=img->small.xplace)
	{
		moveleft(img,nt);
			return;
	}
	else 
	{
		moveright(img,nt);
		return;
	}


}
void moveup(t_data *img,int nt)
{
	// printf("left\n");
	nt++;
	if(nt>3)
		return;
	if(img->map.map[img->enemy.yplace-1][img->enemy.xplace]!=1 && img->map.map[img->enemy.yplace-1][img->enemy.xplace]!=5 && img->map.map[img->enemy.yplace-1][img->enemy.xplace]!=8)
	{
		img->map.map[img->enemy.yplace][img->enemy.xplace]=0;
		img->map.map[img->enemy.yplace-1][img->enemy.xplace]=3;
		img->enemy.yplace--;
	}
	else if(img->enemy.xplace>=img->small.xplace)
	{
		moveleft(img,nt);
			return;
	}
	else 
	{
		moveright(img,nt);
		return;
	}
}
void moveleft(t_data *img,int nt)
{
	// printf("suu\n");
	nt++;
	if(nt>3)
		return;
	if(img->map.map[img->enemy.yplace][img->enemy.xplace-1]!=1 && img->map.map[img->enemy.yplace][img->enemy.xplace-1]!=5&& img->map.map[img->enemy.yplace][img->enemy.xplace-1]!=8)
	{
		img->map.map[img->enemy.yplace][img->enemy.xplace]=0;
		img->map.map[img->enemy.yplace][img->enemy.xplace-1]=3;
		img->enemy.xplace--;
		// p++;
	}
	else if(img->enemy.yplace<=img->small.yplace)
		{
			movedown(img,nt);
			return;
		}
		else 
		{
			moveup(img,nt);
			return;
		}
}
void moveright(t_data *img,int nt)
{
	// printf("left\n");
	nt++;
	if(nt>3)
		return;
	if(img->map.map[img->enemy.yplace][img->enemy.xplace+1]!=1 && img->map.map[img->enemy.yplace][img->enemy.xplace+1]!=5&& img->map.map[img->enemy.yplace][img->enemy.xplace+1]!=8)
	{
		img->map.map[img->enemy.yplace][img->enemy.xplace]=0;
		img->map.map[img->enemy.yplace][img->enemy.xplace+1]=3;
		img->enemy.xplace++;
	}
	else if(img->enemy.yplace<=img->small.yplace)
		{
			movedown(img,nt);
			return;
		}
		else 
		{
			moveup(img,nt);
			return;
		}
}



void changee_enemy(t_data *img)
{
	// printf("%d  %d   vs  %d   %d \n",img->enemy.xplace,img->enemy.yplace,img->small.xplace,img->small.yplace);
	// printf("%d\n",abs(img->small.xplace-img->small.yplace));
	if(abs(img->enemy.xplace-img->small.xplace)>abs(img->enemy.yplace-img->small.yplace) )
	{
		if(img->enemy.xplace>=img->small.xplace)
		{
			moveleft(img,0);
				return;
		}
		else 
		{
			moveright(img,0);
			return;
		}
	}
	else 
	{
		if(img->enemy.yplace<=img->small.yplace)
		{
			movedown(img,0);
			return;
		}
		else 
		{
			moveup(img,0);
			return;
		}
	}
}

int render_next_frame(t_data *img)
{
	static int ds=1;
	static int sa=3;
	if(img->stillplay<=0)
		return 0;
	// printf("up ==> %d  %d \n",img->stillplay,ds);
	if(img->enemy.xplace>0 && sa % 2300 == 0)
	{
	// img->small.x+=3;
	// img->small.y-=3;
	// callimage(*img);
		changee_enemy(img);
	}
	if(ds%2000 ==0)
	{
	img->small.x+=3;
	img->small.y-=3;
	// callimage(img);
	}
	else if(ds%2000 ==1000)
	{
	img->small.x-=3;
	img->small.y+=3;
	// callimage(img);
	}
	 if(ds%1000 ==0)
	{
		callimage(img);
	// printf("%d\n",img->door.many);
	}
		// mlx_put_image_to_window(img->mlx, img->win, img->small.pht,img->small.x, img->small.y);
	if(ds >100000)
		ds =0;
	if(sa >9000)
		sa =0;
	ds++;
	// sa++;
	sa++;
		// mlx_put_image_to_window(img.mlx, img.win, img.small.pht,img.small.x, img.small.y);
		return 0;

}



int	main(int ac,char **av)
{
	if(ac!=2)
		return 0;
	t_data	img;
	// int *wdwd=malloc(125);
	// wdwd[0]=9;
	// printf("%d %d \n",img.map.x,img.map.y);
	img.frame_enemy=ft_split("enemy_3.xpm|enemy_4.xpm|enemy_5.xpm|enemy_6.xpm",'|');
	img.frame_coins=ft_split("frame_0.xpm|frame_1.xpm|frame_2.xpm|frame_3.xpm|frame_4.xpm|frame_5.xpm|frame_6.xpm",'|');
	img.door.many=0;
	img.enemy.xplace=-1;
	int **map=getrslt(&img,av[1]);
	if(!map)
		return 0;
	// printf("%d %d \n",img.map.x,img.map.y);
	int i=0;
	int j=0;
    while(j<img.map.y)
    {
        // i=0;
        // while(i<img.map.x)
        // {
            printf("%p",map[j]);
            // i++;
        // }
            printf("\n");
        j++;
    }
	img.small.x=img.map.xstart*50;
	img.small.y=img.map.ystart*50;
	img.small.xplace=img.map.xstart;
	img.small.yplace=img.map.ystart;
	img.dollar.many=0;
	img.small.many=0;
	img.map.map=map;
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, (img.map.x)*50, (img.map.y+1)*50, "Hello world!");
	img.stillplay=1;
	img.mywin.pht = mlx_xpm_file_to_image(img.mlx, "youwin.xpm", &img.mywin.img_width, &img.mywin.img_height);
	img.gras.pht = mlx_xpm_file_to_image(img.mlx, "back98.xpm", &img.gras.img_width, &img.gras.img_height);
	// img.gras.adr = mlx_get_data_addr(img.gras.pht, &img.bits_per_pixel, &img.line_length, &img.endian);
	// mlx_put_image_to_window(img.mlx, img.win, img.gras.pht, 0, 0);
	callimage(&img);
		// mlx_key_hook(img.win, key_hook, &img);
		mlx_loop_hook(img.mlx, render_next_frame, &img);
		mlx_hook(img.win, 2, 0, key_hook, &img);
		mlx_hook(img.win, 17, 0, destroy, &img);
	
	// mlx_put_image_to_window(img.mlx, img.win, img.small.pht,img.small.x, img.small.y);
	// mlx_put_image_to_window(img->mlx, img->win, img->small.pht,img->small.x, img->small.y);


	
	mlx_loop(img.mlx);
}
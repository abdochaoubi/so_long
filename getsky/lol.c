
# include <fcntl.h> 
# include <string.h> 
# include <stdio.h> 
#include "get_next_line.h"

int checkmove(int **tab,int x,int y)
{
    int i =0;
    int j =0;

    while(j<y)
    {
        i=0;
        while(i<x)
        {
            if(tab[j][i]==7)
                return 1;
            i++;
        }
        j++;
    }
    j=0;
    while(j<y)
    {
        i=0;
        while(i<x)
        {
            if(tab[j][i]==9)
            {
                if(tab[j+1][i]==0||tab[j-1][i]==0||tab[j][i+1]==0||tab[j][i-1]==0)
                    return 1;
                if(tab[j+1][i]==5||tab[j-1][i]==5||tab[j][i+1]==5||tab[j][i-1]==5)
                    return 1;
                if(tab[j+1][i]==8||tab[j-1][i]==8||tab[j][i+1]==8||tab[j][i-1]==8)
                    return 1;
            }
            i++;
        }
        j++;
    }
    return 0;


}


void planmap(int **tab,int x,int y)
{

    int i =0;
    int j =0;

    while(j<y)
    {
        i=0;
        while(i<x)
        {
            if(tab[j][i]==7)
            {
                tab[j][i]=9;
            }
            i++;
        }
        j++;
    }
    while(checkmove(tab,x,y))
    {
        i=0;
        j=0;
        while(j<y)
        {
            i=0;
            while(i<x)
            {
                if(tab[j][i]==9)
                {
                    if(tab[j+1][i]==0||tab[j+1][i]==8||tab[j+1][i]==5)
                                    tab[j+1][i]=9;
                    if(tab[j-1][i]==0||tab[j-1][i]==8||tab[j-1][i]==5)
                                    tab[j-1][i]=9;
                    if(tab[j][i+1]==0||tab[j][i+1]==8||tab[j][i+1]==5)
                                    tab[j][i+1]=9;
                    if(tab[j][i-1]==0||tab[j][i-1]==8||tab[j][i-1]==5)
                                    tab[j][i-1]=9;
                    // tab[j][i]=9;
                }
                i++;
            }
            j++;
        }
    }
}


int **getrslt(t_data *mapty,char *av)
{
    int fd = open(av,O_RDONLY);

    if(fd<0)
        return 0;
    // t_map lki = *mapty;
    int len;
    int basiclen;
    int i;
    int lines;
    int j=0;
    int **map=malloc(100*sizeof(int*));
    char *g=get_next_line(fd);
    basiclen = strlen(g);
    while(g)
    {
        len = strlen(g);
        // printf("%d vd %d\n",len, basiclen);
        if(len !=basiclen)
        {
            // free(g);
            g = get_next_line(fd);
            if(g==0 && basiclen-len ==1)
                basiclen++;
            else{
                printf("error\n");
                exit(0);}
        }
        map[j]=malloc(basiclen*8);
        i=0;
        while(i<len)
        {
            if(g[i]=='1')
                map[j][i]=1;
            if(g[i]=='0')
                map[j][i]=0;
            if(g[i]=='C')
                map[j][i]=5;
            if(g[i]=='K')
            {
                map[j][i]=3;
                mapty->enemy.xplace=i;
                mapty->enemy.yplace=j;
            }
            if(g[i]=='E')
            {
                mapty->map.xend=i;
                mapty->map.yend=j;
                map[j][i]=8;
            }
            if(g[i]=='P')
            {
                mapty->map.xstart=i;
                mapty->map.ystart=j;
                map[j][i]=7;
            }
            i++;
        }
        j++;
        free(g);
        g=get_next_line(fd);
    }
    lines=j-1;
    len--;
    // printf("%d\n",checkmove(map,i,j));
    planmap(map,i,j);
    // printf("error in walls\n");
    // exit(0);
    i=0,j=0;
    while(j<lines)
    {
        i=0;
        while(i<len)
        {
            if(map[j][i]==5||map[j][i]==8)
            {
                printf("error\n");
                exit(0);
            }
            i++;
        }
            // printf("\n");
        j++;

    }
    // printf("%d\n",checkmove(map,i,j));
    // printf("\n");
    close(fd);
    fd = open("map.ber",O_RDONLY);
    i=0,j=0;

    g=get_next_line(fd);
    while(g)
    {
        len = strlen(g);
        // free(map)
        // map[j]=malloc((len+1)*8);
        i=0;
        while(i<len)
        {
            if(g[i]=='1')
                map[j][i]=1;
            if(g[i]=='0')
                map[j][i]=0;
            if(g[i]=='K')
                map[j][i]=3;
            if(g[i]=='C')
            {
                mapty->door.many+=1;
                map[j][i]=5;
            	printf("%d\n",mapty->door.many);

            }
            if(g[i]=='E')
                map[j][i]=8;
            if(g[i]=='P')
                map[j][i]=7;
            i++;
        }
        j++;
    // printf("%d\n",j);
    free(g);
        g=get_next_line(fd);
    }
    mapty->map.x=i-1;
    mapty->map.y=j;
    // lines=j;
    // i=0,j=0;
    // while(j<lines)
    // {
    //     i=0;
    //     while(i<len)
    //     {
    //         printf("%d",map[j][i]);
    //         i++;
    //     }
    //         printf("\n");
    //     j++;

    // }
    // map.x=34;
    // mapty.map =map;
    return map;
}
#include <stdio.h>
#include <stdlib.h>

#define LEN 9

int maze[LEN][LEN] = {
    {2, 2, 2, 2, 2, 2, 2, 2, 2},
    {0, 0, 2, 2, 2, 2, 0, 2, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 2, 0, 2, 2, 0, 2},
    {0, 0, 0, 2, 0, 2, 2, 0, 2},
    {2, 2, 0, 2, 0, 2, 2, 0, 2},
    {2, 2, 0, 2, 0, 0, 0, 0, 2},
    {2, 2, 0, 0, 0, 2, 2, 2, 2},
    {2, 2, 2, 2, 0, 2, 2, 2, 2},
};                                           //?建迷?

int start_x = 1, start_y = 0;               //?置起点
int end_x = 8, end_y = 4;                   //?置?点
int success = 0;

void step(int x, int y);
void print_maze();

int main(int argc, char argv[])
{    

    printf("maze:\n");                    //打印迷??，?方便?看，将数字???形打印
    print_maze();

    step(start_x, start_y);

    return 0;
}


void step(int x, int y)                //用??算法求解路径 
{
    maze[x][y] = 1;

    if(x == end_x && y == end_y)
    {
        print_maze();                //打印函数放入??中，?找到一条成功路径打印一次
    }

    if(x < LEN && y < LEN && maze[x][y + 1] == 0){step(x, y + 1);}           //条件x < LEN && y < LEN避免溢出
    if(x < LEN && y < LEN && maze[x + 1][y] == 0){step(x + 1, y);}
    if(x < LEN && y < LEN && maze[x][y - 1] == 0){step(x, y - 1);}
    if(x < LEN && y < LEN && maze[x - 1][y] == 0){step(x - 1, y);}

    maze[x][y] = 0;
}

void print_maze()
{
    int x, y;

    for(x = 0; x < LEN; x++)
    {
        for(y = 0; y < LEN; y++)
        {
            if(maze[x][y] == 2)
                printf("■");
         else if(maze[x][y] == 1) 
             printf("☆");
         else if(maze[x][y] == 0)
             printf("□");    
     }
     printf("\n");
}

printf("\n");
}
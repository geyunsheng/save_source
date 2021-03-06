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
};                                           //?ΐ?

int start_x = 1, start_y = 0;               //?uN_
int end_x = 8, end_y = 4;                   //?u?_
int success = 0;

void step(int x, int y);
void print_maze();

int main(int argc, char argv[])
{    

    printf("maze:\n");                    //Εσΐ??C?ϋΦ?ΕC«???`Εσ
    print_maze();

    step(start_x, start_y);

    return 0;
}


void step(int x, int y)                //p??Z@πHa 
{
    maze[x][y] = 1;

    if(x == end_x && y == end_y)
    {
        print_maze();                //Εσϊό??C?Qκπ¬χHaΕσκ
    }

    if(x < LEN && y < LEN && maze[x][y + 1] == 0){step(x, y + 1);}           //πx < LEN && y < LENπΖμo
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
                printf("‘");
         else if(maze[x][y] == 1) 
             printf("");
         else if(maze[x][y] == 0)
             printf(" ");    
     }
     printf("\n");
}

printf("\n");
}
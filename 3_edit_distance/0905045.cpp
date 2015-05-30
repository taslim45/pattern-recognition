#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <set>
#include <string>
#include <string.h>
#include <queue>
#include <stack>
#include <iostream>
using namespace std;
#define MAXLEN 1000
#define INSERT 1
#define REPLACE 2
#define DELETE 3
#define NOP 0

char src[MAXLEN],dest[MAXLEN];
int dp[MAXLEN+5][MAXLEN+5];
int path[MAXLEN+5][MAXLEN+5];

int minn(int a,int b)
{
    if(a<b) return a;
    return b;
}
int editDistance()
{
    memset(path,-1,sizeof(path));
    int i,j,k;
    int val;
    int len1 = strlen(src);
    int len2 = strlen(dest);
    dp[0][0] = 0;
    path[0][0] = NOP;
    for(i=1; i<len1; i++) dp[i][0] = i, path[i][0] = DELETE;
    for(i=1; i<len2; i++) dp[0][i] = i, path[0][i] = INSERT;
    for(i=1; i<len1; i++)
    {
        for(j=1; j<len2; j++)
        {
            if(src[i]==dest[j]) val = 0;
            else val = 1;
            int a = dp[i-1][j-1] + val;
            int b = dp[i-1][j] + 1;
            int c = dp[i][j-1] + 1;

            int minimum = minn(a, minn( b, c));
            dp[i][j] = minimum;

            if(minimum == a)
            {
                if(val == 1) path[i][j] = REPLACE;
                else path[i][j] = NOP;
            }
            else if(minimum == b)
            {
                path[i][j] = DELETE;
            }
            else
            {
                path[i][j] = INSERT;
            }

        }
    }

    int x,y;
    x = len1-1;
    y = len2-1;
    while(x>=0 || y>=0)
    {
        //printf("%d %d\n",x,y);
        if(path[x][y] == NOP)
        {
            //printf("NOP\n");
            x--,y--;
        }
        else if(path[x][y] == INSERT)
        {
            printf("insert %c\n",dest[y]);
            y--;
        }
        else if(path[x][y] == DELETE)
        {
            printf("delete %c\n",src[x]);
            x--;
        }
        else if(path[x][y] == REPLACE)
        {
            printf("replace %c\n",src[x],dest[y]);
            x--,y--;
        }
    }
    return dp[len1-1][len2-1];
}

int main()
{
    //freopen("input.txt","r",stdin);
    strcpy(src," argentina");
    strcpy(dest," bangladesh");

    int res = editDistance();
    printf("Min cost %d\n",res);


    return 0;
}

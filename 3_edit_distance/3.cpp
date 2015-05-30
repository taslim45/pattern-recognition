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
#define MAXLEN 2000
#define INSERT 1
#define REPLACE 2
#define DELETE 3
#define NOP 0


int dp[2][MAXLEN+5];

int minn(int a,int b)
{
    if(a<b) return a;
    return b;
}
int editDistance(char *src,char *dest)
{
    int i,j,k;
    int val;
    int len1 = strlen(src);
    int len2 = strlen(dest);
    dp[0][0] = 0;
    dp[1][0] = 1;
    for(i=1; i<len2; i++) dp[0][i] = i;
    int p,q;
    p = 0;
    q = 1;
    for(i=1; i<len1; i++)
    {
        for(j=1; j<len2; j++)
        {
            if(src[i]==dest[j]) val = 0;
            else val = 1;
            dp[q][j] = minn(dp[p][j-1]+val,minn(dp[p][j],dp[q][j-1]) + 1);
        }
        q = 1 - q;
        p = 1 - p;
    }
    return dp[p][len2-1];
}

int edit(char *src,char *dest)
{
    int i,j,k;
    int len1 = strlen(src);
    int len2 = strlen(dest);

}

int main()
{
    char src[MAXLEN],dest[MAXLEN];
    strcpy(src," argentina");
    strcpy(dest," bangladesh");

    int res = editDistance(src,dest);
    printf("Min cost %d\n",res);


    return 0;
}

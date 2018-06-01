/*6.2 Saving James Bond - Easy Version
This time let us consider the situation in the movie "Live and Let Die" in which James Bond, the world's most famous spy, 
was captured by a group of drug dealers. 
He was sent to a small piece of land at the center of a lake filled with crocodiles. 
There he performed the most daring action to escape -- he jumped onto the head of the nearest crocodile! 
Before the animal realized what was happening, James jumped again onto the next big head... 
Finally he reached the bank before the last crocodile could bite him 
(actually the stunt man was caught by the big mouth and barely escaped with his extra thick boot).

Assume that the lake is a 100 by 100 square one. Assume that the center of the lake is at (0,0) and the northeast corner at (50,50). 
The central island is a disk centered at (0,0) with the diameter of 15. A number of crocodiles are in the lake at various positions. 
Given the coordinates of each crocodile and the distance that James could jump, you must tell him whether or not he can escape.

Input Specification:
Each input file contains one test case. Each case starts with a line containing two positive integers N (≤100), 
the number of crocodiles, and D, the maximum distance that James could jump. 
Then N lines follow, each containing the (x,y) location of a crocodile. Note that no two crocodiles are staying at the same position.

Output Specification:
For each test case, print in a line "Yes" if James can escape, or "No" if not.

Sample Input 1:
14 20
25 -15
-25 28
8 49
29 15
-35 -2
5 28
27 -29
-8 -28
-20 -35
-25 -20
-13 29
-30 15
-35 40
12 12
Sample Output 1:
Yes
Sample Input 2:
4 13
-12 12
12 12
-12 -12
12 -12
Sample Output 2:
No
*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>

#define Radius 7.5
#define MaxSize 110
#define Square_Size 100.0

typedef struct Point
{
    double x,y;
}Position;

Position P[MaxSize];
bool Visited[MaxSize];
int n;
double d;

bool IsSave(int V)  /* 判断是否能够跳到岸边 */
{
    return (abs(P[V].x)>=50-d || abs(P[V].y)>=50-d);
}

bool FirstJump(int V)   /* 第一跳及判断是否能够从岛跳到鳄鱼上去 */
{
    return (sqrt(P[V].x*P[V].x+P[V].y*P[V].y)<=d+Radius);
}

bool Jump(int V1,int V2)    /* 计算两点之间的距离 */
{
    return (sqrt((P[V1].x-P[V2].x)*(P[V1].x-P[V2].x)+(P[V1].y-P[V2].y)*(P[V1].y-P[V2].y))<=d);
}

bool DFS(int V)
{
    int i;
    Visited[V]=true;
    bool answer=false;
    if(IsSave(V))
        answer=true;
    for(i=0;i<n;i++)
    {
        if(!Visited[i] && Jump(V,i))
        {
            answer=DFS(i);
            if(answer)
                break;
        }
    }
    return answer;
}

void Save007()
{
    bool answer=false;
    int i;
    for(i=0;i<n;i++)
    {
        if(!Visited[i] && FirstJump(i))
        {
            answer=DFS(i);
            if(answer)
                break;
        }
    }
    if(answer)
        printf("Yes\n");
    else
        printf("No\n");
}

int main()
{
    int i;
    scanf("%d %lf",&n,&d);
    for (i=0;i<n;i++)
        scanf("%lf %lf",&(P[i].x),&(P[i].y));
    for (i=0;i<n;i++)
        Visited[i]=false;
    Save007();
    return 0;
}

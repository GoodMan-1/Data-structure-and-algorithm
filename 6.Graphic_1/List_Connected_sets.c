/*6.1 列出连通集
给定一个有N个顶点和E条边的无向图，请用DFS和BFS分别列出其所有的连通集。假设顶点从0到N−1编号。
进行搜索时，假设我们总是从编号最小的顶点出发，按编号递增的顺序访问邻接点。

输入格式:
输入第1行给出2个整数N(0<N≤10)和E，分别是图的顶点数和边数。随后E行，每行给出一条边的两个端点。每行中的数字之间用1空格分隔。

输出格式:
按照"{ v​1​​  v​2​​  ... v​k​​  }"的格式，每行输出一个连通集。先输出DFS的结果，再输出BFS的结果。

输入样例:
8 6
0 7
0 1
2 0
4 1
2 4
3 5
输出样例:
{ 0 1 4 2 7 }
{ 3 5 }
{ 6 }
{ 0 1 2 7 4 }
{ 3 5 }
{ 6 }
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MaxSize 100
typedef struct LNode *Vertex;
struct LNode
{
    int Data;
    int Flag;
    Vertex Next;
};

Vertex Queue[MaxSize];
int Front=0,Rear=0;

bool IsEmpty()
{
    return (Front==Rear);
}

void AddQ(int X)
{
    Rear=(Rear+1)%MaxSize;
    Queue[Rear]=X;
}

int DeleteQ()
{
    Front=(Front+1)%MaxSize;
    return Queue[Front];
}

Vertex CreateV(int num)
{
    int i;
    Vertex V=(Vertex)malloc(sizeof(struct LNode)*num);
    for(i=0;i<num;i++)
    {
        V[i].Next=NULL;
        V[i].Flag=0;
    }
    return V;
}

void InsertV(Vertex V,int X)
{
    while(V->Next && V->Next->Data<X)
        V=V->Next;
    Vertex temp=(Vertex)malloc(sizeof(struct LNode));
    temp->Data=X;
    temp->Next=V->Next;
    V->Next=temp;
}

void DFS(Vertex V,int key)
{
    if(!V)
        return ;
    Vertex temp=V[key].Next;
    while(temp)
    {
        if(!V[temp->Data].Flag)
        {
            printf(" %d",temp->Data);
            V[temp->Data].Flag=1;
            DFS(V,temp->Data);
        }
        temp=temp->Next;
    }
    return ;
}

void BFS(Vertex V,int key)
{
    Vertex temp=V[key].Next;
    while(temp)
    {
        if(!V[temp->Data].Flag)
        {
            AddQ(temp->Data);
            V[temp->Data].Flag=1;
        }
        temp=temp->Next;
    }
    while(!IsEmpty())
    {
        int pt;
        pt=DeleteQ();
        Vertex t=V[pt].Next;
        while(t)
        {
            if(!V[t->Data].Flag)
            {
                AddQ(t->Data);
                V[t->Data].Flag=1;
            }
            t=t->Next;
        }
        printf(" %d",pt);
    }
}

int main()
{
    int Nv,Ne,i,from,to;
    scanf("%d %d",&Nv,&Ne);
    Vertex V=CreateV(Nv);
    for(i=0;i<Ne;i++)
    {
        scanf("%d %d",&from,&to);
        InsertV(&V[to],from);
        InsertV(&V[from],to);
    }
    for(i=0;i<Nv;i++)
    {
        if(!V[i].Flag)
        {
            V[i].Flag=1;
            printf("{");
            printf(" %d",i);
            DFS(V,i);
            printf(" }\n");
        }
    }
    for(i=0;i<Nv;i++)
        V[i].Flag=0;
    for(i=0;i<Nv;i++)
    {
        if(!V[i].Flag)
        {
            V[i].Flag=1;
            printf("{");
            printf(" %d",i);
            BFS(V,i);
            printf(" }\n");
        }
    }
    return 0;
}

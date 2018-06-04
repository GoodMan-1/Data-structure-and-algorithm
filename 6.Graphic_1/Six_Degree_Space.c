/*6.3 六度空间
“六度空间”理论又称作“六度分隔（Six Degrees of Separation）”理论。
这个理论可以通俗地阐述为：“你和任何一个陌生人之间所间隔的人不会超过六个，也就是说，最多通过五个人你就能够认识任何一个陌生人。”

“六度空间”理论虽然得到广泛的认同，并且正在得到越来越多的应用。但是数十年来，试图验证这个理论始终是许多社会学家努力追求的目标。
然而由于历史的原因，这样的研究具有太大的局限性和困难。
随着当代人的联络主要依赖于电话、短信、微信以及因特网上即时通信等工具，能够体现社交网络关系的一手数据已经逐渐使得“六度空间”理论的验证成为可能。

假如给你一个社交网络图，请你对每个节点计算符合“六度空间”理论的结点占结点总数的百分比。

输入格式:
输入第1行给出两个正整数，分别表示社交网络图的结点数N（1<N≤10​4​​ ，表示人数）、边数M（≤33×N，表示社交关系数）。
随后的M行对应M条边，每行给出一对正整数，分别是该条边直接连通的两个结点的编号（节点从1到N编号）。

输出格式:
对每个结点输出与该结点距离不超过6的结点数占结点总数的百分比，精确到小数点后2位。每个结节点输出一行，格式为“结点编号:（空格）百分比%”。

输入样例:
10 9
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
输出样例:
1: 70.00%
2: 80.00%
3: 90.00%
4: 100.00%
5: 100.00%
6: 100.00%
7: 100.00%
8: 90.00%
9: 80.00%
10: 70.00%
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MaxSize 10001
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
    Vertex V=(Vertex)malloc(sizeof(struct LNode)*(num+1));  /* 输入从1开始，申请空间多1个 */
    for(i=0; i<=num; i++)
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

int BFS(Vertex V,int key)
{
    int last=key,tail,Count=1,level=1;
    Vertex temp=V[key].Next;
    while(temp)
    {
        if(!V[temp->Data].Flag)
        {
            AddQ(temp->Data);
            Count++;
            V[temp->Data].Flag=1;
            tail=temp->Data;
        }
        temp=temp->Next;
    }
    last=tail;
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
                Count++;
                V[t->Data].Flag=1;
                tail=t->Data;
            }
            t=t->Next;
        }
        if(pt==last)
        {
            level++;
            last=tail;
        }
        if(level==6)
            break;
    }
    return Count;
}

int main()
{
    int Nv,Ne,i,j,from,to,pt;
    float result,Count;
    scanf("%d %d",&Nv,&Ne);
    Vertex V=CreateV(Nv);
    for(i=0; i<Ne; i++)
    {
        scanf("%d %d",&from,&to);
        InsertV(&V[to],from);
        InsertV(&V[from],to);
    }
    for(i=1; i<=Nv; i++)
    {
        V[i].Flag=1;
        Count=BFS(V,i); /* 每次访问一个结点，遍历所有结点 */
        result=100.0*(Count/Nv);
        printf("%d: %.2f%%\n",i,result);
        for(j=1; j<=Nv; j++)
            V[j].Flag=0;    /* Flag标记清空为0 */
        while(!IsEmpty())
            pt=DeleteQ();   /* 清空未清空的队列 */
    }
    return 0;
}

/*3.2 List Leaves
Given a tree, you are supposed to list all the leaves in the order of top down, and left to right.

Input Specification:
Each input file contains one test case. For each case, 
the first line gives a positive integer N (≤10) 
which is the total number of nodes in the tree -- and hence the nodes are numbered from 0 to N−1. 
Then N lines follow, each corresponds to a node, and gives the indices of the left and right children of the node. 
If the child does not exist, a "-" will be put at the position. Any pair of children are separated by a space.

Output Specification:
For each test case, print in one line all the leaves' indices in the order of top down, and left to right. 
There must be exactly one space between any adjacent numbers, and no extra space at the end of the line.

Sample Input:
8
1 -
- -
0 -
2 7
- -
- -
5 -
4 6
Sample Output:
4 1 5
*/

/*队列采用动态链表法，二叉树采用静态链表法*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MaxTree 10000
#define ElementType char
#define Tree int
#define Null -1
struct TreeNode
{
    Tree Left;
    Tree Right;
} T[MaxTree];

typedef struct Node *PtrToNode;
struct Node //队列中的结点
{
    int Data;
    PtrToNode Next;
};
typedef PtrToNode Position;

struct QNode
{
    Position Front,Rear;    //队列的头、尾指针
    int MaxSize;    //队列最大容量
};
typedef struct QNode *Queue;

bool IsEmpty(Queue Q)
{
    if(Q->Front==Q->Rear)
        return 1;
    else
        return 0;
}

Queue CreatQueue()
{
    Queue Q=(Queue)malloc(sizeof(struct QNode));
    Q->Front=Q->Rear=(PtrToNode)malloc(sizeof(struct Node));
    Q->Front->Next=NULL;
    Q->MaxSize=0;
    return Q;
}

void AddQ(Queue Q,int x)
{
    PtrToNode temp,t;
    temp=(PtrToNode)malloc(sizeof(struct Node));
    temp->Data=x;
    temp->Next=NULL;
    if(IsEmpty(Q))
        Q->Front->Next=temp;
    else
        Q->Rear->Next=temp;
    Q->Rear=temp;
    Q->MaxSize++;
}

int DeleteQ(Queue Q)
{
    Position FrontCell;
    int FrontElem;
    if(IsEmpty(Q))
        return -1;
    else
    {
        FrontCell=Q->Front->Next;
        FrontElem=FrontCell->Data;
        if(Q->Front->Next==Q->Rear)
            Q->Rear=Q->Front;
        else
            Q->Front->Next=FrontCell->Next;
        free(FrontCell);
        return FrontElem;
    }
}

void PostorderTraversal(Tree R)
{
    Queue Q;
    int flag=0;
    Q=CreatQueue();
    if(R!=Null)
    {
        AddQ(Q,R);
        while(!IsEmpty(Q))
        {
            R=DeleteQ(Q);
            if((T[R].Left==Null) && (T[R].Right==Null))
                if(flag)
                    printf(" %d",R);
                else
                {
                    flag=1;
                    printf("%d",R);
                }
            if(T[R].Left!=Null)
                AddQ(Q,T[R].Left);
            if(T[R].Right!=Null)
                AddQ(Q,T[R].Right);
        }
    }
}

Tree BuildTree(struct TreeNode T[])
{
    int N,i,Root=Null,check[MaxTree];
    char cl,cr;
    scanf("%d",&N);
    for(i=0; i<N; i++)
        check[i]=0;
    for(i=0; i<N; i++)
    {
        scanf("\n%c %c",&cl,&cr);
        if(cl!='-')
        {
            T[i].Left=cl-'0';
            check[T[i].Left]=1;
        }
        else
            T[i].Left=Null;
        if(cr!='-')
        {
            T[i].Right=cr-'0';
            check[T[i].Right]=1;
        }
        else
            T[i].Right=Null;
    }
    for(i=0; i<N; i++)
        if(!check[i])
            break;
    Root=i;
    return Root;
}

int main()
{
    Tree R;
    R=BuildTree(T);
    PostorderTraversal(R);
    return 0;
}

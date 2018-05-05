#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType data;
    PtrToNode   next;
};
typedef PtrToNode List;

void Attach(int d,PtrToNode *prear)
{
    PtrToNode p;
    p=(PtrToNode)malloc(sizeof(struct Node));
    p->data=d;
    p->next=NULL;
    (*prear)->next=p;
    *prear=p;
}

List Read() /* 细节在此不表 */
{
   PtrToNode p,rear;
   int n,data;
   scanf("%d",&n);
   p=(PtrToNode)malloc(sizeof(struct Node));
   p->next=NULL;
   rear=p;
   while(n--)
   {
       scanf("%d",&data);
       Attach(data,&rear);
   }
   rear->next=NULL;
   return p;
}

void Print(List L ) /* 细节在此不表；空链表将输出NULL */
{
    int flag=0;
    List temp=L->next;
    if(!temp)
    {
        printf("NULL\n");
        return;
    }
    while(temp)
    {
        if(!flag)
            flag=1;
        else
            printf(" ");
        printf("%d",temp->data);
        temp=temp->next;
    }
    printf("\n");
}

List Merge( List L1, List L2 )
{
    List head,rear,t1,t2;
    t2=L2->next;
    int d;
    rear=(PtrToNode)malloc(sizeof(struct Node));
    head=rear;
    while(t1&&t2)
    {
       if(t1->data < t2->data)
        {
            Attach(t1->data,&rear);
            t1=t1->next;
        }
       else if(t1->data > t2->data)
       {
            Attach(t2->data,&rear);
            t2=t2->next;
       }
       else
        {
            Attach(t1->data,&rear);
            t1=t1->next;
            Attach(t2->data,&rear);
            t2=t2->next;
        }
    }
    for(;t1;t1=t1->next)
        Attach(t1->data,&rear);
    for(;t2;t2=t2->next)
        Attach(t2->data,&rear);
    rear->next=NULL;
    L1->next=NULL;
    L2->next=NULL;
    return head;
}

int main()
{
    PtrToNode L1, L2, L;
    PtrToNode L3;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

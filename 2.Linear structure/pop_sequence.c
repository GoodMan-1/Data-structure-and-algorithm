/*2.4 Pop Sequence
Given a stack which can keep M numbers at most. Push N numbers in the order of 1, 2, 3, ..., N and pop randomly. 
You are supposed to tell if a given sequence of numbers is a possible pop sequence of the stack. 
For example, if M is 5 and N is 7, we can obtain 1, 2, 3, 4, 5, 6, 7 from the stack, but not 3, 2, 1, 7, 5, 6, 4.

Input Specification:
Each input file contains one test case. 
For each case, the first line contains 3 numbers (all no more than 1000): M (the maximum capacity of the stack), 
N (the length of push sequence), and K (the number of pop sequences to be checked). 
Then K lines follow, each contains a pop sequence of N numbers. 
All the numbers in a line are separated by a space.

Output Specification:
For each pop sequence, print in one line "YES" if it is indeed a possible pop sequence of the stack, or "NO" if not.

Sample Input:
5 7 5
1 2 3 4 5 6 7
3 2 1 7 5 6 4
7 6 5 4 3 2 1
5 6 4 3 7 2 1
1 7 6 5 4 3 2

Sample Output:
YES
NO
NO
YES
NO
*/

/*method 1 链表实现对该题来说较复杂*/

#include<stdio.h>
#include <stdbool.h>
typedef struct SNode *PtrToSNode;
typedef struct SNode
{
    int Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;

Stack CreateStack(int M)
{
    Stack S;
    S=(Stack)malloc(sizeof(struct SNode));
    S->Next=NULL;
    return S;
}

bool IsEmpty(Stack S)
{
    return (S->Next==NULL);
}

bool IsFull(Stack S,int M)
{
    Stack temp=(Stack)malloc(sizeof(struct SNode));
    temp->Next=NULL;
    temp=S->Next;
    while(temp!=NULL)
    {
        temp=temp->Next;
        M--;
        if(M==1)
            break;
    }
    if(M==1)
        return true;
    else
        return false;
}

void Push(Stack S,int X)
{
    PtrToSNode temp=(PtrToSNode)malloc(sizeof(struct SNode));
    temp->Data=X;
    temp->Next=S->Next;
    S->Next=temp;
}

void Pop(Stack S)
{
    PtrToSNode Top;
    int TopElem;
    Top=S->Next;
    TopElem=Top->Data;
    S->Next=Top->Next;
    free(Top);
}

bool Judge(Stack S,int A[],int M,int N)
{
    int i=1,j=1,flag=1;
    while(flag)
    {
        Push(S,i);
        while(S->Next->Data==A[j])
        {
            Pop(S);
            j++;
            if(IsEmpty(S))
                break;
        }
        i++;
        if(IsFull(S,(M+1)))
            break;
        if(i>N && IsEmpty(S))
            flag=0;
    }
    if(flag==1)
        return false;
    else if(flag==0)
        return true;
}

int main()
{
    Stack S;
    int M,N,K,i,j,A[1000];
    scanf("%d %d %d",&M,&N,&K);
    S=CreateStack(M);
    for(j=0; j<K; j++)
    {
        for(i=1; i<=N; i++)
        {
            S=CreateStack(M);
            scanf("%d",&A[i]);
        }
        if(Judge(S,A,M,N))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

/*method 2 线性表实现对该题来说较简单*/

#include <stdio.h>  
#include <stdlib.h>  
#define MaxSize 1000  
typedef struct StackRecord{  
    int capacity;  
    int top;  
    int data[MaxSize];  
}*Stack;  
Stack CreateStack(int capacity) {  
    Stack S = (Stack)malloc(sizeof(struct StackRecord));  
    S->top = -1;  
    S->capacity = capacity;  
    return S;  
}  
int Push(Stack S, int x) {  //将x元素入栈，如果溢出则入栈失败返回0  
    if(S->capacity - S->top <= 1)  
        return 0;  
    S->data[++S->top] = x;  
    return 1;  
}  
int Top(Stack S) {  //返回栈顶元素，空栈时返回-1  
    if(S->top >= 0)  
        return S->data[S->top];  
    else  
        return -1;  
}  
void Pop(Stack S) { //弹出栈顶元素  
    S->top--;  
}  
void DisposeStack(Stack S) {  
    free(S);  
}  
//模拟进栈出栈过程：依次入栈并同时与出栈序列的第一个元素对比；若相等则弹出栈顶元素，并消去出栈序列的首元素；  
//全部已入栈后出栈序列中的元素全部被消去则返回1，否则返回0；  
int IsPopSeq(int* popOrder, int capacity, int n) {  
    Stack S = CreateStack(capacity);  
    int head = 0;       //维护一个下标，指向出栈序列中还没被消去的第一个元素  
    for(int node = 1; node <= n; node++) {   //入栈节点从1到k  
        if(!Push(S, node)){     //如果入栈失败表示栈满，则返回0  
            DisposeStack(S);  
            return 0;  
        }  
        while(Top(S) == popOrder[head]) {  
            Pop(S);  
            head++;  
        }  
    }  
    DisposeStack(S);  
    if(head != n)       //出栈序列不为空，则返回0  
        return 0;  
    return 1;  
}  
int main() {  
    int m, n, k;  
    scanf("%d%d%d", &m, &n, &k);  
    int popOrder[1000];  
    for(int i = 0; i < k; i++) {  
        for(int j = 0; j < n; j++)  
            scanf("%d", &popOrder[j]);  
        if(IsPopSeq(popOrder, m, n))  
            printf("YES\n");  
        else  
            printf("NO\n");  
    }  
  
    return 0;  
}  

/*3.3 Tree Traversals Again
An inorder binary tree traversal can be implemented in a non-recursive way with a stack. 
For example, suppose that when a 6-node binary tree (with the keys numbered from 1 to 6) is traversed, 
the stack operations are: push(1); push(2); push(3); pop(); pop(); push(4); pop(); pop(); push(5); push(6); pop(); pop(). 
Then a unique binary tree (shown in Figure 1) can be generated from this sequence of operations. 
Your task is to give the postorder traversal sequence of this tree.

Figure 1
Input Specification:
Each input file contains one test case. 
For each case, the first line contains a positive integer N (≤30) which is the total number of nodes in a tree(and hence the nodes are numbered from 1 to N). 
Then 2N lines follow, each describes a stack operation in the format: "Push X" where X is the index of the node being pushed onto the stack;or "Pop" meaning to pop one node from the stack.

Output Specification:
For each test case, print the postorder traversal sequence of the corresponding tree in one line. 
A solution is guaranteed to exist. 
All the numbers must be separated by exactly one space, and there must be no extra space at the end of the line.

Sample Input:
6
Push 1
Push 2
Push 3
Pop
Pop
Push 4
Pop
Pop
Push 5
Push 6
Pop
Pop
Sample Output:
3 4 2 6 5 1
*/

/*method 1 答案正确 堆栈数组存储，二叉树链表存储*/
#include<stdio.h>
#include<stdbool.h>
#define MaxSize 30
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    int Elem;
    BinTree Left;
    BinTree Right;
};

int flag=0;
BinTree Stack[MaxSize];
int top = -1;

void Push(BinTree BT)
{
    Stack[++top] = BT;
}

BinTree Pop()
{
    return Stack[top--];
}

bool IsEmpty()
{
    return top == -1;
}

BinTree TOP()
{
    return Stack[top];
}

BinTree ReadTree()
{
    char s[5];
    int i,data,N,FindRoot=0,Poped=0;
    BinTree Root,Father;
    scanf("%d",&N);
    for(i=0; i<2*N; i++)
    {
        scanf("%s",&s);
        if(s[1]=='u')
        {
            scanf("%d",&data);
            BinTree temp=(BinTree)malloc(sizeof(struct TNode));
            temp->Elem=data;
            temp->Left=NULL;
            temp->Right=NULL;
            if(!FindRoot)
            {
                Root=temp;  //根节点
                Push(temp);
                FindRoot=1;
            }
            else
            {
                if(!Poped)  //如果前一个操作不是pop，则父节点为栈顶元素
                    Father=TOP();
                if(Father->Left==NULL)
                    Father->Left=temp;
                else
                    Father->Right=temp;
                Push(temp);
            }
            Poped=0;
        }
        else
        {
            Father=Pop();
            Poped=1;
        }
    }
    return Root;
}

BinTree PostorderTraversal(BinTree BT)
{
    if(BT)
    {
        PostorderTraversal(BT->Left);
        PostorderTraversal(BT->Right);
        if(flag)
            printf(" %d",BT->Elem);
        else
        {
            flag=1;
            printf("%d",BT->Elem);
        }
    }
}

int main()
{
    BinTree BT;
    BT=ReadTree();
    PostorderTraversal(BT);
    return 0;
}

/*method 1 段错误（原因:两个结构体）*/
#include<stdio.h>
#include<stdbool.h>
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    int Elem;
    BinTree Left;
    BinTree Right;
};

struct SNode
{
    int *Data;  //存储元素的数组
    int Top;    //栈顶指针
    int MaxSize;    // 堆栈最大容量
};
typedef struct SNode *Stack;

int flag=0;

Stack CreateStack(int MaxSize)
{
    Stack S=(Stack)malloc(sizeof(struct SNode));
    S->Data=(int *)malloc(MaxSize * sizeof(int));
    S->Top=-1;
    S->MaxSize=MaxSize;
}

bool IsFull(Stack S)
{
    return (S->Top==S->MaxSize-1);
}

bool IsEmpty(Stack S)
{
    return (S->Top==-1);
}

void Push(Stack S, BinTree BT)
{
    S->Data[++(S->Top)]=BT;
}

BinTree Pop(Stack S)
{
    if(IsEmpty(S))
        return -1;
    else
        return (S->Data[(S->Top)--]);
}

BinTree top(Stack S)
{
    return (S->Data[S->Top]);
}

BinTree ReadTree()
{
    char s[10];
    int i,data,N,FindRoot=0,Poped=0;
    BinTree Root,Father;
    Stack S;
    S=CreateStack(30);
    scanf("%d",&N);
    for(i=0;i<2*N;i++)
    {
        scanf("%s",&s);
        if(s[1]=='u')
        {
            scanf("%d",&data);
            BinTree temp=(BinTree)malloc(sizeof(struct TNode));
            temp->Elem=data;
            temp->Left=NULL;
            temp->Right=NULL;
            if(!FindRoot)
            {
                Root=temp;
                Push(S,temp);
                FindRoot=1;
            }
            else
            {
                if(!Poped)
                    Father=top(S);
                if(Father->Left==NULL)
                    Father->Left=temp;
                else
                    Father->Right=temp;
                Push(S,temp);
            }
            Poped=0;
        }
        else
        {
            Father=Pop(S);
            Poped=1;
        }
    }
    return Root;
}

BinTree PostorderTraversal(BinTree BT)
{
    if(BT)
    {
        PostorderTraversal(BT->Left);
        PostorderTraversal(BT->Right);
        if(flag)
        printf(" %d",BT->Elem);
        else
        {
            flag=1;
            printf("%d",BT->Elem);
        }
    }
}

int main()
{
    BinTree BT;
    BT=ReadTree();
    PostorderTraversal(BT);
    return 0;
}

/*method 2 数组实现：已知二叉树的前序遍历，中序遍历，求后序遍历*/
#include<stdio.h>
#define MaxSize 30

int Stack[MaxSize];     //堆栈数组
int pre[MaxSize];       //前序遍历数组
int in[MaxSize];       //中序遍历数组
int post[MaxSize];      //后序遍历数组
int top = -1;

void Push(int BT)
{
    Stack[++top] = BT;
}

int Pop()
{
    return Stack[top--];
}

int PostorderTraversal(int preL,int inL,int postL,int n)
{
    int i,L,root,R;
    if(n==0)
        return;
    if(n==1)
    {
        post[postL]=pre[preL];
        return;
    }
    root=pre[preL];     //根节点为前序遍历的第一个节点
    post[postL+n-1]=root;
    for(i=0;i<n;i++)
        if(in[inL+i]==root)     //中序遍历的根节点将数组分成左右两部分，分别对应左右子树
            break;
    L=i;                        //左子树节点个数
    R=n-L-1;                    //右子树节点个数
    PostorderTraversal(preL+1,inL,postL,L);              //递归解决左子树
    PostorderTraversal(preL+L+1,inL+L+1,postL+L,R);     //递归解决右子树
}

int main()
{
    char s[5];
    int i,data,N,pr=0,pi=0;
    scanf("%d",&N);
    for(i=0; i<2*N; i++)
    {
        scanf("%s",&s);
        if(s[1]=='u')
        {
            scanf("%d",&data);
            pre[pr++]=data;
            Push(data);
        }
        else
            in[pi++]=Pop();
    }
    PostorderTraversal(0,0,0,N);    //参数为三个数组最左边的数组位置，以及节点个数
    printf("%d",post[0]);
    for(i=1;i<N;i++)
        printf(" %d",post[i]);
    return 0;
}

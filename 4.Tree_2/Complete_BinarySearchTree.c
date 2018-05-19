/*4.3 Complete Binary Search Tree
A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

.The left subtree of a node contains only nodes with keys less than the node's key.
.The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
.Both the left and right subtrees must also be binary search trees.
A Complete Binary Tree (CBT) is a tree that is completely filled, 
with the possible exception of the bottom level, which is filled from left to right.

Now given a sequence of distinct non-negative integer keys, 
a unique BST can be constructed if it is required that the tree must also be a CBT.
You are supposed to output the level order traversal sequence of this BST.

Input Specification:
Each input file contains one test case. For each case, the first line contains a positive integer N (≤1000).
Then N distinct non-negative integer keys are given in the next line. 
All the numbers in a line are separated by a space and are no greater than 2000.

Output Specification:
For each test case, print in one line the level order traversal sequence of the corresponding complete binary search tree. 
All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

Sample Input:
10
1 2 3 4 5 6 7 8 9 0
Sample Output:
6 3 8 1 5 7 9 0 2 4
*/

/* method 1 完全二叉树的的一个性质：孩子节点的下标为i则其左孩子节点的下标为2*i，右孩子节点的下标为2*i+1，这个性质只有完全二叉树才满足，
其实反过来按这个性质构造出来的树就是一个完全二叉树。 要实现这棵完全二叉树也是排序树，其实就简单了，
显然一棵二叉排序树的中序遍历序列是递增有序的，所以这就简单了，只要在构造完全二叉树的时候按中序构造就可以了（前提是元素递增有序）。*/

#include<stdio.h>
#include<stdlib.h>
#define MaxSize 1000

int CBST[MaxSize],Node[MaxSize],N,pos;

int compare(const void *a,const void *b)
{
    return *(int*)a-*(int*)b;
}

void solve(int root)
{
    int lson,rson;
    if(root>N)
        return;
    lson=root<<1;
    rson=(root<<1)+1;
    solve(lson);
    CBST[root]=Node[pos++];
    solve(rson);
}

int main()
{
    int i;
    scanf("%d",&N);
    for(i=0;i<N;i++)
        scanf("%d",&Node[i]);
    qsort(Node,N,sizeof(int),compare);
    pos=0;
    solve(1);
    printf("%d",CBST[1]);
    for(i=2;i<=N;i++)
        printf(" %d",CBST[i]);
    return 0;
}

/* methon 2 （1）首先因为是完全二叉树，因此可以用数组来存，既方便又不浪费空间，而且数组就是按层次遍历的顺序存的，最后只要把数组顺序输出就行了。

（2）因为又是二叉搜索树，所以左边的结点一定小于根结点；再根据完全二叉树的性质，能够算出根节点是哪个元素

（3）用分而治之的方法，先求出整棵树的根结点；然后再分别求左子树的根结点，再求右子树的根节点。

注意点：

如何根据二叉搜索树和完全二叉树的性质，来求出根结点

1、完全二叉树，知道了结点个数，就能确定整棵树的形状；因而能求出左子树有多少个结点

2、二叉搜索树，左边的结点一定小于根结点，又因为左边的结点个数L已经算出，只要将所给的元素从小到大排序，第L+1个就是根结点。 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MaxSize 1005

int T[MaxSize],A[MaxSize];

int cmp(const void *a,const void *b){
    int *pa = (int *)a;
    int *pb = (int *)b;
    return *pa-*pb;
}

int GetLeftLength(int n)
{//利用二叉树的性质：满二叉树第i层有 2^(i-1) 个结点， 高为h的满二叉树有 2^h - 1 个结点（从1开始）
    double h, x, L, t;
    h = (double)(int)( log((double)n+1) / log(2.0) );
    //h = floor( log((double)n+1) / log(2.0) );
    x = n - pow(2.0, h) + 1 ;
    t = pow(2.0, h - 1.0);
    x = x < t ? x : t;
    L = t - 1 + x;
    return (int)L;
}

void solve(int ALeft,int ARight,int TRoot)
{//初始调用： solve(0, n-1, 0)
    int n,L,LeftTRoot,RightTRoot;
    n=ARight-ALeft+1;       //数组中的总个数
    if(n==0)                //递归退出的条件
        return;
    L=GetLeftLength(n);       //计算出左子树的结点
    T[TRoot]=A[ALeft+L];      //将新的根结点放入新的数组
    LeftTRoot=TRoot*2+1;      //左孩子
    RightTRoot=LeftTRoot+1;   //右孩子
    solve(ALeft,ALeft+L-1,LeftTRoot);
    solve(ALeft+L+1,ARight,RightTRoot);
}

int main()
{
    int i,N;
    scanf("%d",&N);
    for(i=0;i<N;i++)
        scanf("%d",&A[i]);
    qsort(A,N,sizeof(int),cmp);
    solve(0,N-1,0);
    printf("%d",T[0]);
    for(i=1;i<N;i++)
        printf(" %d",T[i]);
    return 0;
}

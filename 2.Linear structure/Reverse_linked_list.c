/*2.3 Reversing Linked List
Given a constant K and a singly linked list L, you are supposed to reverse the links of every K elements on L. 
For example, given L being 1→2→3→4→5→6, if K=3, then you must output 3→2→1→6→5→4; if K=4, you must output 4→3→2→1→5→6.

Input Specification:
Each input file contains one test case. For each case, the first line contains the address of the first node, a positive N (≤10
​5
​​ ) which is the total number of nodes, and a positive K (≤N) which is the length of the sublist to be reversed. 
The address of a node is a 5-digit nonnegative integer, and NULL is represented by -1.

Then N lines follow, each describes a node in the format:

Address Data Next
where Address is the position of the node, Data is an integer, and Next is the position of the next node.

Output Specification:
For each case, output the resulting ordered linked list. Each node occupies a line, and is printed in the same format as in the input.

Sample Input:
00100 6 4
00000 4 99999
00100 1 12309
68237 6 -1
33218 3 00000
99999 5 68237
12309 2 33218

Sample Output:
00000 4 33218
33218 3 12309
12309 2 00100
00100 1 99999
99999 5 68237
68237 6 -1
*/

/*method 1 c语言*/
#include<stdio.h>
#define MAX_SIZE 100004

typedef struct tagLNode{
    int addr;      //节点位置Address
    int data;      //Data值
    int nextAddr;  //下个节点位置
    struct tagLNode *next;  //指向下个节点的指针
} LNode;
/*
    LNode *listReverse(LNode *head, int k);
    反转单链表函数
    参数1：单链表的头节点，
    参数2：反转子链表的长度，
    返回值：反转后的链表的第一个节点(不是头结点)

*/
LNode *listReverse(LNode *head, int k);
//输出单链表 参数为单链表的头结点
void printList(LNode *a);

int main()
{
    int firstAddr;
    int n = 0;            //节点数 N
    int k = 0;            //反转子链表的长度K
    int num = 0;          //链表建好之后的链表节点数
    int data[MAX_SIZE];   //存data值 节点位置作为索引值
    int nexts[MAX_SIZE];   //存next值 节点位置为索引
    int tmp;              //临时变量，输入的时候用

    scanf("%d %d %d", &firstAddr, &n, &k);
    LNode a[n+1];                //能存n+1个几点的数组。
    a[0].nextAddr = firstAddr;   //a[0] 作为头节点
    //读输入的节点
    int i = 1;
    for (; i < n+1; i++){
        scanf("%d", &tmp);
        scanf("%d %d", &data[tmp], &nexts[tmp]);
    }

    //构建单链表
    i = 1;
    while (1){
        if (a[i-1].nextAddr == -1){
            a[i-1].next = NULL;
            num = i-1;
            break;
        }
        a[i].addr = a[i-1].nextAddr;
        a[i].data = data[a[i].addr];
        a[i].nextAddr = nexts[a[i].addr];
        a[i-1].next = a+i;

        i++;
    }

    LNode *p = a;                    //p指向链表头结点
    LNode *rp = NULL;                //反转链表函数的返回值
    if (k <= num ){

        for (i = 0; i < (num/k); i++){
            rp = listReverse(p, k);  //
            p->next = rp;            // 第一次执行，a[0]->next 指向第一段子链表反转的第一个节点
            p->nextAddr = rp->addr;  // 更改Next值，指向逆转后它的下一个节点的位置

            int j = 0;
            //使p指向下一段需要反转的子链表的头结点（第一个节点的前一个节点）
            while (j < k){
                p = p->next;
                j++;
            }
        }
    }

    printList(a);
}

LNode *listReverse(LNode *head, int k)
{
    int count = 1;
    LNode *new = head->next;
    LNode *old = new->next;
    LNode *tmp = NULL;

    while (count < k){
        tmp = old->next;
        old->next = new;
        old->nextAddr = new->addr;
        new = old;   //new向后走一个节点
        old = tmp;   //tmp向后走一个节点
        count++;
    }
    //使反转后的最后一个节点指向下一段子链表的第一个节点
    head->next->next = old;
    if (old != NULL){
        //修改Next值，使它指向下一个节点的位置
        head->next->nextAddr = old->addr;
    }else{
        //如果old为NULL,即没有下一个子链表，那么反转后的最后一个节点即是真个链表的最后一个节点
        head->next->nextAddr = -1;
    }
    return new;
}

void printList(LNode *a)
{
    LNode *p = a;

    while (p->next != NULL){
        p = p->next;
        if (p->nextAddr != -1 ){
            //格式输出，%.5意味着如果一个整数不足5位，输出时前面补0 如：22，输出：00022
            printf("%.5d %d %.5d\n", p->addr, p->data, p->nextAddr);
        }else{
            //-1不需要以%.5格式输出
            printf("%.5d %d %d\n", p->addr, p->data, p->nextAddr);
        }
    }
}

/*method 2 c++*/
#include<iostream>  
#include<stdio.h>  
#include<algorithm>    ///使用到reverse 翻转函数  
using namespace std;  

#define MAXSIZE 1000010   ///最大为五位数的地址  

struct node    ///使用顺序表存储data和下一地址next  
{  
   int data;     
   int next;  
}node[MAXSIZE];  

int List[MAXSIZE];   ///存储可以连接上的顺序表  
int main()  
{  
    int First, n, k;    
    cin>>First>>n>>k;   ///输入头地址 和 n，k；  
    int Address,Data,Next;  
    for(int i=0;i<n;i++)  
    {  
        cin>>Address>>Data>>Next;  
        node[Address].data=Data;  
        node[Address].next=Next;  
    }  

    int j=0;  ///j用来存储能够首尾相连的节点数  
    int p=First;   ///p指示当前结点  
    while(p!=-1)  
    {  
        List[j++]=p;  
        p=node[p].next;  
    }  
    int i=0;  
    while(i+k<=j)   ///每k个节点做一次翻转  
    {  
        reverse(&List[i],&List[i+k]);  
        i=i+k;  
    }  
    for(i=0;i<j-1;i++)  
        printf("%05d %d %05d\n",List[i],node[List[i]].data,List[i+1]);  
    printf("%05d %d -1\n",List[i],node[List[i]].data);  
    return 0;  
}  

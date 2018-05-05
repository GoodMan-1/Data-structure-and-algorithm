/*
1.1 最大子列和问题
给定K个整数组成的序列{ N​1​​ , N​2​​ , ..., N​K​​  }，“连续子列”被定义为{ N​i​​ , N​i+1​​ , ..., N​j​​  }，
其中 1≤i≤j≤K。“最大子列和”则被定义为所有连续子列元素的和中最大者。
例如给定序列{ -2, 11, -4, 13, -5, -2 }，其连续子列{ 11, -4, 13 }有最大的和20。
现要求你编写程序，计算给定整数序列的最大子列和。

本题旨在测试各种不同的算法在各种数据情况下的表现。各组测试数据特点如下：

数据1：与样例等价，测试基本正确性；
数据2：102个随机整数；
数据3：103个随机整数；
数据4：104个随机整数；
数据5：105个随机整数；
输入格式:
输入第1行给出正整数K (≤100000)；第2行给出K个整数，其间以空格分隔。

输出格式:
在一行中输出最大子列和。如果序列中所有整数皆为负数，则输出0。

输入样例:
6
-2 11 -4 13 -5 -2
输出样例:
20
*/
/*method 1:在线处理 T(N)=O(n)*/
#include<stdio.h>
const int maxnum = 100010;
int main() {
  int n,i,A[maxnum];
  scanf("%d\n",&n);
  for(i=0;i<n;i++)
   scanf("%d",&A[i]);
  printf("%d\n",findmax(A,n));
  return 0;
  }
int findmax(int A[],int n) {
  int max=0,thisnum=0;
  int i;
  for(i=0;i<n;i++){
    thisnum+=A[i];
    if(thisnum>max)
     max=thisnum;
    else if(thisnum<0)
     thisnum=0;
    }
  return max;
}

/*method 2:分治法 T(N)=O(n)*/
#include<stdio.h>
const int maxnum = 100010;
int main() {
  int n,i,A[maxnum];
  scanf("%d\n",&n);
  for(i=0;i<n;i++)
   scanf("%d",&A[i]);
  printf("%d\n",MaxSubseqSum3(A,n));
  return 0;
}
int Max3( int A, int B, int C )
{ /* 返回3个整数中的最大值 */
    return A > B ? A > C ? A : C : B > C ? B : C;
}
 
int DivideAndConquer( int List[], int left, int right )
{ /* 分治法求List[left]到List[right]的最大子列和 */
    int MaxLeftSum, MaxRightSum; /* 存放左右子问题的解 */
    int MaxLeftBorderSum, MaxRightBorderSum; /*存放跨分界线的结果*/
 
    int LeftBorderSum, RightBorderSum;
    int center, i;
 
    if( left == right )  { /* 递归的终止条件，子列只有1个数字 */
        if( List[left] > 0 )  return List[left];
        else return 0;
    }
 
    /* 下面是"分"的过程 */
    center = ( left + right ) / 2; /* 找到中分点 */
    /* 递归求得两边子列的最大和 */
    MaxLeftSum = DivideAndConquer( List, left, center );
    MaxRightSum = DivideAndConquer( List, center+1, right );
 
    /* 下面求跨分界线的最大子列和 */
    MaxLeftBorderSum = 0; LeftBorderSum = 0;
    for( i=center; i>=left; i-- ) { /* 从中线向左扫描 */
        LeftBorderSum += List[i];
        if( LeftBorderSum > MaxLeftBorderSum )
            MaxLeftBorderSum = LeftBorderSum;
    } /* 左边扫描结束 */
 
    MaxRightBorderSum = 0; RightBorderSum = 0;
    for( i=center+1; i<=right; i++ ) { /* 从中线向右扫描 */
        RightBorderSum += List[i];
        if( RightBorderSum > MaxRightBorderSum )
            MaxRightBorderSum = RightBorderSum;
    } /* 右边扫描结束 */
 
    /* 下面返回"治"的结果 */
    return Max3( MaxLeftSum, MaxRightSum, MaxLeftBorderSum + MaxRightBorderSum );
}
 
int MaxSubseqSum3( int List[], int N )
{ /* 保持与前2种算法相同的函数接口 */
    return DivideAndConquer( List, 0, N-1 );
}

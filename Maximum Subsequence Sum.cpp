
//Maximum Subsequence Sum

#include "stdio.h"
#include "stdlib.h"


class MaxSubseqSum{
public:
    long Sum;
    int i,j;
    MaxSubseqSum(long _Sum,int _i,int _j){Sum=_Sum;i=_i;j=_j;}
};


bool operator==(const MaxSubseqSum& m1, const MaxSubseqSum& m2)
{
    if (m1.Sum == m2.Sum && m1.i == m2.i && m1.j ==m2.j) {
        return true;
    }
    return false;
}
bool operator>(const MaxSubseqSum& m1, const MaxSubseqSum& m2)
{
    if (m1.Sum > m2.Sum) return true;
    else if( m1.Sum == m2.Sum && m1.i < m2.i)return true;
    else if (m1.Sum == m2.Sum && m1.i == m2.i && (m1.i+m1.j) < (m2.i+m2.j))return true;
    else return false;
}
bool operator<(const MaxSubseqSum& m1, const MaxSubseqSum& m2)
{
    if (!(m1>m2) && !(m1 == m2)) {
        return true;
    }
    return false;
}
MaxSubseqSum Find_CrossMax(int a[],int i,int mid,int j)
{
    long leftsum=0,sum=0,rightsum=0;
    int maxleft=j,maxright=j;
    for (int x=mid; x>=i; x--) {
        sum+=a[x];
        if(sum>leftsum){
            leftsum = sum;
            maxleft = x;
        }
    }
    sum=0;
    for (int x=mid+1; x<=j; x++) {
        sum+=a[x];
        if(sum>rightsum){
            rightsum = sum;
            maxright = x;
        }
    }
    MaxSubseqSum temp(leftsum+rightsum,maxleft,maxright);
    return temp;
}


MaxSubseqSum Find_MaxSubSum(int a[],int i,int j)
{
    if (i == j) {
        MaxSubseqSum temp(a[i],i,i);
        return temp;
    }
    int Mid = (i + j)/2;
    MaxSubseqSum temp1 = Find_MaxSubSum(a, i, Mid);
    MaxSubseqSum temp2 = Find_MaxSubSum(a, Mid+1, j);
    MaxSubseqSum temp0 = Find_CrossMax(a, i, Mid, j);
    if (temp1 > temp2 && temp1 > temp0) {
        return temp1;
    } else if(temp2 > temp1 && temp2 > temp0){
        return temp2;
    }else{
        return temp0;
    }
    
}

int main(int argc, const char * argv[]) {
    
    int K;int i,j;
    scanf("%d",&K);
    int *a = (int*)calloc(K, sizeof(int));
    for (i=0,j=0; i < K; i++){
        scanf("%d",a+i);
        if (*(a+i)<0) {
            j++;
        }
    }
    if(i == j){printf("%d %d %d",0,a[0],a[K-1]);}
    else {MaxSubseqSum temp = Find_MaxSubSum(a, 0, K-1);
        printf("%ld %d %d",temp.Sum,a[temp.i],a[temp.j]);}
    return 0;
}

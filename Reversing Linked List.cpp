//Reversing Linked List

#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 100000


long ReversewithK(long First,int K,int data[],long next[])
{
    long *tempaddress = (long*)calloc(K,sizeof(long));
    int i;long p=First;
    for (i =0; i<K; i++) {
        tempaddress[i]=p;
        if (next[p] == -1 && i != K-1) return First;
        p=next[p];
    }
    for (i = K-1; i>0; i--) next[tempaddress[i]]=tempaddress[i-1];
    next[tempaddress[0]]=p;
    p=tempaddress[K-1];free(tempaddress);
    return p;
}

int main(int argc,const char* argv[])
{
    int N,K;long p;
    long tempaddress,tempnext;
    int tempdata;
    long *next = (long*)calloc(MAXNUM+1, sizeof(long));next++;
    int *data  = (int*)calloc(MAXNUM+1, sizeof(int));data++;
    
    scanf("%ld%d%d",&next[-1],&N,&K);
    for (int i=0; i < N; i++) {
        scanf("%ld%d%ld",&tempaddress,&tempdata,&tempnext);
        data[tempaddress]=tempdata;
        next[tempaddress]=tempnext;
    }
    p=-1;if(K<2)K=N+1;
    next[p]=ReversewithK(next[p], K,data,next);
    while (1)
    {
        for (int i=0; i<K; i++) {
            p=next[p];
            if(next[p] == -1){printf("%05ld %d %ld\n",p,data[p],next[p]);return 0;}
            if(i != K-1)printf("%05ld %d %05ld\n",p,data[p],next[p]);
            if(i == K-1)printf("%05ld %d %05ld\n",p,data[p],next[p]=ReversewithK(next[p], K,data,next));
            
        }
        
    }
    
}

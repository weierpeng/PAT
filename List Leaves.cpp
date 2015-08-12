

#include <stdio.h>

class Queues {
    int *_q;
    int _front,_rare;
    int _capacity;
    
public:
    Queues(int capacity){
        _capacity = capacity;
        _q = new int[capacity];
        _front=_rare=0;
    }
    int push(int data){
        _front = _front % _capacity;
        _rare = _rare % _capacity;
        if(_front == _rare -1)return -1;
        _q[_front]=data;
        _front++;
        return 0;
    }
    int pop(){
        _front = _front % _capacity;
        _rare = _rare % _capacity;
        if(_front == _rare )return -1;
        return _q[_rare++];
    }
    bool empty(){
        _front = _front % _capacity;
        _rare = _rare % _capacity;
        if(_front == _rare )return true;
        return false;
    }
};

class Buffer {
    int *_c;
    int _top;
    int _capacity;
    
public:
    Buffer(int capacity){
        _capacity = capacity;
        _c = new int[_capacity];
        _top = 0;
    }
    int push(int data){
        if(_top==_capacity)return -1;
        _c[_top++]=data;
        return 0;
    }
    int print(){
        int tag=0,i;
        for (i = 0; i < _top; i++) {
            if(tag)printf(" ");
            printf("%d",_c[i]);
            tag=1;
        }
        return 0;
    }
};

int main(int argc,const char* argv[])
{
    int N;int i;char a,b;
    int L[10],R[10],root[10];
    for (i=0; i<10; i++) {
        L[i]=-1;
        R[i]=-1;
        root[i]=1;
    }
    
    scanf("%d",&N);getchar();
    for (i=0; i<N; i++) {
        scanf("%c %c",&a,&b);getchar();
        if (a == '-')L[i]=-1;
        else {L[i]=a-'0';root[L[i]]=0;}
        if (b == '-')R[i]=-1;
        else {R[i]=b-'0';root[R[i]]=0;}
    }
    Queues q(10);Buffer buff(10);
    for (i=0; i<N; i++)if(root[i]==1)q.push(i);
    
    while (!q.empty()) {
        int l = q.pop();
        if(L[l] == -1 && R[l]==-1){buff.push(l);continue;}
        if(L[l] != -1)q.push(L[l]);
        if(R[l] != -1)q.push(R[l]);
    }
    buff.print();
    return 0;
}

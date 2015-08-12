

#include <stdio.h>


class stack {
    int _top;
    int *_s;
    int _capacity;
    
public:
    stack(int capacity){
        _s = new int[capacity];
        _capacity = capacity;
        _top = 0;
    }
    int push(int data){
        if (_top >= _capacity)return -1;
        _s[_top++] = data;
        return 0;
    }
    int pop(){
        if (_top <= 0)return -1;
        return _s[--_top];
    }
    int top(){
        return _top<=0?-1:_s[_top-1];
    }
    int clear(){
        delete _s;
        _s = new int[_capacity];
        _top=0;
        return 0;
    }
    int empty()
    {
        return _top<=0?1:0;
    }
};

int main(int argc, const char *argv[])
{
    int M,N,K;
    scanf("%d%d%d",&M,&N,&K);
    stack s(M-1);
    int *buffer = new int[N];
    for (int k=0; k < K; k++) {;
        int n;int i=1;int tag=1;
        for (n=0; n<N; n++)scanf("%d",buffer+n);
        n=0;
        while (n < N) {
            if(i == buffer[n]){
                i++;n++;
                continue;
            }else if(s.top() == buffer[n]){
                    n++;s.pop();
                    continue;
            }else if (i < buffer[n]){
                if(s.push(i)==-1){tag=0;break;}
                i++;
                continue;
            }else{
                tag=0;
                break;
            }
        }
        
        
        
        if (tag)printf("YES\n");
        else printf("NO\n");
        s.clear();
    }
    return 0;
}

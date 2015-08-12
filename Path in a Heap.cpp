
#include <iostream>
#include <limits>
using  namespace::std;

class minHeap {
    int *p;
    int n;
    int _capacity;
    
public:
    minHeap(int N){
        p = new int[N+1];
        p[0]=numeric_limits<int>::min();
        n=1;
        _capacity = N;
    }
    ~minHeap(){
        delete p;
    }
    int size(){
        return n-1;
    }
    int capacity(){
        return _capacity;
    }
    void push(int s){
        int i=n++;
        while( p[i/2]>s) {
            p[i]=p[i/2];
            i/=2;
        }
        p[i]=s;
        
    }
    inline void swap(int &a,int &b){int c=a;b=a;a=c;}
    int pop(){
        int re=p[1];
        int temp=p[n];
        n--;
        int child,parent;

        for (parent = 1; parent * 2 <= n; parent = child) {
            child = parent * 2;
            if (child != n && p[child] > p[child+1])child++;
            if (temp <= p[child])break;
            else p[parent]=p[child];
        }
        p[parent]=temp;
        
        return re;
    }
    int operator[] (int i){
        return p[i];
    }
};


int main(int argc,const char* argv[])
{
    ios::sync_with_stdio(false);
    int N,M;int temp;
    cin>>N>>M;
    minHeap H(N);
    for (int i=0; i<N; i++) {
        cin>>temp;
        H.push(temp);
    }
    for (int i=0; i<M; i++) {
        cin>>temp;
        while (temp>1) {
            cout<<H[temp]<<" ";
            temp/=2;
        }
        cout<<H[temp]<<endl;
    }
    
    return 0;
    
}
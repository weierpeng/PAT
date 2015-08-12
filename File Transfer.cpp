
#include <iostream>
#include <string>
using  namespace::std;

class Set {
    int *a;
    int n;
    
public:
    Set(int N){
        a = new int[N+1];
        n=N;
        for (int i=0; i<=N; i++)a[i]=-1;
    }
    ~Set(){delete a;}
    int I(int c1,int c2){
        int c0;
        int r1,r2;
        if(a[c1]<0)r1=c1;else r1=a[c1];
        if(a[c2]<0)r2=c2;else r2=a[c2];
        if (a[r1]>a[r2])c0=r1,r1=r2,r2=c0;
        a[r1]+=a[r2];
        a[r2]=r1;
        for (int i=1; i<=n; i++)
            if(a[i]==r2)a[i]=r1;
        return 0;
    }
    bool C(int c1,int c2){
        int r1,r2;
        if(a[c1]<0)r1=c1;else r1=a[c1];
        if(a[c2]<0)r2=c2;else r2=a[c2];
        return r1 == r2;
    }
    int S(){
        int m=0;
        for (int i=1; i<=n; i++) {
            if (a[i]<0)m++;
        }
        return m;
    }
    int size(){return n;}
};


int main(int argc,const char* argv[])
{
    ios::sync_with_stdio(false);
    int N;
    cin>>N;
    string op;
    int c1,c2;
    Set S(N);

    while (cin>>op && op[0]!='S') {
        cin>>c1>>c2;
        if (op[0]=='I') {
            S.I(c1, c2);
        }else if (op[0]=='C'){
            cout<< (S.C(c1, c2)?"yes":"no")<<endl;
        }
    }
    c1 = S.S();
    if(c1 == 1)cout<<"The network is connected."<<endl;
    else printf("There are %d components.\n",c1);
    return 0;
}
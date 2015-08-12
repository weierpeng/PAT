


#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <math.h>

using namespace::std;

int Pre_order(int tree[],int pos,int Sn,vector<int>& p){
    if (pos > Sn) return 0;
    Pre_order(tree, pos*2,Sn,p);
    if (p.empty())tree[pos]=-1;
    else {
        tree[pos]=p[0];
        p.erase(p.begin());
    }
    Pre_order(tree, pos*2+1, Sn, p);
    return 0;
    
}



int main(int argc,const char* argv[])
{
    int N,temp;
    int tag=1;
    vector<int> p;
    cin >> N;
    for (int i=0; i < N; i++) {
        cin>>temp;
        p.push_back(temp);
    }
    sort(p.begin(), p.end());
    int *tree = new int[N+1];
    Pre_order(tree, 1, N, p);
    
    for (int i=1;i<=N; i++) {
        if (tag) {
            cout<<tree[i];
            tag=0;
        }else
            cout<<" "<<tree[i];
        
        
    }
    
    return 0;
    
}
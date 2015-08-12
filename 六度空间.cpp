
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cstring>
#include <math.h>
using namespace::std;


class Graph {
    int *V;
    int **E;
    int n;
    bool *visited;
    int *depth;
    
public:
    Graph(int _n):n(_n){
        V=new int[n];
        memset(V, 0, (n)*sizeof(int));
        visited=new bool[n];
        depth = new int[n];
        reset();
        E=new int*[n];
        for (int i=0;i<n; i++){
            E[i]=new int[n];
            memset(E[i], 0, n*sizeof(int));
        }
    }
    ~Graph(){
        delete V;
        for (int i=0;i<n; i++)delete  E[i];
        delete E;
        delete depth;
    }
    int addEdge(int i,int j,int f=1){
        E[i][j]=f;
        E[j][i]=f;
        return 0;
    }
    size_t BSF(int i0,int c){
        queue<int> q;
        vector<int> s;
        q.push(i0);
        visited[i0]=true;
        depth[i0]=c;
        while (!q.empty()) {
            int i=q.front();
            q.pop();
            s.push_back(i);
            if (depth[i]==0)continue;
            for (int j=0; j<n; j++) {
                if (E[i][j]==1 && visited[j]==false){
                    q.push(j);
                    depth[j]=depth[i]-1;
                    visited[j]=true;
                }
            }
            
        }

        reset();
        return s.size();
    }
    void reset(){
        for (int i=0;i<n; i++){
           visited[i]=false;
        }
        memset(depth, 0, n*sizeof(int));
    }
};

int main(){
    ios::sync_with_stdio(false);
    int N,M;
    int i,j;
    cin>>N>>M;
    Graph G(N);
    for (int k=0; k<M; k++) {
        cin>>i>>j;
        G.addEdge(i-1, j-1);
    }
    for (int k=1; k<=N; k++) {
        printf("%d: %.2lf%%\n",k,100.*G.BSF(k-1, 6)/N);
    }
    return 0;
}
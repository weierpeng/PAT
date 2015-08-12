
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <string.h>
using namespace::std;


class Graph {
    int *V;
    int **E;
    int n;
    bool *visited;
    
public:
    Graph(int _n):n(_n){
        V=new int[n];
        memset(V, 0, n*sizeof(int));
        visited=new bool[n];
        for (int i=0;i<n; i++)visited[i]=false;
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
    }
    int addEdge(int i,int j,int f=1){
        E[i][j]=f;
        E[j][i]=f;
        return 0;
    }
    vector<string> BSF(){
        queue<int> q;
        vector<string> v;
        for (int component=0; component<n; component++) {
            string s;
            if (visited[component]==false){
                q.push(component);
                visited[component]=true;
                while (!q.empty()) {
                    int i=q.front();
                    q.pop();
                    s.push_back(i+'0');
                    for (int j=0; j<n; j++) {
                        if (E[i][j]==1 && visited[j]==false){
                            q.push(j);
                            visited[j]=true;
                        }
                    }
                }
                v.push_back(s);
            }
        }
        for (int i=0;i<n; i++)visited[i]=false;
        return v;
    }
    vector<string> DSF(){
        vector<string> v;
        for (int component=0; component<n; component++) {
            if (visited[component]==false){
                string s=dsf(component);
                v.push_back(s);
            }
        }
        for (int i=0;i<n; i++)visited[i]=false;
        return v;
    }
    string dsf(int i){
        string temp;
        temp.push_back(i+'0');
        visited[i]=true;
        for (int j=0; j<n; j++) {
            if (E[i][j]==1 && visited[j]==false){
                temp+=dsf(j);
            }
        }
        return temp;
    }
};

int coutWithGraph(ostream& out ,vector<string>& p){
    
    for (vector<string>::iterator iter=p.begin(); iter!=p.end(); iter++) {
        out<<"{ ";
        for (string::iterator i=iter->begin(); i!=iter->end(); i++) {
            out<<*i<<' ';
        }
        out<<'}'<<endl;
    }
    
    return 0;
}
int main()
{
    int N,E;
    int i,j;
    cin>>N>>E;
    Graph G(N);
    while (E--) {
        cin>>i>>j;
        G.addEdge(i, j);
    }
    vector<string> p2=G.BSF();
    vector<string> p1=G.DSF();
    coutWithGraph(cout,p1);
    coutWithGraph(cout,p2);
    return 0;
}





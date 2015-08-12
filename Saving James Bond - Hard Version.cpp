
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cstring>
#include <math.h>
#include <limits>
#include <stack>
using namespace::std;


class Graph {
    int *V;
    double **E;
    double *E0;
    int n;
    bool *visited;
    
public:
    Graph(int _n):n(_n){
        V=new int[n];
        memset(V, 0, (n)*sizeof(int));
        visited=new bool[n];
        for (int i=0;i<n; i++)visited[i]=false;
        E=new double*[n];
        E0= new double[n*n];
        for (int i=0;i<n*n;i++)E0[i]=-1.;
        for (int i=0;i<n; i++){
            E[i]=&(E0[i*n]);
        }
    }
    ~Graph(){
        delete V;
        delete E;
        delete E0;
    }
    int addEdge(int i,int j,double f=1){
        E[i][j]=f;
        E[j][i]=f;
        return 0;
    }
    bool isTwoVerticesConnected(int _i,int _j){
        queue<int> q;
        q.push(_i);
        visited[_i]=true;
        while (!q.empty()) {
            int i=q.front();
            q.pop();
            if (i==_j){
                for (int i=0;i<n; i++)visited[i]=false;
                return true;
            }
            for (int j=0; j<n; j++) {
                if (E[i][j]==1 && visited[j]==false){
                    q.push(j);
                    visited[j]=true;
                }
            }
            
        }
        for (int i=0;i<n; i++)visited[i]=false;
        return false;
    }
    queue<int> shorttestPath(int _i,int _j){
        
        int *dist=new int[n];
        for (int i=0; i<n; i++) {
            dist[i]=numeric_limits<int>::max();
        }
        bool *collected=new bool[n]();
        for (int i=0; i<n; i++) {
            collected[i]=false;
        }
        int *path=new int[n]();
        for (int i=0; i<n; i++) {
            path[i]=-1;
        }
        int j;
        dist[_i]=0;
        auto lamda = [dist,collected](int n){
            int temp = numeric_limits<int>::max();
            int j = -1;
            for (int i=0; i<n; i++) {
                if (collected[i]==false && dist[i]<temp) {
                    j=i;
                    temp=dist[i];
                }
            }
            return j;
        };
        while ((j=lamda(n))!=-1) {
            collected[j]=true;
            for (int i=0 ; i < n ; i++) {
                if(E[j][i]>0 && collected[i]==false && dist[j]+E[j][i]<dist[i]){
                    dist[i]=dist[j]+1;
                    path[i]=j;
                }
    
            }
        }
        queue<int> q;
        if (path[_j]>=0) {
            for (int i=0 ; i < n ; i++) {
                if( E[_j][i]>0  && (dist[_j]-1==dist[i])){
                    if (E[_j][i]<E[_j][path[_j]]){
                        path[_j]=i;
                    }
                }
            }
            while ((_j=path[_j])!=_i && _j>=0){
                q.push(_j);
            }
        }
        return q;
    }
    
};


class Points {
    int x,y;
public:
    Points(int _x=0,int _y=0):x(_x),y(_y){}
    friend istream& operator>>(istream& in,Points& p){
        if(in)in>>p.x>>p.y;
        return in;
    }
    double distFromPoint(Points& p){
        return sqrt((this->x-p.x)*(this->x-p.x)+(this->y-p.y)*(this->y-p.y));
    }
    int distFromBound(){
        int d1=50-abs(this->x);
        int d2=50-abs(this->y);
        return d1<d2?d1:d2;
    }
    friend ostream& operator<<(ostream& o,Points& p){
        if(o)o<<p.x<<' '<<p.y<<endl;
        return o;
    }
};


const double diameter = 15;
const double radius = diameter/2;
const int dx=2;
int main()
{
    int N,D;
    cin>>N>>D;
    Points *p=new Points[N];
    Points p0(0,0);
    Graph G(N+dx);
    double dist;
    for (int i=0; i<N; i++) {
        cin>>p[i];
        if ((dist=p[i].distFromBound())<=D)G.addEdge(0, i+dx,dist);
        if ((dist=p[i].distFromPoint(p0)-radius)<=D)G.addEdge(1, i+dx,dist);
        for (int j=0; j<i; j++)
            if((dist=p[i].distFromPoint(p[j]))<=D){
                G.addEdge(i+dx, j+dx,dist);
            }
    }
    if (radius+D>=50) {
        cout<<1<<endl;
    }else{
        queue<int> q = G.shorttestPath(0,1);
        if(!q.empty()){
            cout<<q.size()+1<<endl;
            while (!q.empty()){
                cout<<p[q.front()-dx];
                q.pop();
            }
        }else{
            cout<<0<<endl;
        }
    }
    return 0;
}





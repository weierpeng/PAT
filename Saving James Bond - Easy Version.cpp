
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
    
public:
    Graph(int _n):n(_n){
        V=new int[n];
        memset(V, 0, (n)*sizeof(int));
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
};


const double diameter = 15;
const double radius = diameter/2;
const int dx=2;
int main()
{
    int N,D;
    cin>>N>>D;
    if (D>=50-radius) {
        cout<<"Yes"<<endl;
        return 0;
    }
    Points *p=new Points[N];
    Points p0(0,0);
    Graph G(N+dx);
    for (int i=0; i<N; i++) {
        cin>>p[i];
        if (p[i].distFromBound()<=D)G.addEdge(0, i+dx);
        if (p[i].distFromPoint(p0)<=D+radius)G.addEdge(1, i+dx);
        for (int j=0; j<i; j++)
            if(p[i].distFromPoint(p[j])<=D){
                G.addEdge(i+dx, j+dx);
            }
    }
    cout<<(G.isTwoVerticesConnected(0, 1)?"Yes":"No")<<endl;
    return 0;
}





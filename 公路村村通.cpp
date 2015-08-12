


#include <iostream>
#include <limits>
#include <queue>

using namespace::std;

template <class EdgeType,class VertexType>
class Graph {
    VertexType *V;
    EdgeType **E;
    EdgeType *E0;
    size_t n;
    bool *visited;
    
public:
    Graph(size_t _n):n(_n){
        V = new VertexType[n];
        visited = new bool[n];
        for (int i=0;i<n; i++)visited[i]=false;
        E = new EdgeType*[n];
        E0= new EdgeType[n*n];
        for (int i=0;i<n*n;i++)E0[i]=-1;
        for (int i=0;i<n; i++){
            E[i]=&(E0[i*n]);
        }
    }
    ~Graph(){
        delete V;
        delete E;
        delete E0;
    }
    int addEdge(VertexType i,VertexType j,const EdgeType& f){
        E[i][j]=f;
        E[j][i]=f;
        return 0;
    }
    EdgeType getShortestPath(int _i,int _j){
        
        EdgeType *dist=new EdgeType[n];
        for (int i=0; i<n; i++) {
            dist[i].setMax();
        }
        bool *collected=new bool[n]();
        for (int i=0; i<n; i++) {
            collected[i]=false;
        }
        int *path=new int[n];
        for (int i=0; i<n; i++) {
            path[i]=-1;
        }
        dist[_i]=0;
        auto lamda = [dist,collected](size_t n){
            EdgeType temp;
            temp.setMax();
            int j = -1;
            for (int i=0; i<n; i++) {
                if (collected[i]==false && dist[i]<temp) {
                    j=i;
                    temp=dist[i];
                }
            }
            return j;
        };
        int j;
        while ((j=lamda(n))!=-1) {
            collected[j]=true;
            for (int i=0 ; i < n ; i++) {
                if(E[j][i]!=-1 && dist[j]+E[j][i]<dist[i]){
                    dist[i]=dist[j]+E[j][i];
                    path[i]=j;
                }
            }
        }
        return dist[_j];
    }
    EdgeType getEdge(VertexType i,VertexType j){
        return E[i][j];
    }
    EdgeType Prim(){
        EdgeType *dist=new EdgeType[n];
        EdgeType cost;
        for (int i=0; i<n; i++) {
            dist[i].setMax();
        }
        bool *collected=new bool[n]();
        for (int i=0; i<n; i++) {
            collected[i]=false;
        }
        int *path=new int[n];
        for (int i=0; i<n; i++) {
            path[i]=-1;
        }
        dist[0]=0;
        auto lamda = [dist,collected](size_t n){
            EdgeType temp;
            temp.setMax();
            int j = -1;
            for (int i=0; i<n; i++) {
                if (collected[i]==false && dist[i]<temp) {
                    j=i;
                    temp=dist[i];
                }
            }
            return j;
        };
        int j;
        while ((j=lamda(n))!=-1) {
            collected[j]=true;
            cost+=dist[j];
            for (int i=0 ; i < n ; i++) {
                if(E[j][i]!=-1 && E[j][i]<dist[i]){
                    dist[i]=E[j][i];
                    path[i]=j;
                }
            }
        }
        for (int i=0; i<n; i++) {
            if(collected[i]==false){
                cost=-1;
            }
        }
        return cost;
    }
};

class line {
public:
    int distance;
    int fee;
    line(){
        this->distance=0;
        this->fee=0;
    }
    line(const line& r){
        this->distance=r.distance;
        this->fee=r.fee;
    }
    line& operator+=(const line& r){
        this->distance+=r.distance;
        this->fee+=r.fee;
        return *this;
    }
    line& operator-=(const line& r){
        this->distance-=r.distance;
        this->fee-=r.fee;
        return *this;
    }
    bool operator<(const line& r){
        if(this->distance<r.distance)return true;
        else if(this->distance==r.distance && this->fee<r.fee)return true;
        return false;
    }
    friend istream& operator>>(istream& in,line& t){
        if(in){
            cin>>t.distance>>t.fee;
        }
        return in;
    }
    void setMax(void){
        this->distance=numeric_limits<int>::max();
        this->fee=numeric_limits<int>::max();
    }
    line operator=(const int i){
        this->distance=i;
        this->fee=i;
        return *this;
    }
    bool operator==(const int i){
        if(this->distance==i && this->fee==i)return true;
        return false;
    }
    bool operator!=(const int i){
        return !(*this==i);
    }
};
line operator+(const line& s,const line& r){
    line temp(s);
    temp+=r;
    return temp;
}

int main()
{
    int N,M;
    cin>>N>>M;
    Graph<line, int> G(N);
    while (M--) {
        line temp;
        int i,j,k;
        cin>>i>>j>>k;
        temp.fee=k;
        G.addEdge(i-1, j-1, temp);
        
    }
    line q=G.Prim();
    cout<<q.fee<<endl;
    return 0;
}
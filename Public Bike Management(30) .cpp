//
//  Public Bike Management .cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/4.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//


#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
#include <stack>
using namespace std;
template <typename T,typename E>
class Graph {
protected:
    size_t numEdges;
    size_t numVertices;
    size_t maxVertices;
    virtual size_t getVertexPos(T vertex);
    
public:
    const E maxWeight;
    Graph();
    virtual ~Graph();
    bool GraphEmpty() const{
        if (numEdges == 0) return true;
        else return false;
    }
    bool GraphFull() const{
        if (!GraphEmpty() && numEdges == numVertices * (numVertices - 1) / 2) {
            return true;
        }
        else return false;
    }
    size_t NumberOfVertices(){return numVertices;}
    size_t NumberOfEdges(){return numEdges;}
    virtual T getValue(int i);
    virtual E getWeight(int v1,int v2);
    virtual int getNeighbor(int v);
    virtual bool insertVertex(const T& vertex);
    virtual bool insertEdge(int v1,int v2,E cost);
    virtual bool removeVertex(int v);
    virtual bool removeEdge(int v1,int v2);
};

template <typename T,typename E>
class Graphmtx {
protected:
    vector<T> VerticeList;
    E ** Edge;
    size_t n;
public:
    Graphmtx(size_t n):VerticeList(n),n(n),path(n),d(n),collected(n){
        Edge = (E**)new E*[n];
        for (int i=0; i<n; i++) {
            Edge[i]=new E[n];
            for (int j=0; j<n; j++) {
                Edge[i][j]=0;
            }
        }
    }
    ~Graphmtx(){
        for (int i=0; i<n; i++) {
            Edge[i]=new E[n];
            for (int j=0; j<n; j++) {
                Edge[i][j]=0;
            }
        }
    }
    bool insertEdge(int v1,int v2,E cost){
        Edge[v1][v2] = cost;
        Edge[v2][v1] = cost;
        return true;
    }
    vector<int> getNeighbor(int v){
        vector<int> p;
        for (int i=0; i < n; i++) {
            if (Edge[v][i] > 0) {
                p.push_back(i);
            }
        }
        return p;
    }
    bool removeVertex(int v){
        for (int i=0; i < n; i++) {
            Edge[v][i]=0;
            Edge[i][v]=0;
        }
    }
    bool insertVertex(const T& vertex){
        VerticeList.pushback(vertex);
        return true;
    }
    T& getValue(int i){
        return VerticeList[i];
    }
    E& getWeight(int v1,int v2){
        return Edge[v1][v2];
    }
    stack<T> minPath(int i,int j){

        for (int i=0; i<n; i++) {
            path[i]=-1;
            collected[i]=false;
            d[i]=numeric_limits<int>::max();
        }

        d[i]=0;
        int k;
        while ((k=min(VerticeList[j]))!=-1){
            collected[k]=true;
            vector<int> ner = getNeighbor(k);
            for (int i=0; i<ner.size();i++) {
                if (d[k]+getWeight(k, ner[i])<d[ner[i]]) {
                    d[ner[i]] = d[k]+getWeight(k, ner[i]);
                    path[ner[i]]=k;
                }
            }
        }
        stack<int> s;
        s.push(j);
        k=j;
        while ((k=path[k])!=-1) {
            s.push(k);
        }
        return s;
    }
    int min(int z){
        bool flag=false;
        int k=-1;
        for (int i=0; i<n; i++) {
            if (collected[i]==false) {
                if (!flag) {
                    k=i;
                    flag=true;
                    continue;
                }
                if (cmp(i, k, z)) {
                    k=i;
                }
            }
        }
        return k;
    }
    bool cmp(int v1,int v2,int flag){
        if (d[v1]<d[v2]) {
            return true;
        }else if (d[v1] == d[v2]){
            return (VerticeList[v1]>VerticeList[v2]);
        }
        return false;
    }
private:
    vector<int> path;
    vector<int> d;
    queue<int> q;
    vector<int> collected;
};

int main(int argc,const char* argv[]){
    int Cmax,N,Sp,M;
    cin>>Cmax>>N>>Sp>>M;
    Graphmtx<int, int> G(N+1);
    for (int i=0; i<N; i++) {
        int temp;
        cin>>temp;
        G.getValue(i+1)=temp-Cmax/2;
        
    }
    for (int i=0; i<M; i++) {
        int v1,v2,cost;
        cin>>v1>>v2>>cost;
        G.insertEdge(v1,v2,cost);
    }
    stack<int> s = G.minPath(0, Sp);
    vector<int> path;
    path.push_back(s.top());
    s.pop();
    int k = 0;
    int a[2]={0};
    while (!s.empty()) {
        int i = s.top();
        k+=G.getValue(i);
        if (k<0) {
            a[0]+=-k;
            k=0;
        }
        s.pop();
        path.push_back(i);
    }

    if (k>0) {
        a[1]=k;
    }
    cout<<a[0]<<' '<<path[0];
    for (int i=1; i<path.size(); i++) {
        cout<<"->"<<path[i];
    }
    cout<<' '<<a[1]<<endl;
    return 0;
}

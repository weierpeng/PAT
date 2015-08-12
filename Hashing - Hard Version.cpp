//
//  Hashing - Hard Version.cpp
//  TestAllThings
//
//  Created by 彭威 on 15/8/3.
//  Copyright © 2015年 NJU. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
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
    Graphmtx(size_t n):VerticeList(n),n(n){
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
    bool insertEdge(int v1,int v2){
        Edge[v1][v2] = 1;
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
};

int main(int argc,const char* argv[]){
    int N;
    cin>>N;
    vector<int> hash_table(N);
    for (int i=0; i < N; ++i) {
        cin>>hash_table[i];
    }
    vector<int> count(N);
    Graphmtx<int, int> G(N);
    for (int i=0; i < hash_table.size(); i++) {
        int j = hash_table[i]%N;
        if (hash_table[i]<0) {
            continue;
        }else if (j < i) {
            while (j!=i) {
                G.insertEdge(j, i);
                count[i]++;
                j++;
            }
        }else if (j > i){
            while (j!=i+N) {
                G.insertEdge(j%N, i);
                count[i]++;
                j++;
            }
        }
    }
    auto x = [hash_table](int a,int b){
        return hash_table[a]<hash_table[b];
    };
    vector<int> result;
    while (result.size()<N) {
        int temp = -1;
        for (int i=0; i<N; i++) {
            if (count[i]==0) {
                if (temp==-1) {
                    temp = i;
                }
                if (hash_table[i]< hash_table[temp]){
                    temp = i;
                }
                
            }
        }
        count[temp]=-1;
        
        vector<int> ner=G.getNeighbor(temp);
        for (int j=0; j<ner.size(); j++) {
            count[ner[j]]--;
        }
        

        result.push_back(temp);
    }
    int flag=0;
    for (int i=0; i<result.size(); i++) {
        if (hash_table[result[i]]<0) {
            continue;
        }
        if(flag == 0) {
            cout<<hash_table[result[i]];
            flag++;
        }else{
            cout<<' '<<hash_table[result[i]];
        }
    }
    cout<<endl;
    return 0;
}

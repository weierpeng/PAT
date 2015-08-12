//
//  Forwards on Weibo (30).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/9.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <vector>
#include <memory>
#include <memory.h>
#include <queue>
using namespace std;
class Graph {
    vector<vector<size_t>> neighborList;
    int *node;
    int L;
    size_t n;
    
public:
    Graph(size_t n):n(n){
        node = new int[n];
        neighborList.resize(n);
    }
    bool addEdge(size_t i,size_t j){
        neighborList[i].push_back(j);
        return true;
    }
    size_t countWithLevel(size_t i,int L){
        clear();
        node[i]=0;
        queue<size_t> q;
        size_t count=0;
        q.push(i);
        while (!q.empty()) {
            size_t j=q.front();
            q.pop();
            if (node[j]>L) {
                continue;
            }
            count++;
            for (auto k:neighborList[j]){
                if (node[k]==-1) {
                    node[k]=node[j]+1;
                    q.push(k);
                }
            }
        }
        return count-1;
    }
    void clear(){
        memset(node, -1, n*sizeof(int));
    }
};
int main(int argc,const char* argv[]){
    ios::sync_with_stdio(false);
    int N,L;
    cin>>N>>L;
    Graph G(N+1);
    for (int i=1; i<=N; i++) {
        int n;
        cin>>n;
        for (int j=0; j<n; j++) {
            int k;
            cin>>k;
            G.addEdge(k, i);
        }
    }
    int n;
    cin>>n;
    for (int i=0; i<n; i++) {
        size_t j;
        cin>>j;
        cout<<G.countWithLevel(j,L)<<endl;
    }
    return 0;
}

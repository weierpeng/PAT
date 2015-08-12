//
//  Acute Stroke (30).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/6.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
vector<vector<vector<int>>> Q;
vector<vector<vector<bool>>> V;
struct xyz {
    int a[3];
    xyz(int i,int j,int k){
        a[0]=i;
        a[1]=j;
        a[2]=k;
    }
    bool valid(){
        return (!V[a[0]][a[1]][a[2]] && Q[a[0]][a[1]][a[2]]);
    }
};
vector<xyz> validNeighbor(xyz p){
    xyz temp(p);
    vector<xyz> re;
    for (int i=0; i<3; i++) {
        temp.a[i]+=1;
        if (temp.valid()) {
            re.push_back(temp);
        }
        temp.a[i]-=2;
        if (temp.valid()) {
            re.push_back(temp);
        }
        temp.a[i]+=1;
    }
    
    return re;
}
int BFS(int i,int j,int k){
    queue<xyz> q;
    int m=0;
    xyz p(i, j, k);
    V[p.a[0]][p.a[1]][p.a[2]]=true;
    q.push(p);
    while (!q.empty()) {
        xyz p = q.front();
        q.pop();
        ++m;
        vector<xyz> x=validNeighbor(p);
        for (int i=0; i<x.size(); i++) {
            V[x[i].a[0]][x[i].a[1]][x[i].a[2]]=true;
            q.push(x[i]);
        }
    }
    return m;
}
int main(int argc,const char* argv[]){
    ios::sync_with_stdio(false);
    int M,N,L,T;
    long long VV=0;
    cin>>M>>N>>L>>T;
    Q.resize(L+2);
    V.resize(L+2);
    for (int i=0; i<L+2; i++) {
        Q[i].resize(M+2);
        V[i].resize(M+2);
        for (int j=0; j<M+2; j++) {
            Q[i][j].resize(N+2, 0);
            V[i][j].resize(N+2, false);
        }
    }
    for (int i=1; i<L+1; i++) {
        for (int j=1; j<M+1; j++) {
            for (int k=1; k<N+1; k++) {
                cin>>Q[i][j][k];
            }
        }
    }
    for (int i=1; i<L+1; i++) {
        for (int j=1; j<M+1; j++) {
            for (int k=1; k<N+1; k++) {
                if(Q[i][j][k] && !V[i][j][k]){
                    int m = BFS(i,j,k);
                    if (m<T) {
                        continue;
                    }
                    VV+=m;
                }
            }
        }
    }
    cout<<VV<<endl;
    return 0;
}
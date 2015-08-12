//
//  All Roads Lead to Rome (30).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/5.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <limits>
using namespace std;

class Graphm {
    int n;
    vector<int> V;
    vector<vector<int>> E;
    vector<bool> visited;
    vector<int> path;
    vector<int> num;
    vector<int> happy;
    vector<int> bypass;
    vector<int> d;
    int cost_min;
    int happiness_max;
    vector<int> final_path;

    
public:
    vector<string> index;
    Graphm(int n):n(n),V(n),E(n),visited(n),num(n),happy(n),bypass(n),d(n),path(n){
        for (int i=0; i<n; i++) {
            vector<int> temp(n);
            E[i]=temp;
        }
    }
    bool addEdge(int v1,int v2,int cost){
        E[v1][v2]=cost;
        E[v2][v1]=cost;
        return true;
    }
    int& getV(int i){
        return V[i];
    }
    vector<int> getNear(int z){
        vector<int> near;
        vector<int> near_cost;
        for (int i=0; i<n ; i++) {
            if (E[z][i]>0 && !visited[i]) {
                near.push_back(i);
                near_cost.push_back(E[z][i]);
            }
        }
        return near;
    }
    void dijkstra(int begin,int end){
        for (int i=0; i<n; i++) {
            visited[i]=false;
            bypass[i] = d[i] = numeric_limits<int>::max();
            num[i] = happy[i] = 0;
            path[i] = -1;
        }
        d[begin]=0;
        visited[begin]=0;
        num[begin]=1;
        bypass[begin]=0;
        for (int i=0; i<n; i++) {
            int k=-1;
            for (int j=0; j<n; j++) {
                if (!visited[j] && (k<0 || d[j]<d[k])) {
                    k=j;
                }
            }
            visited[k]=true;
            for (int j=0; j<n; j++) {
                if (!visited[j] && E[k][j]>0) {
                    int cost = d[k]+E[k][j];
                    if (cost<d[j]) {
                        d[j]=cost;
                        num[j]=num[k];
                        path[j]=k;
                        happy[j]=happy[k]+V[j];
                        bypass[j]=bypass[k]+1;
                    }else if (cost == d[j]){
                        num[j]+=num[k];
                        if (happy[j]<happy[k]+V[j] ||
                            (happy[j]==happy[k]+V[j] && bypass[j]>bypass[k]+1)) {
                            d[j]=cost;
                            path[j]=k;
                            happy[j]=happy[k]+V[j];
                            bypass[j]=bypass[k]+1;
                        }
                    }
                }
            }
        }
    }
    void out(int i){
        cout<<num[i]<<' '
            <<d[i]<<' '
            <<happy[i]<<' '
            <<happy[i]/bypass[i]
            <<endl;
        print_path(i);
    }
    void print_path(int i){
        if (path[i]!=-1) {
            print_path(path[i]);
            cout<<"->";
        }
        cout<<index[i];
    }

};

int main(int argc,const char* argv[]){
    int N,M;
    cin>>N>>M;
    Graphm G(N);
    map<string, int> index;
    vector<string> dict;
    string city;
    int happiness;
    cin>>city;
    dict.push_back(city);
    index[city]=0;
    for (int i=1; i<N; i++) {
        cin>>city>>happiness;
        G.getV(i)=happiness;
        index[city]=i;
        dict.push_back(city);
    }
    string c1,c2;
    int cost;
    for (int i=0; i<M; i++) {
        cin>>c1>>c2>>cost;
        G.addEdge(index[c1],index[c2],cost);
    }
    G.index=dict;
    G.dijkstra(0, 1);
    G.out(index["ROM"]);
    cout<<endl;
    return 0;
}
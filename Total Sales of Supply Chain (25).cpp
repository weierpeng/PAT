//
//  Total Sales of Supply Chain (25).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/9.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
int N;
double P,r;
double total;
struct Tree {
    bool retailer;
    double P;
    int amount;
    vector<int> next;
};
int Traveral(vector<Tree>& nodes){
    nodes[0].P=P;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int i=q.front();
        q.pop();
        if (nodes[i].retailer) {
            total+=nodes[i].amount * nodes[i].P;
        }
        for (auto j:nodes[i].next){
            q.push(j);
            nodes[j].P=nodes[i].P*(1+r/100);
        }
    }
    return 0;
}
int main(int argc,const char* argv[]){
    ios::sync_with_stdio(false);

    cin>>N>>P>>r;
    vector<Tree> nodes(N);
    for (int i=0; i<N; i++) {
        int k;
        cin>>k;
        if (k==0) {
            nodes[i].retailer=true;
            cin>>nodes[i].amount;
        }else{
            for (int j=0; j<k; j++) {
                int temp;
                cin>>temp;
                nodes[i].next.push_back(temp);
            }
        }
    }
    Traveral(nodes);
    printf("%.1lf",total);
    return 0;
}
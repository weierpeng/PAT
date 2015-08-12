//
//  Build A Binary Search Tree (30).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/9.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct node {
    int key;
    node* next[2];
};
vector<node> nodes;
vector<int> a;
bool func(int &key){
    static int i=0;
    key=a[i++];
    return true;
}
int LDR(node* i){
    node* l=i->next[0];
    node* r=i->next[1];
    if (l!=nullptr) {
        LDR(l);
    }
    if (!func(i->key)) {
        return 1;
    }
    if (r!=nullptr) {
        LDR(r);
    }
    return 0;
}
vector<int> LevelTraversal(){
    queue<node*> q;
    vector<int> temp;
    q.push(&nodes[0]);
    while (!q.empty()) {
        node* p = q.front();
        q.pop();
        temp.push_back(p->key);
        if (p->next[0]!=nullptr) {
            q.push(p->next[0]);
        }
        if (p->next[1]!=nullptr) {
            q.push(p->next[1]);
        }
    }
    return temp;
}
int main(int argc,const char* argv[]){
    ios::sync_with_stdio(false);
    int N;
    cin>>N;
    nodes.resize(N);
    for (int i=0; i<N; i++) {
        int l,r;
        cin>>l>>r;
        if (l!=-1) {
            nodes[i].next[0]=&nodes[l];
        }else{
            nodes[i].next[0]=nullptr;
        }
        if (r!=-1) {
            nodes[i].next[1]=&nodes[r];
        }else{
            nodes[i].next[1]=nullptr;
        }
    }
    a.resize(N);
    for (int i=0; i<N; i++) {
        cin>>a[i];
    }
    sort(a.begin(), a.end());
    LDR(&nodes[0]);
    a = LevelTraversal();
    cout<<a[0];
    for (int i=1; i<a.size(); i++) {
        cout<<' '<<a[i];
    }
    cout<<endl;
    return 0;
}

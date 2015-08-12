//
//  The Largest Generation (25).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/7.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
using namespace std;

struct pedigree {
    pedigree* parent;
    int depth;
    vector<pedigree*> children;
};
int main(int argc,const char* argv[]){
    map<string, pedigree*> dict;
    int N,M;
    cin>>N>>M;
    for (int i=0; i<M; i++) {
        string ID;
        int K;
        cin>>ID>>K;
        if (dict.find(ID)==dict.end()) {
            pedigree *node = new pedigree;
            dict[ID]=node;
        }
        
        for (int j=0; j<K; j++) {
            string child;
            cin>>child;
            if (dict.find(child)==dict.end()) {
                pedigree *node = new pedigree;
                dict[child]=node;
            }
            dict[ID]->children.push_back(dict[child]);
            dict[child]->parent = dict[ID];
        }
    }
    queue<pedigree*> Q;
    Q.push(dict["01"]);
    dict["01"]->depth=1;
    int max_depth=0;
    int max_count=0;
    int depth=0;
    int count=0;
    while (!Q.empty()) {
        pedigree *node = Q.front();
        Q.pop();
        if (node->depth!=depth) {
            if (count>max_count) {
                max_count =count;
                max_depth =depth;
            }
            count=1;
            depth=node->depth;
        }else if(node->depth == depth){
            count++;
        }
        for (auto iter = node->children.begin(); iter!=node->children.end(); ++iter) {
            (**iter).depth = depth+1;
            Q.push(*iter);
        }
    }
    cout<<max_count<<' '<<max_depth<<endl;
    return 0;
}
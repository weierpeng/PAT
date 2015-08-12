//
//  Deduplication on a Linked List (25).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/8.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;
struct node {
    int key;
    long next;
};
int abs(int k){
    return k>0?k:-k;
}
int print(node* mem, long begin){
    while (mem[begin].next != -1) {
        printf("%05ld %d %05ld\n",begin,mem[begin].key,mem[begin].next);
        begin=mem[begin].next;
    }
    printf("%05ld %d %ld\n",begin,mem[begin].key,mem[begin].next);
    return 0;
}
int main(int argc,const char* argv[]){
    ios::sync_with_stdio(false);
    long begin,d_begin=-1;
    int K;
    node* mem = new node[100000];
    cin>>begin>>K;
    for (int i=0; i<K; i++) {
        size_t pos;
        cin>>pos;
        cin>>(mem[pos].key);
        cin>>(mem[pos].next);
    }
    unordered_set<int> keys(K);
    keys.insert(abs(mem[begin].key));
    long p1=begin,p2=mem[begin].next,p3=-1;
    while (p2!=-1) {
        if (keys.count(abs(mem[p2].key))!=0) {
            if (p3==-1) {
                p3=p2;
                d_begin=p3;
            }else{
                mem[p3].next=p2;
                p3=p2;
            }
            mem[p1].next=mem[p2].next;
        }else{
            keys.insert(abs(mem[p2].key));
            p1=p2;
        }
        p2=mem[p2].next;
    }
    mem[p3].next=-1;
    print(mem,begin);
    if (d_begin!=-1) {
        print(mem,d_begin);
    }
    return 0;
}

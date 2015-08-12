//
//  main.cpp
//  散列1. Hashing
//
//  Created by 彭威 on 15/7/25.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <vector>
using namespace::std;

int MSize,N;

bool isPrime(int n){
    if (n <= 1) {
        return false;
    }
    if (n == 2 || n == 3) {
        return true;
    }
    int k = sqrt(n);
    for (int i = k; i >= 2; i--) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
int H(int key){
    return key%MSize;
}
ostream& operator<<(ostream& out,vector<int>& p){
    if (p.size()>0) {
        out<<p[0];
        for (auto iter = p.begin()+1; iter!=p.end(); iter++) {
            if (*iter == -1) {
                out<<" -";
            }else{
                out<<' '<<*iter;
            }
        }
    }
    return out;
}
int main(int argc, const char * argv[]) {
    
    cin>>MSize>>N;
    int size=MSize;
    while (!isPrime(size)) {
        ++size;
    }
    MSize = size;
    vector<int> HashTable(size,-1);
    vector<int> outVector;
    for (int i = 0; i < N; i++) {
        int key,p;
        cin>>key;
        int j;
        for ( j = 0; j <= MSize; j++) {
            p = H(key);
            p+=j*j;
            p%=size;
            if (HashTable[p] == -1) {
                HashTable[p] = key;
                outVector.push_back(p);
                break;
            }
        }
        if (j > MSize) {
            outVector.push_back(-1);
        }
    }
    cout<<outVector<<endl;
    return 0;
}

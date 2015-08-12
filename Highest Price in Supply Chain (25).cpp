//
//  Highest Price in Supply Chain (25).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/6.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <vector>
#include <limits>
#include <math.h>
using namespace std;
int N;
vector<int> d;
vector<int> S;



int cpud(int i){
    if (d[i]!=-1) {
        return d[i];
    }
    if (S[i]==-1) {
        return 0;
    }
    return d[i]=(cpud(S[i])+1);
}

int main(int argc,const char* argv[]){
    
    double P,r;
    cin>>N>>P>>r;
    S.resize(N);
    d.resize(N, -1);
    for (int i=0; i<N; i++) {
        scanf("%d",S.begin()+i);
    }
    int num=0;
    int max=0;
    for (int i=0; i<N; i++) {
        int temp = cpud(i);
        if (temp>max) {
            max=temp;
            num=1;
        }else if(temp==max){
            num++;
        }
    }
    printf("%.2f %d\n",P*pow((1+r/100),max),num);
    return 0;
}

//
//  Prime Factors (25).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/11.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
int main(int argc,const char* argv[]){
    long int N;
    cin>>N;
    vector<vector<int>> prime;
    int i=2;
    cout<<N<<'=';
    while (i <= sqrt(N)+1) {
        vector<int> temp;
        while (N%i==0) {
            N/=i;
            temp.push_back(i);
        }
        if (!temp.empty()) {
            prime.push_back(temp);
        }
        i++;
    }
    if (prime.empty()) {
        cout<<N;
    }else{
        if (prime[0].size()==1) {
            cout<<prime[0][0];
        }else{
            cout<<prime[0][0]<<'^'<<prime[0].size();
        }
        for (int i=1; i<prime.size(); i++) {
            cout<<'*';
            if (prime[i].size()==1) {
                cout<<prime[i][0];
            }else{
                cout<<prime[i][0]<<'^'<<prime[i].size();
            }
        }
        if (N!=1) {
            cout<<'*'<<N;
        }
    }
    cout<<endl;
    return 0;
}

//
//  Consecutive Factors (20).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/8.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
int main(int argc,const char* argv[]){
    long long N=1;
    cin>>N;
    vector<long long> maxArray;
    long long end = sqrt(N)+1;
    for (long long i=2; i<end; ++i) {
        long long temp = N;
        vector<long long> tempArray;
        for (long long j=i;j<N/2; ++j) {
            if ((temp%j)!=0) {
                break;
            }
            tempArray.push_back(j);
            temp/=j;
        }
        if (tempArray.size()>maxArray.size()) {
            maxArray=tempArray;
        }
    }
    if (maxArray.size()==0) {
        maxArray.push_back(N);
    }
    long index;
    cout<<maxArray.size()<<endl;
    for (index=0; index<maxArray.size()-1; ++index) {
        cout<<maxArray[index]<<'*';
    }
    cout<<maxArray[index]<<endl;
    
    return 0;
}

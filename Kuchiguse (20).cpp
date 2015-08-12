//
//  Kuchiguse (20).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/9.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc,const char* argv[]){
    ios::sync_with_stdio(false);
    int N;
    cin>>N;
    string nr;
    getline(cin,nr);
    vector<string> a;
    a.resize(N);
    for (int i=0; i<N; i++) {
        getline(cin, a[i]);
    }
    sort(a.begin(), a.end());
    size_t max=a[0].size();
    for (int i=1; i<N; i++) {
        size_t temp=0;
        auto it=a[i].rbegin();
        auto i0=a[0].rbegin();
        for (;temp<max; temp++) {
            if (*it++!=*i0++) {
                break;
            }
        }
        max=temp;
    }
    
    if (max==0)
        cout<<"nai"<<endl;
    else{
        cout<<a[0].c_str()+(a[0].size()-max)<<endl;
    }
    return 0;
}

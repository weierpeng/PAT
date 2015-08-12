//
//  QQ帐户的申请与登陆.cpp
//  TestAllThings
//
//  Created by 彭威 on 15/7/26.
//  Copyright © 2015年 NJU. All rights reserved.
//

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
using namespace std;
int main(int argc,const char* argv[]){
    unordered_map<unsigned long long, string> qqSQL;
    int N;
    cin>>N;
    while (N--) {
        string op;
        unsigned long long qq;
        string pw;
        cin>>op>>qq>>pw;
        if (op == "L") {
            auto iter = qqSQL.find(qq);
            if (iter == qqSQL.end()) {
                cout<<"ERROR: Not Exist"<<endl;
                continue;
            }else{
                if (qqSQL[qq] == pw) {
                    cout<<"Login: OK"<<endl;
                    continue;
                }else{
                    cout<<"ERROR: Wrong PW"<<endl;
                    continue;
                }
            }
        }else if (op == "N"){
            auto iter = qqSQL.find(qq);
            if (iter == qqSQL.end()) {
                qqSQL[qq] = pw;
                cout<<"New: OK"<<endl;
                continue;
            }else{
                cout<<"ERROR: Exist"<<endl;
                continue;
            }
        }
    }
    return 0;
}


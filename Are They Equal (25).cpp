//
//  Are They Equal (25).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/11.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<string> split(const string& s,char ch){
    vector<string> re;
    size_t last = 0;
    auto pos = s.find(ch);
    if (s[0]=='-'){
        re.push_back(s.substr(0,1));
        last=1;
    }else{
        re.push_back(string());
    }
    while (pos < s.size()) {
        string temp = s.substr(last,pos-last);
        re.push_back(temp);
        last = pos+1;
        pos = s.find(ch, last);
    }
    string temp = s.substr(last,pos-last);
    re.push_back(temp);
    re.resize(3);
    return re;
}
struct StandardNumber {
    string num;
    int exp;
    int n;
    string flag;
    
    StandardNumber(int n):n(n){num.resize(n);};
    friend istream& operator>>(istream& in,StandardNumber& p){
        string temp;
        int exp = 0;
        in>>temp;
        vector<string> num = split(temp, '.');
        if (num[1].size()==1 && num[1][0]=='0'){
            int i=0;
            for (;i<num[2].size();i++){
                if (num[2][i]!='0'){
                    exp=-i;
                    break;
                }
            }
            int j=0;
            while(i<num[2].size() && j<p.n){
                p.num[j++]=num[2][i++];
            }
            while(j<p.n){
                p.num[j++]='0';
            }
            
        }else{
            int i=0;
            int j=0;
            for (;i<num[1].size();i++){
                if (num[1][i]!='0'){
                    exp=(int)num[1].size()-i;
                    break;
                }
            }
            while(i<num[1].size() && j<p.n){
                p.num[j++]=num[1][i++];
            }
            i=0;
            while(i<num[2].size() && j<p.n){
                p.num[j++]=num[2][i++];
            }
            while(j<p.n){
                p.num[j++]='0';
            }
        }
        p.exp=exp;
        p.flag=num[0];
        return in;
    }
    friend bool operator==(StandardNumber& p1,StandardNumber&p2){
        if (p1.num==p2.num && p1.exp == p2.exp && p1.flag==p2.flag)return true;
        return false;
    }
    friend ostream& operator<<(ostream& out,StandardNumber& p){
        cout<<p.flag<<"0."<<p.num<<"*10^"<<p.exp;
        return out;
    }
};
int main(int argc,const char* argv[]){
    ios::sync_with_stdio(false);
    int N;
    cin>>N;
    StandardNumber A(N),B(N);
    cin>>A>>B;
    if (A==B) {
        cout<<"YES"<<' ';
        cout<<A<<endl;
    }else{
        cout<<"NO"<<' '
        <<A<<' '<<B<<endl;
    }

    return 0;
}

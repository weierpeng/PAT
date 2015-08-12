//
//  Cars on Campus (30).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/7.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

struct record {
    string plate_number;
    long time;
    string status;
    bool valid;
    friend bool operator<(const record& p1,const record& p2){
        if (p1.time<p2.time) return true;
        else if (p1.time==p2.time && p1.plate_number>p2.plate_number)
            return true;
        return false;}
    friend bool operator==(const record& p1,const record& p2){return p1.plate_number==p2.plate_number;}
};

long time2long(){
    string s;
    cin>>s;
    long temp=0;
    temp+=(s[0]-'0')*10*3600;
    temp+=(s[1]-'0')*3600;
    temp+=(s[3]-'0')*10*60;
    temp+=(s[4]-'0')*60;
    temp+=(s[6]-'0')*10;
    temp+=(s[7]-'0');
    return temp;
}

int main(int argc,const char* argv[]){
    ios::sync_with_stdio(false);
    int N,K;
    cin>>N>>K;
    vector<record> store;
    for (long i=0; i<N; i++) {
        record temp;
        cin>>temp.plate_number;
        temp.time=time2long();
        cin>>temp.status;
        store.push_back(temp);
    }
    for (long i=0; i<K; i++) {
        record temp;
        temp.time=time2long();
        //temp.status="print";
        //temp.plate_number = "0000000";
        store.push_back(temp);
    }
    sort(store.begin(), store.end());
    map<string, long> check;
    for (long i=0; i<store.size(); ++i) {
        if (check.find(store[i].plate_number)==check.end()) {
            check[store[i].plate_number]=-1;
        }
        if (store[i].status == "in") {
            long &x =check[store[i].plate_number];
            if(x==-1){
                x = i;
                continue;
            }
            store[x].status = "out";
            x=i;
        }else if (store[i].status == "out"){
            long &x =check[store[i].plate_number];
            if (x!=-1) {
                x=-1;
            }
        }
    }
    for (auto i=check.begin();i!=check.end();++i){
        if (i->second!=-1) {
            store[i->second].status="out";
        }
    }
    unordered_map<string, long> timeOnCampus(N);
    unordered_map<string, long> OnCampus(N);
    for (auto iter = store.begin(); iter!=store.end(); ++iter) {
        if (iter->status == "in") {
            OnCampus[iter->plate_number]=iter->time;
        }else if (iter->status == "out"){
            auto x=OnCampus.find(iter->plate_number);
            if (x == OnCampus.end()) {
                continue;
            }
            timeOnCampus[iter->plate_number]+=iter->time - x->second;
            OnCampus.erase(x);
        }else {
            printf("%lu\n",OnCampus.size());
        }
    }
    vector<string> longTime;
    long max=0;
    for (auto x = timeOnCampus.begin(); x!=timeOnCampus.end(); ++x) {
        
        if (x->second>max) {
            longTime.clear();
            longTime.push_back(x->first);
            max=x->second;
        }else if (x->second==max){
            longTime.push_back(x->first);
        }
        
    }
    sort(longTime.begin(), longTime.end());
    for (auto iter = longTime.begin(); iter!=longTime.end(); ++iter) {
        printf("%s ",iter->c_str());
    }
    printf("%02ld:%02ld:%02ld\n",max/3600,(max%3600/60),max%60);
    return 0;
}

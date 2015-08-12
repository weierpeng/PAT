//
//  Cars on Campus (30)(2).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/8.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;
const size_t DAYTIME = 24 * 60 * 60 ;
struct record {
    size_t plate_number;
    long time;
    bool in;
    
    friend bool operator<(const record& p1,const record& p2){
        if (p1.plate_number < p2.plate_number)
            return true;
        else if (p1.plate_number == p2.plate_number){
            if (p1.time < p2.time)
                return true;
        }
        return false;
    }
};
int main(int argc,const char* argv[]){
    ios::sync_with_stdio(false);
    int N,K;
    scanf("%d %d",&N,&K);
    vector<record> store;
    unordered_map<string, size_t> str2int;
    vector<string> int2str;
    for (int i=0; i<N; i++) {
        char plate[8];
        record temp;
        scanf("%s",plate);
        string plate_number(plate);
        if (str2int.count(plate_number)==0) {
            int2str.push_back(plate_number);
            str2int[plate_number]=int2str.size()-1;
        }
        temp.plate_number = str2int[plate_number];
        int hh,mm,ss;
        scanf("%d:%d:%d",&hh,&mm,&ss);
        temp.time = hh*3600+mm*60+ss;
        char action[5];
        scanf("%s",action);
        if (action[0]=='i') {
            temp.in=true;
        }else{
            temp.in=false;
        }
        store.push_back(temp);
    }
    sort(store.begin(), store.end());
    vector<int> inCampus(DAYTIME,0);
    vector<size_t> OnCampus(DAYTIME,0);
    long maxTime=0;
    vector<string> maxRecord;
    long tempTime=0;
    for (auto iter = store.begin()+1; iter!=store.end(); ++iter) {
        auto last = iter-1;
        if (iter->plate_number == last->plate_number) {
            if (!(iter->in) && (last->in)) {
                tempTime+=iter->time-last->time;
                --inCampus[iter->time];
                ++inCampus[last->time];
            }
        }else{
            if (tempTime>maxTime) {
                maxRecord.clear();
                maxRecord.push_back(int2str[last->plate_number]);
                maxTime=tempTime;
            }else if(tempTime==maxTime){
                maxRecord.push_back(int2str[last->plate_number]);
            }
            tempTime=0;
        }
    }
    OnCampus[0]+=inCampus[0];
    for (size_t i=1; i < OnCampus.size() ; ++i) {
        OnCampus[i]=OnCampus[i-1]+inCampus[i];
    }
    for (int i=0; i<K; ++i) {
        int hh,mm,ss;
        scanf("%d:%d:%d",&hh,&mm,&ss);
        size_t time = hh*3600+mm*60+ss;
        printf("%ld\n",OnCampus[time]);
    }
    for (auto i = maxRecord.begin(); i != maxRecord.end(); ++i) {
        printf("%s ",i->c_str());
    }
    printf("%02ld:%02ld:%02ld\n",maxTime/3600,maxTime%3600/60,maxTime%60);
    return 0;
}

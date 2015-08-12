//
//  Stack (30).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/10.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>
#include <string>
using namespace std;

template <typename T>
class Stack_PeekMedian {
    multiset<T> store_low;
    multiset<T> store_high;
    T median;
    stack<T> s;
private:
    void rebalance(){
        if (s.empty()) {return;}
        size_t n1 = store_low.size();
        size_t n2 = store_high.size();
        if (n1 > n2) {
            auto iter = store_low.end();
            --iter;
            store_high.insert(median);
            median = *iter;
            store_low.erase(iter);
        }else if (n1+1 < n2){
            auto iter = store_high.begin();
            store_low.insert(median);
            median = *iter;
            store_high.erase(iter);
        }
    }
public:
    bool empty(){return s.empty();}
    T Pop(){
        T temp=s.top();
        s.pop();
        if (temp>median && !store_high.empty()) {
            auto iter=store_high.find(temp);
            store_high.erase(iter);
        }else if (temp<median && !store_low.empty()){
            auto iter=store_low.find(temp);
            store_low.erase(iter);
        }else if (temp==median && !store_high.empty()){
            auto iter=store_high.begin();
            median=*iter;
            store_high.erase(iter);
        }
        rebalance();
        return temp;
    }
    void Push(const T& i){
        if (s.empty()) {
            median=i;
            s.push(i);
        }else if (i<median){
            store_low.insert(i);
            s.push(i);
        }else {
            store_high.insert(i);
            s.push(i);
        }
        rebalance();
    }
    T PeekMedian(){return median;}
};


int main(int argc,const char* argv[]){
    ios::sync_with_stdio(false);
    Stack_PeekMedian<int> s;
    int N;
    cin>>N;
    while (N--) {
        string act;
        cin>>act;
        if (act=="Push") {
            int i;
            cin>>i;
            s.Push(i);
        }else if(act=="Pop"){
            if (s.empty()) {
                cout<<"Invalid"<<endl;
                continue;
            }
            int i=s.Pop();
            cout<<i<<endl;
        }else{
            if (s.empty()) {
                cout<<"Invalid"<<endl;
                continue;
            }
            int i=s.PeekMedian();
            cout<<i<<endl;
        }
    }
    return 0;
}

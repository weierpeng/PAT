//
//  Insertion or Heap Sort (25).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/8.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//
// It's not enough
#include <iostream>
#include <vector>
using namespace std;
vector<int> store;
vector<int> fun;
int N;

void Heap(){
    cout<<"Heap Sort"<<endl;
    int i,j;
    for (i=1; i<N; i++) {
        if (fun[i]>=fun[0]) {
            break;
        }
    }
    i--;
    int temp = fun[i];
    fun[i]=fun[0];
    fun[0]=temp;
    j=0;
    while (j<i) {
        int big=j;
        int z;
        z=j*2+1;
        if (z<i && fun[j]<fun[z]) {
            big=z;
        }
        z++;
        if (z<i && fun[big]<fun[z]) {
            big=z;
        }
        if (big==j) {
            break;
        }
        int temp = fun[j];
        fun[j]=fun[big];
        fun[big]=temp;
        j=big;
    }
}
void Insertion(){
    cout<<"Insertion Sort"<<endl;
    int i,j;
    for ( i=N-1; i>=0; i--) {
        if (fun[i]!=store[i]) {
            break;
        }
    }
    i++;
    int temp = fun[i];
    for (j=i-1; j>=0; j--) {
        if (fun[j]>=temp) {
            fun[j+1]=fun[j];
        }else{
            fun[j+1]=temp;
            break;
        }
    }
}
bool isHeap(){
    int i;
    for (i=N-2; i>0; --i) {
        if (fun[i]<fun[0]) {
            break;
        }else if (fun[i+1]<fun[i]){
            return false;
        }
    }
    i++;
    for (int j=0; j<i/2; j++) {
        int z=j*2+1;
        if (z<i && fun[j]<fun[z]) {
            return false;
        }
        z++;
        if (z<i && fun[j]<fun[z]) {
            return false;
        }
    }
    return true;
}
bool isInsert(){
    int i;
    for (i=N-1; i>0; --i) {
        if (store[i]!=fun[i]){
            break;
        }
    }
    for (int j=i; j>0; j--) {
        if (fun[j]<fun[j-1]) {
            return false;
        }
    }
    return true;
}
int main(int argc,const char* argv[]){
    ios::sync_with_stdio(false);
    cin>>N;
    store.resize(N);
    fun.resize(N);
    for (int i=0; i<N; i++) {
        cin>>store[i];
    }
    for (int i=0; i<N; i++) {
        cin>>fun[i];
    }
    if (!isInsert()) {
        Heap();
    }else if (!isHeap()){
        Insertion();
    }
    cout<<fun[0];
    for (int i=1; i<N; i++) {
        cout<<' '<<fun[i];
    }
    cout<<endl;
    return 0;
}


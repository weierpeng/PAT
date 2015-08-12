//
//  A+B in Hogwarts (20).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/11.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

class Hogwarts {
    int a[3];
public:
    Hogwarts(string& str){
        sscanf(str.c_str(), "%d.%d.%d",a,a+1,a+2);
    }
    Hogwarts(){};
    friend const Hogwarts operator+(const Hogwarts& p1,const Hogwarts& p2){
        Hogwarts temp;
        temp.a[2]=p1.a[2]+p2.a[2];
        temp.a[1]=temp.a[2]/29;
        temp.a[2]%=29;
        temp.a[1]+=p1.a[1]+p2.a[1];
        temp.a[0]=temp.a[1]/17;
        temp.a[1]%=17;
        temp.a[0]+=p1.a[0]+p2.a[0];
        return temp;
    }
    void print(){
        printf("%d.%d.%d",a[0],a[1],a[2]);
    }
};
int main(int argc,const char* argv[]){
    string s1,s2;
    cin>>s1>>s2;
    Hogwarts n1(s1),n2(s2),temp;
    temp = n1 + n2;
    temp.print();
    return 0;
}

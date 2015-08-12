//
//  有限状态机.cpp
//  TestAllThings
//
//  Created by 彭威 on 15/7/28.
//  Copyright © 2015年 NJU. All rights reserved.
//
/*
 
 [我也带来一波节奏]既然想reroll码农的这么多，那来做个游戏吧，真实BAT面试(37楼以后各路高玩出现)
 发这个没有别的意思
 有很多转行/自学/经验少的旁友很好奇真正的面试题是什么样子的，也想检验下自己什么水平
 正好最近朋友给我看了这个真实的例子，就发来给大家看看
 本题不涉及任何特定的算法，数学与专门的理论知识
 考察的是基本的逻辑思维，抽象思维，基本的算法分析与动手能力
 
 
 如图有限状态机
 A，B，C三个状态
 从左边start进入A开始运行，到达最右边的end状态结束
 每个状态节点有若干条边来标识状态转换的路径
 每个边上的符号代表一个概率p，表示到达这个节点后有p的概率走这条路线
 概率值精确到2位小数
 每个状态所有出去的路径概率之和为1
 比如a1+a2+a3+a4=1
 每到达一个状态后输出该状态的字母
 如果到达end则停止输出
 那么根据这个规则，可以随机输出一系列字符串，例如：
 AABC
 ABCCCAABC
 等等
 
 问题：
 1. 写一个程序实现上述字符串输出
 2. 给定一个字符串长度N，写一个函数计算1中的算法最终输出字符串长度为N的概率。
 3. 给出2中算法的复杂度，是否有优化方法。
 4. 快下班的时候，boss：小李啊，客户突然有个需求，要通过读取配置文件得到状态机信息，改下你的程序以支持用户输入的任意状态机，改完了再走吧，打车公司报销
 
 要求：
 手写代码
 编码限时15分钟 (只要有核心功能即可，标准库随便用)
 复杂度什么的写完代码再慢慢聊
 
 
 
 */
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

#define Rand ((double)arc4random() / 0x100000000)

using namespace std;
static const int n = 4;
static const double p[n][n] = {
    0.1,0.2,0.3,0.4,
    0.2,0.3,0.4,0.1,
    0.3,0.4,0.1,0.2,
    0  ,0  ,0  ,0
};
char print[n] = {'A','B','C','\n'};
class AutoStep {
    int current;
public:
    AutoStep(int start=0):current(start){};
    string start(){
        string result;
        result.push_back(print[current]);
        while (!isEnd()) {
            current = makeChoice();
            result.push_back(print[current]);
        }
        return result;
    }
protected:
    bool isEnd(){
        return (n-1) == current;
    }
    int makeChoice(){
        vector<double> pro(n);
        pro[0] = probability(current,0);
        for (int i = 1; i < n; i++) {
            pro[i] = pro[i-1] + probability(current,i);
        }
        auto iter = lower_bound(pro.begin(), pro.end(), Rand);
        return (int)(iter - pro.begin());
    }
    double probability(int i,int j){
        return p[i][j];
    }
};
template <typename T>
class Matrix {
private:
    T **m;
    T *m0;
    unsigned int n;
    unsigned int K;
    
public:
    Matrix(unsigned int _n,const T *a){
        const T *p=a;
        init(_n);
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++) {
                m[i][j]=*p++;
            }
        
    }
    Matrix(unsigned int _n){
        init(_n);
    };
    void init(unsigned int _n){
        n=_n;
        m = new T*[n];
        m0= new T[n*n];
        for (int i=0;i<n*n;i++)m0[i]=0;
        for (int i=0;i<n; i++){
            m[i]=&(m0[i*n]);
        }
    }
    Matrix(const Matrix& r){
        init(r.n);
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++) {
                m[i][j]=r.m[i][j];
            }
    }
    
    Matrix& operator=(const Matrix& r){
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++) {
                m[i][j]=r.m[i][j];
            }
        return *this;
    }
    Matrix& operator%=(unsigned long long r){
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++) {
                m[i][j]%=r;
            }
        return *this;
    }
    Matrix& operator+=(const Matrix& r){
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++) {
                m[i][j]+=r.m[i][j];
                
            }
        return *this;
    }
    Matrix& operator*=(const Matrix& r){
        Matrix temp(n);
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++) {
                for (int k=0; k<n; k++) {
                    temp.m[i][j]+=(this->m[i][k]*r.m[k][j]);
                }
            }
        *this=temp;
        return *this;
    }
    void MatrixI(){
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++) {
                m[i][j]=0;
            }
        for (int i=0; i<n; i++){
            m[i][i]=1;
        }
    }
    T value(int i,int j){
        return m[i][j];
    }
};
template <typename T>
Matrix<T> operator+(const Matrix<T>& s,const Matrix<T>& r){
    Matrix<T> temp(s);
    temp+=r;
    return temp;
}
template <typename T>
Matrix<T> operator*(const Matrix<T> &s,const Matrix<T> &r){
    Matrix<T> temp(s);
    temp*=r;
    return temp;
}

int main(int argc,const char* argv[]){
    int N;
    cin>>N;
    while (N--) {
        AutoStep step;
        cout<<step.start();
    }
    cin>>N;
    Matrix<double> M(n,*p);
    vector<Matrix<double>> a;
    Matrix<double> temp(n);
    a.push_back(M);
    for(int i=1;i<=32;i++){
        temp=a[i-1];
        temp*=temp;
        a.push_back(temp);
    }
    temp.MatrixI();
    for (int i=0; i<32; i++) {
        if (N & (1<<i)) {
            temp*=a[i];
        }
    }
    cout<<temp.value(0, n-1)<<endl;
    return 0;
}
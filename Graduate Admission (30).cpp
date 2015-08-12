//
//  Graduate Admission (30).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/9.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N,M,K;
vector<vector<int>> schools;
vector<int> quota;
struct student {
    int G_E;
    int G_I;
    int Total;
    vector<int> choice;
    friend istream& operator>>(istream& in,student& s){
        in>>s.G_E>>s.G_I;
        s.Total=s.G_E+s.G_I;
        s.choice.resize(K);
        for (int i=0;i<K;i++)in>>s.choice[i];
        return in;
    }
    friend bool operator==(const student& s1,const student& s2){
        if (s1.Total == s2.Total && s1.G_E == s2.G_E)
            return true;
        return false;
    }
};
vector<student> stu;
struct ID {
    int ID;
    
};
vector<ID> id_rank;
bool operator<(const ID& s1,const ID& s2){
    if (stu[s1.ID].Total>stu[s2.ID].Total)return true;
    else if (stu[s1.ID].Total == stu[s2.ID].Total){
        if (stu[s1.ID].G_E > stu[s2.ID].G_E) return true;
    }
    return false;
}
bool operator==(const ID& s1,const ID& s2){
    if (stu[s1.ID].Total == stu[s2.ID].Total && stu[s1.ID].G_E == stu[s2.ID].G_E)
        return true;
    return false;
}
int main(int argc,const char* argv[]){
    ios::sync_with_stdio(false);
    cin>>N>>M>>K;
    stu.resize(N);
    id_rank.resize(N);
    schools.resize(M);
    quota.resize(M);
    for (int i=0; i<M; i++) {
        cin>>quota[i];
    }
    for (int i=0; i<N; i++) {
        cin>>stu[i];
        id_rank[i].ID=i;
    }
    sort(id_rank.begin(), id_rank.end());
    for (int i=0; i<N; i++) {
        int z = id_rank[i].ID;
        for (int j=0; j<K; j++) {
            int k=stu[z].choice[j];
            if (schools[k].size()<quota[k]) {
                schools[k].push_back(z);
                break;
            }else if(stu[z]==stu[schools[k].back()]){
                schools[k].push_back(z);
                break;
            }
        }
    }
    for (int i=0; i<M; i++) {
        if (schools[i].size()) {
            sort(schools[i].begin(), schools[i].end());
            cout<<schools[i][0];
            for (int j=1; j<schools[i].size(); j++) {
                cout<<' '<<schools[i][j];
            }
        }
        cout<<endl;
    }
    return 0;
}

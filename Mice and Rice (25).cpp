//
//  Mice and Rice (25).cpp
//  PAT_test
//
//  Created by 彭威 on 15/8/10.
//  Copyright © 2015年 biophy.nju.edu.cn. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;
int main(int argc,const char* argv[]){
    ios::sync_with_stdio(false);
    int Np,Ng;
    cin>>Np>>Ng;
    vector<int> mice(Np);
    vector<int> pos(Np);
    vector<int> mice_rank(Np);
    for (int i=0; i<Np; i++) {
        cin>>mice[i];
    }
    for (int i=0; i<Np; i++) {
        cin>>pos[i];
    }
    size_t end = pos.size();
    auto func = [&end,&mice,&pos,&Ng](size_t i){
        size_t max=i;
        int max_mice=mice[pos[i]];
        for (size_t j=i+1; j<end && j<i+Ng; j++) {
            if (mice[pos[j]]>max_mice) {
                max_mice=mice[pos[j]];
                max=j;
            }
        }
        return pos[max];
    };
    int r = (Np-1)/Ng + 2;
    while (end>1) {
        for (size_t i=0; i<end; i++) {
            mice_rank[pos[i]]=r;
        }
        size_t j=0;
        for (size_t i=0; i<end; i+=Ng) {
            pos[j++]=(int)func(i);
        }
        end = j;
        r = (int)(j-1)/Ng + 2;
    }
    mice_rank[pos[0]]=1;
    cout<<mice_rank[0];
    for (int i=1; i<Np; i++) {
        cout<<' '<<mice_rank[i];
    }
    cout<<endl;
    return 0;
}




#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class User {
    public:
    int user_id,total_score,*score;
    unsigned int K;
    bool flag ;
    int perfect;

    friend class ManageUser;
    friend bool operator<(const User &s,const User &r);
    friend bool compare(const User &s,const User &r);
    
    User(unsigned int _K=5):K(_K),total_score(-1),flag(false){
        score = new int[K];
        for (int i=0; i<K; i++)score[i]=-1;
    }
    
    void setScore(int _userid,int _k,int _score){
        user_id=_userid;
        if (_score < score[_k])return;
        if (_score == -1) score[_k] = 0;
        if (_score > score[_k]){
            score[_k]=_score;
            flag = true;
        }
    }
};

bool compare(const User &s,const User &r){
    if (s.total_score > r.total_score) {
        return true;
    }else if(s.total_score == r.total_score){
        if (s.perfect > r.perfect) {
            return true;
        }else if(s.perfect == r.perfect && s.user_id < r.user_id)
            return true;
    }
    return false;
}
class ManageUser {
    int N,K,M;
    int PERFERT[5]={0};
    User *u;
    
public:
    void readPara(){
        cin>>N>>K>>M;
        for (int i=0; i<K; i++)cin>>PERFERT[i];
        vector<User> u(N+1);
        int user_id,k,score;
        while (M--) {
            cin>>user_id>>k>>score;
            u[user_id].setScore(user_id,k-1,score);
        }
        for (int i=1; i<=N; i++) {
            totalScore(u[i]);
        }
        sort(u.begin()+1,u.end(),compare);
        int n=0,currentScore=-1;
        for (int i=1; i<=N; i++) {
            
            if (currentScore!=u[i].total_score) {
                n=i;
                currentScore=u[i].total_score;
            }
            if (u[i].flag == false)break;
            printf("%d %05d %d",n,u[i].user_id,u[i].total_score);
            for (int j=0; j<K; j++) {
                if (u[i].score[j]==-1) {
                    printf(" -");
                }else
                printf(" %d",u[i].score[j]);
            }
            cout<<endl;
        }
    }
    int totalScore(User &s){
        if (s.flag) {
            s.perfect = 0;
            s.total_score = 0;
            for (int i=0; i<K; i++) {
                if (s.score[i]!=-1) {
                    s.total_score += s.score[i];
                    if (s.score[i]==PERFERT[i])++s.perfect;
                }
            }
            return s.total_score;
        }
        return -1;
    }
    
};

int main(){
    ManageUser M;
    M.readPara();
    return 0;
}